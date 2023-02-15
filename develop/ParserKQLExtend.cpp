#include <Parsers/ASTLiteral.h>
#include <Parsers/IParserBase.h>
#include <Parsers/ExpressionListParsers.h>
#include <Parsers/ParserTablesInSelectQuery.h>
#include <Parsers/Kusto/ParserKQLQuery.h>
#include <Parsers/Kusto/ParserKQLMakeSeries.h>
#include <Parsers/Kusto/ParserKQLOperators.h>
#include <Parsers/Kusto/ParserKQLExtend.h>
#include <Parsers/ParserSetQuery.h>
#include <format>

namespace DB
{

bool ParserKQLMVExpand::parseColumnArrayExprs(ColumnArrayExprs & column_array_exprs, Pos & pos, Expected & expected)
{
    ParserToken equals(TokenType::Equals);
    ParserToken open_bracket(TokenType::OpeningRoundBracket);
    ParserToken close_bracket(TokenType::ClosingRoundBracket);
    ParserToken comma(TokenType::Comma);

    ParserKeyword s_to("to");
    ParserKeyword s_type("type");

    while (!pos->isEnd() && pos->type != TokenType::PipeMark && pos->type != TokenType::Semicolon)
    {
        String alias;
        String column_array_expr;
        String to_type;
        
        String first_token(pos->begin, pos->end);

        ++pos;
        if (equals.ignore(pos, expected))
        {
            alias = std::move(first_token);
            column_array_expr = String(pos->begin, pos->end);
            ++pos;
        }
        else
            column_array_expr = std::move(first_token);

        if (s_to.ignore(pos, expected))
        {
            if (!s_type.ignore(pos, expected))
                return false;
                
            if (!open_bracket.ignore(pos, expected))
                return false;

            to_type = String (pos->begin, pos->end);

            ++pos;
            if (!close_bracket.ignore(pos, expected))
                return false;
        }

        if (alias.empty())
            alias = column_array_expr;
        column_array_exprs.push_back(ColumnArrayExpr(alias, column_array_expr, to_type));

        if (String(pos->begin, pos->end) == "limit")
        {
            break;
        }
        if (!comma.ignore(pos, expected))
            break;
    }
    return true;
}

bool ParserKQLMVExpand::parserMVExpand(KQLMVExpand & kql_mv_expand, Pos & pos, Expected & expected)
{
    ParserKeyword s_bagexpansion("bagexpansion");
    ParserKeyword s_kind("kind");
    ParserKeyword s_with_itemindex("with_itemindex");
    ParserKeyword s_to("to");
    ParserKeyword s_type("type");
    ParserKeyword s_limit("limit");

    ParserToken equals(TokenType::Equals);
    ParserToken comma(TokenType::Comma);

    auto & column_array_exprs = kql_mv_expand.column_array_exprs;
    auto & bagexpansion = kql_mv_expand.bagexpansion;
    auto & with_itemindex = kql_mv_expand.with_itemindex;
    auto & limit = kql_mv_expand.limit;

    if (s_bagexpansion.ignore(pos, expected))
    {
        if (!equals.ignore(pos, expected))
            return false;
        bagexpansion = String(pos->begin, pos->end);
        ++pos;
    }
    else if (s_kind.ignore(pos, expected))
    {
        if (!equals.ignore(pos, expected))
            return false;
        bagexpansion = String(pos->begin, pos->end);
        ++pos;
    }

    if (s_with_itemindex.ignore(pos, expected))
    {
        if (!equals.ignore(pos, expected))
            return false;
        with_itemindex = String(pos->begin, pos->end);
        ++pos;
    }

    if (!parseColumnArrayExprs(column_array_exprs, pos, expected))
        return false;

    if (s_limit.ignore(pos, expected))
        limit = String(pos->begin, pos->end);

    return true;
}



String ParserKQLMVExpand::genQuery(KQLMVExpand & kql_mv_expand, String input)
{
/*
    struct ColumnArrayExpr {
        String alias;
        String column_array_expr;
        String to_type;
    struct KQLMVExpand {
        ColumnArrayExprs column_array_exprs;
        String bagexpansion;
        String with_itemindex;
        String limit;
    */    
    //auto & limit = kql_mv_expand.limit;

    String expand_str;

    for (auto column : kql_mv_expand.column_array_exprs)
    {
        expand_str = expand_str.empty() ? String("ARRAY JOIN ") + column.alias : expand_str + "," + column.alias;
    }

    if (!kql_mv_expand.limit.empty())
        expand_str += " LIMIT " + kql_mv_expand.limit;
    auto sub_query = std::format("(Select * From {} {})", input, expand_str);

    return sub_query;
}

bool ParserKQLMVExpand::parseImpl(Pos & pos, ASTPtr & node, Expected & expected)
{
    ASTPtr tmp_setting;
    if (op_pos.empty())
        return true;

    auto begin = pos;
    String input = table_name;
    //KQLMVExpand kql_mv_expand;
    for (auto npos : op_pos)
    {
        auto kql_mv_expand = std::make_unique<KQLMVExpand>();
        if (parserMVExpand(*kql_mv_expand, npos, expected))
            input = genQuery(*kql_mv_expand, input);
    }


    Tokens token_subquery(input.c_str(), input.c_str() + input.size());
    IParser::Pos pos_subquery(token_subquery, pos.max_depth);

    if (!ParserTablesInSelectQuery().parse(pos_subquery, node, expected))
        return false;

    const String setting_str = "enable_unaligned_array_join = 1";
    Tokens token_settings(setting_str.c_str(), setting_str.c_str() + setting_str.size());
    IParser::Pos pos_settings(token_settings, pos.max_depth);

    //ParserSetQuery parser_settings(true);
    if (!ParserSetQuery(true).parse(pos_settings, tmp_setting, expected))
        return false;

    settings = std::move(tmp_setting);
    pos = begin;
    return true;
}

}
