# Initial Features of KQL to support 

This is the initial features of a MVP version in ClickHouse

Basically,the idea is to  make the features list a little bit broader but shallower in the initial phase based on the higher impact described in the  [Minimal.KQL.Spec.for.Beta.GA.pdf](https://github.ibm.com/ClickHouse/release/files/941181/Minimal.KQL.Spec.for.Beta.GA.pdf). That will give us a more complete picture of the whole project.

So in this phase, will try to support the following features:

- [**Tabular expression statements**](#Tabular)
- [**Limit returned results**](#limit)  
- [**Select Column (basic project)**](#project)  
- [**sort, order**](#sort)  
- [**Perform string equality operations**](#stringequal)  
- [**Filter using a list of elements**](#in)  
- [**Filter using common string operations**](#string)   
    only support string data types using the contains , startswith , and endswith operators
- [**Aggregate by columns**](#aggragate)  
- [**Base aggregate functions**](#aggragatefunc)  
    only support avg, count ,min, max, sum  
- [**Aggregate by time intervals**](#timeinterval) 




 The design document can be found here:  
 https://github.ibm.com/ClickHouse/issue-repo/blob/master/docs/features/KQL/phase1/phase1-KQL-design.md

 The test plan can be found here:  
https://github.ibm.com/ClickHouse/issue-repo/blob/master/docs/features/KQL/phase1/phase1-KQL-testplan.md

## Tabular expression statements<a name="Tabular"></a> 
Queries always run in the context of a particular database in the cluster. They may also refer to data in another database, or even in another cluster.

- Syntax:  

    *Source* `|` *Operator1* `|` *Operator2* 

    - *Source* - tabular data sources (references to Kusto tables)
    - *Operator* - tabular data operators such as filters and projections

source data references (references to Kusto tables) 
one or more query operators applied in sequence,   
indicated visually by the use of a pipe character (|) to delimit operators.  

For example:
```sql
StormEvents 
| where State == 'FLORIDA' and StartTime > datetime(2000-01-01)
| count
```
Each filter prefixed by the pipe character | is an instance of an operator, with some parameters. The input to the operator is the table that is the result of the preceding pipeline. In most cases, any parameters are scalar expressions over the columns of the input. In a few cases, the parameters are the names of input columns, and in a few cases, the parameter is a second table. The result of a query is always a table, even if it only has one column and one row.


## Limit returned results<a name="limit"></a> 
- Requirements  
    - Return up to the specified number of rows, using the take t
able operator.
    - Must implement the limit table operator as an alias to take .
- Syntax:   
`take` *NumberOfRows*  
`limit` *NumberOfRows*
- Example
    ```kusto
    Traces
    | take 5
    ```

## Select Column (basic project)<a name="project"></a> 
- Requirements  
    - Select the columns to display in the output, in the specified 
order, using the project operator.  
    - Does not have to implement renaming columns. 
    - Does not have to implement supporting expressions to 
insert new columns

- Syntax:  
    *T* `| project` *ColumnName* [`=` *Expression*] [`,` ...]
- Example
    ```kusto
    events
    | project starttime, eventname
    ```
## sort, order<a name="sort"></a> 

- Requirements
    - Sort the output rows into order by one or more columns, using the `sort by` table operator.
    - Must implement the `order by` table operator as an alias to sort by .
    - Must allow specifying ascending and descending order using `asc` or `desc` .
    - If the direction is not specified, default to desc .
    - Must allow specifying the direction for each column separately.
    - Must allow specifying where to place nulls values; at the beginning using `nulls first` or at the end using `nulls last`
- Syntax:  
    *T* `| sort by` *expression* [`asc` | `desc`] [`nulls first` | `nulls last`] [`,` ...]  
    *T* `| order by` *expression* [`asc` | `desc`] [`nulls first` | `nulls last`] [`,` ...]
- Example 
    ```kusto
    Traces
    | where ActivityId == "479671d99b7b"
    | sort by Timestamp asc nulls first
    ```
## Perform string equality operations <a name="stringequal"></a> 
- Requirements  
    - Must allow equals, equals case-insensitive, not equals, and 
not equals case-insensitive operations on string data types, 
using == , =~ , != , and !~ operators.  
- Syntax   
    *T* `|` `where` *col* `=~` `(`*expression*`)`
- Description:  

    |Operator   |Description   |Case-Sensitive  |Example (yields `true`)  |
    |-----------|--------------|----------------|-------------------------|
    |`==`|Equals |Yes|`"aBc" == "aBc"`|
    |`!=`|Not equals |Yes |`"abc" != "ABC"`|
    |`=~` |Equals |No |`"abc" =~ "ABC"`|
    |`!~` |Not equals |No |`"aBc" !~ "xyz"`|


## Filter using a list of elements<a name="in"></a> 
- Requirements
    - Filter data on string or numerical data types using a comma separated list of elements, using the in operator.
    - Must implement the case insensitive in~ , negating !in , and negating case insensitive !in~ operators.
    - This feature item does not include supporting subselect

- Syntax

    *T* `|` `where` *col* `in~` `(` *list of scalar expressions* `)`  
    *T* `|` `where` *col* `in~` `(` *tabular expression* `)`
- Description:    

    |Operator   |Description   |Case-Sensitive  |Example (yields `true`)  |  
    |-----------|--------------|----------------|-------------------------|  
    |`in`  |Equals to one of the elements |Yes |`"abc" in ("123", "345", "abc")`|  
    |`!in` |Not equals to any of the elements |Yes | `"bca" !in ("123", "345", "abc")` |  
    |`in~`  |Equals to any of the elements |No | `"Abc" in~ ("123", "345", "abc")` |  
    |`!in~`  |Not equals to any of the elements |No | `"bCa" !in~ ("123", "345", "ABC")` |  
- Example 
    ```kusto
    events
    | where process in~ ("powershell.exe", "powershell_ise.exe")
    ```


## Filter using common string operations <a name="string"></a> 
- Requirements  
    - Must allow filtering data on string data types using the contains , startswith , and endswith operators.
    - Must support their case insensitive contains_cs , startswith_cs , and endswith_cs operators.

- Syntax  
    *T* `|` `where` *col* `contains` `(`*expression*`)`   
    *T* `|` `where` *col* `contains_cs` `(`*expression*`)`  

    *T* `|` `where` *col* `startswith` `(`*expression*`)`  
    *T* `|` `where` *col* `startswith_cs` `(`*expression*`)`  

    *T* `|` `where` *col* `endswith` `(`*expression*`)`  
    *T* `|` `where` *col* `endswith_cs` `(`*expression*`)`  

- Example:
    ```kusto
    StormEvents
        | summarize event_count=count() by State
        | where State contains "enn"
        | where event_count > 10
        | project State, event_count
        | render table
    ```

## Aggregate by columns <a name="aggragate"></a> 
- Requirements  
    - Must allow one or more columns.  
    -  Must allow specifying multiple aggregation functions (count, dcount, avg, etc.)

- Syntax  
*T* `| summarize` [*SummarizeParameters*]
      [[*Column* `=`] *Aggregation* [`,` ...]]
    [`by`
      [*Column* `=`] *GroupExpression* [`,` ...]]

- Example
    ```kusto

    events
    | where username == 'john' and eventname='logonfailed'
    | summarize count() by sourceip

    ```

## Base aggregate functions<a name="aggragatefunc"></a> 
- Requirements
    - Must allow the following aggregation functions:  
    avg, count ,min, max,sum, 

- Syntax  
    `avg` `(`*Expr*`)`  
    `count` `()`  
    `min` `(`*Expr*`)`  
    `max` `(`*Expr*`)`  
    `sum` `(`*Expr*`)`  

- Example 
    ```kusto
    Activities 
    | summarize Min = min(Timestamp), Max = max(Timestamp)
    ```

## Aggregate by time intervals<a name="timeinterval"></a> 
- Requirements  
    Allow aggregating by time intervals using the bin function to allow intuitive time-based analytics.
- Syntax  
    `bin(`*value*`,`*roundTo*`)`

- Example
    ```kusto
    events
    | where eventname == 'logonfailed'
    | summarize count() by bin(starttime, 1h)
    ```
