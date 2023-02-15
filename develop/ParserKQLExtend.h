
#pragma once

#include <Parsers/IParserBase.h>
#include <Parsers/Kusto/ParserKQLQuery.h>

namespace DB
{

class ParserKQLMVExpand : public ParserKQLBase
{
public:

    void setTableName(String table_name_) {table_name = table_name_;}
    ASTPtr settings;
protected:

    struct ColumnArrayExpr {
        String alias;
        String column_array_expr;
        String to_type;
        ColumnArrayExpr(String alias_, String column_array_expr_, String to_type_)
        :alias(alias_), column_array_expr(column_array_expr_), to_type(to_type_){}
    };
    using ColumnArrayExprs = std::vector<ColumnArrayExpr>;

    struct KQLMVExpand {
        ColumnArrayExprs column_array_exprs;
        String bagexpansion;
        String with_itemindex;
        String limit;
    };
 
    static bool parseColumnArrayExprs(ColumnArrayExprs & column_array_exprs, Pos & pos, Expected & expected);
    static bool parserMVExpand(KQLMVExpand & kql_mv_expand, Pos & pos, Expected & expected);
    static String genQuery(KQLMVExpand & kql_mv_expand, String input);
    const char * getName() const override { return "KQL mv-expand"; }
    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
private:
    String table_name;
};

}


/*

bool ParserKQLQuery::parseImpl(Pos & pos, ASTPtr & node, Expected & expected)
{
    auto select_query = std::make_shared<ASTSelectQuery>();
    node = select_query;

    ParserKQLFilter kql_filter_p;
    ParserKQLLimit kql_limit_p;
    ParserKQLProject kql_project_p;
    ParserKQLSort kql_sort_p;
    ParserKQLSummarize kql_summarize_p;
    ParserKQLTable kql_table_p;
    ParserKQLMakeSeries kql_make_series_p;
    ParserKQLMVExpand kql_mv_expand_p;

    ASTPtr select_expression_list;
    ASTPtr tables;
    ASTPtr where_expression;
    ASTPtr group_expression_list;
    ASTPtr order_expression_list;
    ASTPtr limit_length;
    ASTPtr settings;

    std::unordered_map<std::string, ParserKQLBase * > kql_parser = {
        { "filter",&kql_filter_p},
        { "where",&kql_filter_p},
        { "limit",&kql_limit_p},
        { "take",&kql_limit_p},
        { "project",&kql_project_p},
        { "sort",&kql_sort_p},
        { "order",&kql_sort_p},
        { "summarize",&kql_summarize_p},
        { "table",&kql_table_p},
        { "make-series",&kql_make_series_p},
        { "mv-expand",&kql_mv_expand_p}
    };

    std::vector<std::pair<String, Pos>> operation_pos;

    operation_pos.push_back(std::make_pair("table",pos));
    String table_name(pos->begin,pos->end);
    auto _pos = pos;
    auto idx = 0;
    while (!_pos->isEnd() && _pos->type != TokenType::Semicolon)
    {
        String tmp(_pos->begin, _pos->end);
        std::cout<<idx<<" _ "<< tmp << " _ type idx: " << int(_pos->type) <<std::endl;
        ++_pos;
        ++idx;
    }

    if (table_name == "print")
    {
        ++pos;
        if (!ParserKQLPrint().parse(pos, select_expression_list, expected))
            return false;

        select_query->setExpression(ASTSelectQuery::Expression::SELECT, std::move(select_expression_list));

        return true;
    }

    ++pos;
    while (!pos->isEnd() && pos->type != TokenType::Semicolon)
    {
        if (pos->type == TokenType::PipeMark)
        {
            ++pos;
            String kql_operator(pos->begin,pos->end);
            auto multi_word_op = [&] {
                auto new_op_pos = pos;
                ++pos;
                ParserToken s_dash(TokenType::Minus);
                if (s_dash.ignore(pos,expected))
                {
                    String new_op(new_op_pos->begin, pos->end);
                    //++pos;
                    return new_op;
                }
                return kql_operator;
            };

            kql_operator = multi_word_op();

            if (pos->type != TokenType::BareWord || kql_parser.find(kql_operator) == kql_parser.end())
                return false;
            ++pos;
            operation_pos.push_back(std::make_pair(kql_operator,pos));
            kql_parser[kql_operator]->getExprFromToken(pos);
        }
        else
            ++pos;
    }

    for (auto &op_pos : operation_pos)
    {
        auto kql_operator = op_pos.first;
        auto npos = op_pos.second;
        if (!npos.isValid())
            return false;

        if (!kql_parser[kql_operator]->parsePrepare(npos))
            return false;
    }

    if (!kql_table_p.parse(pos, tables, expected))
        return false;

    if (!kql_project_p.parse(pos, select_expression_list, expected))
        return false;

    kql_mv_expand_p.setTableName(table_name);
    if (!kql_mv_expand_p.parse(pos, tables, expected))
        return false;
    else
        settings = kql_mv_expand_p.settings;

    if (!kql_limit_p.parse(pos, limit_length, expected))
        return false;

    if (!kql_filter_p.parse(pos, where_expression, expected))
        return false;

    if (!kql_sort_p.parse(pos, order_expression_list, expected))
         return false;

    kql_summarize_p.setTableName(table_name);
    kql_summarize_p.setFilterPos(kql_filter_p.op_pos);
    if (!kql_summarize_p.parse(pos, select_expression_list, expected))
         return false;
    else
    {
        group_expression_list = kql_summarize_p.group_expression_list;
        if (kql_summarize_p.tables)
            tables = kql_summarize_p.tables;

        if (kql_summarize_p.where_expression)
            where_expression = kql_summarize_p.where_expression;
    }


    kql_make_series_p.setTableName(table_name);
    if (!kql_make_series_p.parse(pos, select_expression_list, expected))
         return false;
    else
    {
        if (kql_make_series_p.group_expression_list)
            group_expression_list = kql_make_series_p.group_expression_list;

        if (kql_make_series_p.tables)
            tables = kql_make_series_p.tables;

    }

    select_query->setExpression(ASTSelectQuery::Expression::SELECT, std::move(select_expression_list));
    select_query->setExpression(ASTSelectQuery::Expression::TABLES, std::move(tables));
    select_query->setExpression(ASTSelectQuery::Expression::WHERE, std::move(where_expression));
    select_query->setExpression(ASTSelectQuery::Expression::GROUP_BY, std::move(group_expression_list));
    select_query->setExpression(ASTSelectQuery::Expression::ORDER_BY, std::move(order_expression_list));
    select_query->setExpression(ASTSelectQuery::Expression::LIMIT_LENGTH, std::move(limit_length));
    select_query->setExpression(ASTSelectQuery::Expression::SETTINGS, std::move(settings));

    return true;
}

*/
