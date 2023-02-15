# Add Support Kusto Query Language (KQL) to ClickHouse

## Background

Add support for KQL (Kusto) described in the ticket:  https://github.ibm.com/ClickHouse/release/issues/40

- Currently will :  
Add KQL (Kusto) in front of ClickHouse  
Application uses KQL as front-end (instead of SQL)  

- Long term goal:  
    Proposal is to put the optimizer in ClickHouse – longer term feature  
    Further proposal is for ClickHouse to support KQL natively.


SO at current stage, will support to use KQL interface to get query result, the underneath process will use the query process of CLickHouse. ( the concept of KQL is different from SQL, which can be found in the [Azure_Data_Explorer_white_paper](https://azure.microsoft.com/mediahandler/files/resourcefiles/azure-data-explorer/Azure_Data_Explorer_white_paper.pdf) )   


 The requirement document can be found here:  
 https://github.ibm.com/ClickHouse/issue-repo/blob/master/docs/features/KQL/phase1/phase1-KQL-requirements.md
 
 The test plan can be found here:  
https://github.ibm.com/ClickHouse/issue-repo/blob/master/docs/features/KQL/phase1/phase1-KQL-testplan.md

## Process KQL in ClickHouse:

The KQL is a query with output , similar to the SQL select query. 

ClickHouse first parse the select query to ASTSelectQuery , then do further process:  
![KQL parse process analysis](../images/clickhouse_process_select.png)  

So for KQL, also parse to ASTSelectQuery first:  
![KQL parse process analysis](../images/clickhouse_process_KQL.png)  




- **Difference ClickHouse select query parse and KQL parse:**
    - **ClickHouse**
        1. ClickHouse SQL started with a `Select` keyword
        2. ClickHouse parse the the select with input according the keywords sequence in select statement. i.e, the Select statement must follow the predefined order.
            ```sql
            WITH expr_list
            SELECT  
            FROM  
            PREWHERE 
            WHERE  
            GROUP BY  
            WITH ROLLUP, CUBE or TOTALS
            HAVING  
            WINDOW  
            ORDER BY  
            LIMIT  
            SETTINGS  
            ```
    - **Kusto (KQL)**
        1. KQL start with a `table name`
        2. KQL statement is modeled as a flow of data from one tabular query operator to another, starting with some tabular data reference and concatenated by the pipe ( | ) character, it can be any order and can repeat any times as long as it can get from previous output, like:  
            ```kusto
            Customers
            | take 6 
            | sort by CityName
            | sort by  Education
            | take 3
            | where Education == "High School"
            | where CityName =="Ballard" 
            | project CityName,Education, Gender
            | project Education, Gender
            | where Gender =="M" 
            ```
        3. Conceptually, it takes the output of the previous operator (to the left of the pipe) and makes it an input of the next operator (to the right of the pipe). Most tabular operators are parameterized by scalar expressions that refer to the data fields of the incoming record stream and operate in the context of the “current record”. 


- **Parse KQL to ClickHouse Select Query**

    Some of the functionality in KQL exist in ClickHouse, parsing KQL will reuse them , the following table show the equivalent in ClickHouse:  

    - **KQL ClickHouse  equivalent** 
        |functionality| Syntax|ClickHouse SQL equivalent ||
        |---|---|---|---|
        |Tabular expression|Source \| Operator1 \| Operator2|ASTSelectQuery||
        |Filter|T \| **where** Predicate |WHERE|
        ||T \| **filter** Predicate|WHERE|
        |Limit returned results|T \| **take** | LIMIT||
        | |T \| **limit** | LIMIT||
        |Select Column|T \| **project** ColumnName [= Expression] [, ...]| Columns in select
        |Sort result|T \| **sort by** expression [asc \| desc] [nulls first \| nulls last] [, ...]|ORDER BY||
        | |T \| **order by** expression [asc \| desc] [nulls first \| nulls last] [, ...]|ORDER BY||
        |string equality operations|T \| where col **==** (expression)|==||
        | |T \| where col **!=** (expression)|!=||
        | |T \| where col **=~** (expression)|||
        ||T \| where col **!~** (expression)|||
        |Filter using a list |T \| where col **in** ( list of scalar expressions )|IN||
        |  |T \| where col **!in** ( list of scalar expressions )|NOT IN||
        |  |T \| where col **in~** ( list of scalar expressions )|||
        |  |T \| where col **!in~** ( list of scalar expressions )|||
        |Filter by string operations|T \| where col **contains** (expression)|ilike|
        ||T \| where col **contains_cs** (expression)|like|
        ||T \| where col **startswith** (expression)|||
        ||T \| where col **startswith_cs** (expression)|startsWith|
        ||T \| where col **endswith** (expression)||
        ||T \| where col **endswith_cs** (expression)|endsWith|
        |Aggregate by columns|T \| **summarize** [SummarizeParameters] [[Column =] Aggregation [, ...]] [by [Column =] GroupExpression [, ...]]|GROUP BY |
        |Aggregate by time intervals|**bin**(value,roundTo)|||
        |Basic aggregate functions|**avg** (Expr)|avg||
        ||**count** (Expr)|count||
        ||**min** (Expr)|min||
        ||**max** (Expr)|max||
        ||**sum** (Expr)|sum||
    


    - **Operations to build ASTs**  
        |KQL operation|ClickHouse AST|note|
        |---|---|---|
        |root  |ASTSelectQuery|
        |source(table)|ASTSelectQuery::Expression::TABLES|
        |where, filter|ASTSelectQuery::Expression::WHERE|
        |project|ASTSelectQuery::Expression::SELECT|missing `project` ->select *
        |order by, sort by|ASTSelectQuery::Expression::ORDER_BY|
        |summarize|ASTSelectQuery::Expression::GROUP_BY|
        |limit, take,|ASTSelectQuery::Expression::LIMIT_LENGTH|


## Parsers to process KQL
The root  parser will scan the query statements, call each sub parser according to the keywords in each section of the pipeline, each operation may occur many times in a query, so we define parser for each operation. 
|KQL operation|parser |
|---|---|
|root parser|ParserKQLQuery|
|source(table identifier)|ParserKQLTables|
|where, filter|ParserKQLFilter|
|project|ParserKQLColumns|
|order by, sort by|ParserKQLSort|
|summarize|ParserKQLSummarize|
|take, limit|ParserKQLLimit|

Each parsers will follow the ClickHouse format, they have similar definition, but have different parse logic.
- **Definition of parser classes :**
    1. ParserKQLQuery
        ```c++
        class ParserKQLQuery : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL Query"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```
    2. ParserKQLTables
        ```c++
        class ParserKQLTables : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL Table"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```
    3. ParserKQColumns
        ```c++
        class ParserKQLColumns : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL  Columns"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```
    4. ParserKQLLimit
        ```c++
        class ParserKQLLimit : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL Limit"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```
    5. ParserKQLFilter
        ```c++
        class ParserKQLFilter : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL Where Operation"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```

    5. ParserKQLSort
        ```c++
        class ParserKQLSort : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL Sort"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```
    7. ParserKQLSummarize
        ```c++
        class ParserKQLSummarize : public IParserBase
        {
        protected:
            const char * getName() const override { return "KQL Summarize"; }
            bool parseImpl(Pos & pos, ASTPtr & node, Expected & expected) override;
        };
        ```

- **Parsers processing logic:**
    1. ParserKQLQuery:  
        This is the parser to process the whole query statement, and generate a ASTSelectQuery in the ClickHouse pipeline  

    2. ParserKQLTables:  
        resolve the first `identifier` to table AST  
        dev test:
        ```kusto
            T  ==> pass
            T; ==> pass
            T| ==> fail
            T1 T2 ==>fail
        ```

    3. ParserKQColumns  
        resolve the `project` expressions to select_expression_list AST  
        narrow down the columns if there are multiple `project`, raise exception if cannot be narrowed ,e.g  
        ```kusto
        T | project a, b, c | project b,c  ==> project b, c

        T | project a, b, c | project b, c, d  ==> exception
        ```

    4. ParserKQLimit  
        resolve the `take` or `limit`  expressions to limit_by_expression_list AST
        use the smallest number of limit  
        ```kusto
        T | take 10 | take 20 ==> take 10
        ```        

    5. ParserKQLFilter:  
        resolve the `where` expressions to where_expression AST  
        combine multiple where_expression  
        ```Kusto
        T | where a > 5 | where b < 10  ==> where a > 5 and b < 10
        ```


    6. ParserKQLSort  
        resolve the `sort by` or `order by`  expressions to order_expression_list AST
        combine the sort statements according to the sequence in the query 
        ```kusto
        T | order by col1 | order by col2 ==> order by col1, col2
        ```
    7. ParserKQLSummarize  
        resolve the `summarize` expressions to group_expression_list AST  
        update select_expression_list if needed 
    


## The process of parsing

Token: 
the clickHouse does support single Pipe Mark, so we have enable it:  
add the token type:
```
    M(PipeMark)          /** Pipeline Mark for KQL |  */ \
```
src/Parsers/Lexer.cpp
```c++
change:
        case '|':
        {
            ++pos;
            if (pos < end && *pos == '|')
                return Token(TokenType::Concatenation, token_begin, ++pos);
            return Token(TokenType::ErrorSinglePipeMark, token_begin, pos);
        }
to:
        case '|':
        {
            ++pos;
            if (pos < end && *pos == '|')
                return Token(TokenType::Concatenation, token_begin, ++pos);
            return Token(TokenType::PipeMark, token_begin, pos);
        }

```

Originally,when parse a select query statement not started with `select` , the parsing will fail, and will return false to terminate the query process:

```c++
bool ParserUnionQueryElement::parseImpl(Pos & pos, ASTPtr & node, Expected & expected)
{
    if (!ParserSubquery().parse(pos, node, expected) && !ParserSelectQuery().parse(pos, node, expected))
        return false;

    if (const auto * ast_subquery = node->as<ASTSubquery>())
        node = ast_subquery->children.at(0);

    return true;
}
```

So we add the process of passing KQL after the failure of parsing ParserSelectQuery:
```c++
bool ParserUnionQueryElement::parseImpl(Pos & pos, ASTPtr & node, Expected & expected)
{
    if (!ParserSubquery().parse(pos, node, expected) && !ParserSelectQuery().parse(pos, node, expected))
    {
        if (!ParserKQLQuery().parse(pos, node, expected))
            return false;
    }

    if (const auto * ast_subquery = node->as<ASTSubquery>())
        node = ast_subquery->children.at(0);

    return true;
}
```

- **ParserKQLQuery::parseImpl :**    

    the process will return node as an ASTSelectQuery.
    Currently will use the instances of parsers and ASTs define above. the flow as the diagram below:

    ![KQL parse process analysis](../images/kql_process.png)  

- **Functions and operators:**  
    - for existing ClickHouse functions and operators, need a routine to convert from KQL ClickHouse(define later):
        ```c++
            void FuncConvert(...)   <-- name to be decided
            {

            }
        ```
        currently  only do :
        | From| To|
        |---|---|
        |**!in** |NOT IN||
        |**contains** |ilike|
        |**contains_cs** |like|
        |**startswith_cs**|startsWith|
        |**endswith_cs** |endsWith|
    - functions and operators not in ClickHouse :  
        will add the functions to ClickHouse later
- **parseImpl for other classes**  
`parseImpl(Pos & pos, ASTPtr & node, Expected & expected)` :  
`pos` is the started pos (0) of the query (expected)  
`node` is a AST node will be  added ASTSelectQuery  
`expected` is the string of each operation in KQL input (between 2 pipeline symbol `|` )


## Reference 
[Kusto Query Language reference](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/)  
[Azure_Data_Explorer_white_paper](https://azure.microsoft.com/mediahandler/files/resourcefiles/azure-data-explorer/Azure_Data_Explorer_white_paper.pdf)  
[Kusto Query Language Grammar](https://github.ibm.com/AIDBUTLR/cp4s-kql/blob/main/src/main/antlr4/com/ibm/si/qradar/cp4s/kql/KQL.g4)  
[ClickHouse grammar](https://github.com/ClickHouse/ClickHouse/blob/master/utils/antlr/ClickHouseParser.g4)

https://github.com/ClickHouse/ClickHouse/pull/36308/files#diff-ff8ad4aed4cf07fe29cb5344d2ab79bc24efd97d054aa112c3a05b5ab853cc44

https://github.com/ClickHouse/ClickHouse/pull/36308/files#diff-630eaed4584484f0c3900cc6c5d88514586a369aa7b635993abaf26b268eb5beR1