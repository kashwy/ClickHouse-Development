# Multiple ARRAY JOIN (Cartesian Product of Arrays) Tech Spec    

# Overview
The Multiple ARRAY JOIN is a missed feature of ClickHouse as described in the OPen Source issue [#8687](https://github.com/ClickHouse/ClickHouse/issues/8687), and IBM 
# Problem
Currently this feature only support one ARRAY JOIN, but can join  In this case, JOIN is performed with them simultaneously (the direct sum, not the cartesian product). 

the depth

https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Interpreters/InterpreterSelectQuery.cpp.html#293
    if (settings.max_subquery_depth && options.subquery_depth > settings.max_subquery_depth)
        throw Exception("Too deep subqueries. Maximum: " + settings.max_subquery_depth.toString(),
            ErrorCodes::TOO_DEEP_SUBQUERIES);

# Goal
The goal is to add this ARRAY JOIN (Cartesian Product of Arrays) to ClickHouse. which will :  
No Change on One Keyword of ARRAY JOIN.  New feature will not affect the behavior of existing ARRAY JOIN, e.g. one ARRAY JOIN with one column or one ARRAY JOIN with multiple column.
new feature will produce cartesian product of arrays:
1. Support multiple keyword of INNER ARRAY JOIN with one column, each ARRAY JOIN only has one column. e.g `ARRAY JOIN  arr1 ARRAY JOIN  arr2` 
2. Support multiple keyword of LEFT ARRAY JOIN with one column, each ARRAY JOIN only has one column. e.g `LEFT ARRAY JOIN  arr1 LEFT ARRAY JOIN  arr2` 
3. Support multiple keyword of ARRAY JOIN combined inner and left join with one column, each ARRAY JOIN only has one column. e.g `ARRAY JOIN  arr1 LEFT ARRAY JOIN arr2` 
4. Support multiple keyword of ARRAY JOIN with one column, and aliases. e.g. `ARRAY JOIN  arr1 as c1 ARRAY JOIN  arr2 as c2`
5. Support multiple keyword of ARRAY JOIN with multiple column, e.g. `ARRAY JOIN arr1 ARRAY JOIN arr2 , arr3` 
6. Support multiple keyword of ARRAY JOIN with nested struct, e.g. `ARRAY JOIN  nested1 ARRAY JOIN  nested2`


The goal  will splited to 2 stages.
Stage 1 , complete the No1, and No2. 
Stage 2 , complete the rest.

# Implementation
Parsing and AST  
Because we will not make any changes on existing ARRAY JOIN, so will create a sperate AST for the Multiple ARRAY Join, name it MultiArrayJoin.
```c++
struct ASTMultiArrayJoin : public IAST
{
    ASTPtr expression_list;
    ...
};
```

and a parser to handle the multiple array join:  

```c++
class ParserMultiArrayJoin : public IParserBase
{
protected:
    const char * getName() const override { return "multiple array join"; }
    bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
};

```
ARRAY JOIN clause is apart of select query,select query parsed by the ClickHouse has the follwoing structure:
inside the AST of select query (ASTSelectQuery), there's a child AST of table (ASTTablesInSelectQuery) , inside the AST of table, there may be more AST of ASTTablesInSelectQueryElement , each ASTTablesInSelectQueryElement may have a array join AST.

currently ClickHouse will raise an exception if there are more than on ASTTablesInSelectQueryElement containg array join.


class `ParserTablesInSelectQuery` is used to parse tables elements, will add `ParserMultiArrayJoin().parse()`  before return to apply multiple array joion:

```c++
bool ParserTablesInSelectQuery::parseImpl(Pos & pos, ASTPtr & node, Expected & expected)
{
    ....

    ParserMultiArrayJoin().parse(...);
    return true;
}
```
`ParserMultiArrayJoin` will check the children of ASTTablesInSelectQuery, if there's only one array join, then will do nothing.  


# Implementation
[getColumnsAfterArrayJoin]  
->[arrayJoinExpressionList](https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Interpreters/ExpressionAnalyzer.cpp.html#278)  
--> [getFirstArrayJoin](https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Parsers/ASTSelectQuery.cpp.html#339)  
->[addMultipleArrayJoinAction](https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Interpreters/ExpressionAnalyzer.cpp.html#285)  




[ExpressionAnalysisResult_constructor]  
->[SelectQueryExpressionAnalyzer::appendArrayJoin](https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Interpreters/ExpressionAnalyzer.cpp.html#1688)  
-->[arrayJoinExpressionList](https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Interpreters/ExpressionAnalyzer.cpp.html#937)  
-->[addMultipleArrayJoinAction](https://clickhouse.com/codebrowser/html_report/ClickHouse/src/Interpreters/ExpressionAnalyzer.cpp.html#945)  


# Test Plan
# Timeline