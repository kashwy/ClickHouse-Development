# IBM Kusto Query Language Support in ClickHouse
# Table of Contents   
[KQL-Detect](#KQL-Detect)   
[Tabular operators](#Tab_operators)  
[Data types](#data_types)  
[Scalar operators](#Tab_operators)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[String operators ](#String_operators)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[other operators ](#other_operators)  
[Scalar functions](#Scalar_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[IBM-KQL functions ](#IBM-KQL_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Binary functions ](#Binary_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Conversion functions ](#Conversion_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[DateTime/timespan functions ](#DateTime_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Dynamic/array functions ](#Dynamic_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Flow control functions ](#Flow_control_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Mathematical functions ](#Math_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Rounding functions ](#Rounding_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Conditional functions ](#Conditional_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[String functions ](#String_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[IPv4/IPv6 functions ](#IP_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[IPv4 text match functions ](#IPv4_macth_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[IPv6 text match functions ](#IPv6_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Type functions ](#Type_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Hash functions ](#Hash_functions)  
[Aggregation function](#Aggregation_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Binary functions ](#Binary_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Dynamic functions ](#AGG_Dynamic_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Row selector functions ](#Row_Selector_functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Statistical functions ](#Statistical_functions)  
[Description, deviation or limitations ](#Deviation_or_limitations)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[KQL-dialect setting  ](#Deviation_dialect)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[join operator ](#Deviation_join)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[make-series operator ](#Deviation_make-series)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[mv-expand operator ](#Deviation_mv-expand)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[summarize operator ](#Deviation_summarize)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[top-hitters operator ](#Deviation_top-hitters)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[dynamic data type ](#Deviation_dynamic)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[array_sort_desc() , array_sort_asc()](#Deviation_array_sort)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[range() function ](#Deviation_range)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[arg_max(),arg_min() function ](#Deviation_arg_max)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[take_any(),take_anyif() function ](#Deviation_take_any)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[hash() function ](#Deviation_hash)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[KQL sub-query ](#Deviation_subquery)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[kql() KQL table function](#Deviation_tablefunction)   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[hll family functions](#Deviation_hll)   


# KQL-Detect <a name="KQL-Detect"></a> 
|Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|set dialect='kusto'|only process kql|	v22.7.1.1-cli,Jun 24,2022|[Description](#Deviation_dialect)  |
|set dialect='clickhouse'|only process CH sql|	v22.7.1.1-cli,Jun 24,2022||
|kql() function|KQL table function|	v22.7.1.1-cli,Jun 24,2022|[Description](#Deviation_tablefunction) |

# Tabular operators <a name="Tab_operators"></a> 


|Operator Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|  [count operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/countoperator.md) |   | v22.8.6.73-clib, Oct 26,2022| |
|  [distinct operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/distinctoperator.md) |   |  v22.8.6.72-clib,	Oct 12,2022||
|  [extend operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extendoperator.md) |   |  v22.8.4.84-clib,	Sep 15,2022||
|  [getschema operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/getschemaoperator.md) |   |  23.2.4.14-1-stable-ibm,	Mar 18,2023||
|  [join operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/joinoperator.md) |   |v22.8.9.26-clib,	Nov 25,2022| [Shuffle join and summarize](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/shufflequery.md) are out of scope. [deviation or limitations](#Deviation_join)  |
|  [limit operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/limitoperator.md) |   |  v22.7.1.1-clib,    Jun 24,2022|
|  [lookup operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/lookupoperator.md) |   |  v22.8.9.26-clib,Nov 25,2022||
|  [make-series operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-seriesoperator.md) |   |  v22.8.1.4-clib,	Aug 31,2022|[deviation or limitations](#Deviation_make-series)|
|  [mv-expand operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/mvexpandoperator.md) |   |  v22.8.1.4-clib,Aug 31,2022|[deviation or limitations](#Deviation_mv-expand)
|  [order operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/orderoperator.md) |   | v22.7.1.1-clib	Jun 24,2022 |
|  [project operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/projectoperator.md) |   |  v22.7.1.1-clib,	Jun 24,2022|
|  [project-away operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/projectawayoperator.md) |   | v23.2.1.2538-stable-ibm, Feb28, 2023| |
|  [project-rename operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/projectrenameoperator.md) |   |v23.3.1.2825-lts-ibm, Apr.14, 2023| |
|  [print operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/printoperator.md) |   |  v22.8.1.1-clib,	Aug 3,2022||
|  [range operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/rangeoperator.md) |   |  v22.12.3.6-stable-ibm, Jan 26, 2023|[deviation or limitations](#Deviation_range)  |
|  [sort operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sortoperator.md) |   |  v22.7.1.1-clib	Jun 24,2022||
|  [summarize operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/summarizeoperator.md) |   | v22.7.1.1-clib,	Jun 24,2022|[Shuffle join and summarize](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/shufflequery.md) are out of scope. [deviation or limitations](#Deviation_summarize)  |
|  [take operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/takeoperator.md) |   | v22.7.1.1-clib, Jun 24,2022 |
|  [top operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/topoperator.md) |   |  v22.8.6.73-clib, Oct 26,2022|  |
|  [top-nested operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/topnestedoperator.md) |   |v22.12.3.6-stable-ibm,, Jan 26, 2023||
|  [top-hitters operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tophittersoperator.md) |   |  v22.8.6.73-clib, Oct 26,2022|[deviation or limitations](#Deviation_top-hitters)  |
|  [where operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/whereoperator.md) |   | v22.7.1.1-clib,	Jun 24,2022 |

# Data types <a name="data_types"></a> 

|DataType Name     |Best-fit ClickHouse type             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|  [bool](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/bool.md) |  [Bool](https://clickhouse.com/docs/en/sql-reference/data-types/boolean)  | v22.8.1.3-clib,	Aug 18,2022| |
|  [datetime](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/datetime.md) |  [DateTime64(9, 'UTC')](https://clickhouse.com/docs/en/sql-reference/data-types/datetime64)  | v22.8.1.3-clib,	Aug 18,2022| |
|  [decimal](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/decimal.md) |  [Decimal128](https://clickhouse.com/docs/en/sql-reference/data-types/decimal)  |v22.8.1.3-clib,	Aug 18,2022|  |
|  [dynamic](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/dynamic.md) |  N/A  |v22.8.1.3-clib,	Aug 18,2022| [deviation or limitations](#Deviation_dynamic)   |
|  [guid](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/guid.md) |  [UUID](https://clickhouse.com/docs/en/sql-reference/data-types/uuid)  | v22.8.1.3-clib,	Aug 18,2022| |
|  [int](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/int.md) |  [Int32](https://clickhouse.com/docs/en/sql-reference/data-types/int-uint)  | v22.8.1.3-clib,	Aug 18,2022| |
|  [long](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/long.md) |  [Int64](https://clickhouse.com/docs/en/sql-reference/data-types/int-uint)  |  v22.8.1.3-clib,	Aug 18,2022||
|  [real](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/real.md) |  [Float64](https://clickhouse.com/docs/en/sql-reference/data-types/float)  | v22.8.1.3-clib,	Aug 18,2022| |
|  [string](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/string.md) |  [String](https://clickhouse.com/docs/en/sql-reference/data-types/string)  | v22.8.1.3-clib,	Aug 18,2022| |
|  [timespan](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/./scalar-data-types/timespan.md) |  [IntervalNanosecond](https://clickhouse.com/docs/en/sql-reference/data-types/special-data-types/interval/)  |v22.8.1.3-clib,	Aug 18,2022|  |

# Scalar operators<a name="Tab_operators"></a> 

## String operators <a name="String_operators"></a>

The following abbreviations are used in this article:

* RHS = right hand side of the expression
* LHS = left hand side of the expression

Operators with an `_cs` suffix are case sensitive.

> [!NOTE]
> Case-insensitive operators are currently supported only for ASCII-text. For non-ASCII comparison, use the [tolower()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tolowerfunction.md) function.

|Operator   |Description   |Case-Sensitive  |Example (yields `true`)  | Available since | Comment|
|-----------|--------------|----------------|------------|------|-------|
|[`==`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/equals-cs-operator.md)|Equals |Yes|`"aBc" == "aBc"`|v22.7.1.1-clib	Jun 24,2022||
|[`!=`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-equals-cs-operator.md)|Not equals |Yes |`"abc" != "ABC"`|v22.7.1.1-clib	Jun 24,2022||
|[`=~`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/equals-operator.md) |Equals |No |`"abc" =~ "ABC"`|v22.12.3.6-stable-ibm,, Jan 26, 2023||
|[`!~`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-equals-operator.md) |Not equals |No |`"aBc" !~ "xyz"`|v22.12.3.6-stable-ibm,, Jan 26, 2023||
|[`contains`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/contains-operator.md) |RHS occurs as a subsequence of LHS |No |`"FabriKam" contains "BRik"`|v22.7.1.1-clib	Jun 24,2022||
|[`!contains`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-contains-operator.md) |RHS doesn't occur in LHS |No |`"Fabrikam" !contains "xyz"`|v22.7.1.1-clib	Jun 24,2022||
|[`contains_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/contains-cs-operator.md) |RHS occurs as a subsequence of LHS |Yes |`"FabriKam" contains_cs "Kam"`|v22.7.1.1-clib	Jun 24,2022||
|[`!contains_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-contains-cs-operator.md)   |RHS doesn't occur in LHS |Yes |`"Fabrikam" !contains_cs "Kam"`|v22.7.1.1-clib	Jun 24,2022||
|[`endswith`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endswith-operator.md) |RHS is a closing subsequence of LHS |No |`"Fabrikam" endswith "Kam"`|v22.7.1.1-clib	Jun 24,2022||
|[`!endswith`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-endswith-operator.md) |RHS isn't a closing subsequence of LHS |No |`"Fabrikam" !endswith "brik"`|v22.7.1.1-clib	Jun 24,2022||
|[`endswith_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endswith-cs-operator.md) |RHS is a closing subsequence of LHS |Yes |`"Fabrikam" endswith_cs "kam"`|v22.7.1.1-clib	Jun 24,2022||
|[`!endswith_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-endswith-cs-operator.md) |RHS isn't a closing subsequence of LHS |Yes |`"Fabrikam" !endswith_cs "brik"`|v22.7.1.1-clib	Jun 24,2022||
|[`has`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-operator.md) |Right-hand-side (RHS) is a whole term in left-hand-side (LHS) |No |`"North America" has "america"`|v22.7.1.1-clib	Jun 24,2022||
|[`!has`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-has-operator.md) |RHS isn't a full term in LHS |No |`"North America" !has "amer"`|v22.7.1.1-clib	Jun 24,2022||
|[`has_all`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-all-operator.md) |Same as `has` but works on all of the elements |No |`"North and South America" has_all("south", "north")`|v22.7.1.1-clib	Jun 24,2022||
|[`has_any`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-anyoperator.md) |Same as `has` but works on any of the elements |No |`"North America" has_any("south", "north")`|v22.7.1.1-clib	Jun 24,2022||
|[`has_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-cs-operator.md) |RHS is a whole term in LHS |Yes |`"North America" has_cs "America"`|v22.7.1.1-clib	Jun 24,2022||
|[`!has_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-has-cs-operator.md) |RHS isn't a full term in LHS |Yes |`"North America" !has_cs "amer"`|v22.7.1.1-clib	Jun 24,2022||
|[`hasprefix`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hasprefix-operator.md) |RHS is a term prefix in LHS |No |`"North America" hasprefix "ame"`|v22.7.1.1-clib	Jun 24,2022||
|[`!hasprefix`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hasprefix-operator.md) |RHS isn't a term prefix in LHS |No |`"North America" !hasprefix "mer"`|v22.7.1.1-clib	Jun 24,2022||
|[`hasprefix_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hasprefix-cs-operator.md) |RHS is a term prefix in LHS |Yes |`"North America" hasprefix_cs "Ame"`|v22.7.1.1-clib	Jun 24,2022||
|[`!hasprefix_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hasprefix-cs-operator.md) |RHS isn't a term prefix in LHS |Yes |`"North America" !hasprefix_cs "CA"`|v22.7.1.1-clib	Jun 24,2022||
|[`hassuffix`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hassuffix-operator.md) |RHS is a term suffix in LHS |No |`"North America" hassuffix "ica"`|v22.7.1.1-clib	Jun 24,2022||
|[`!hassuffix`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hassuffix-operator.md) |RHS isn't a term suffix in LHS |No |`"North America" !hassuffix "americ"`|v22.7.1.1-clib	Jun 24,2022||
|[`hassuffix_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hassuffix-cs-operator.md)  |RHS is a term suffix in LHS |Yes |`"North America" hassuffix_cs "ica"`|v22.7.1.1-clib	Jun 24,2022||
|[`!hassuffix_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hassuffix-cs-operator.md) |RHS isn't a term suffix in LHS |Yes |`"North America" !hassuffix_cs "icA"`|v22.7.1.1-clib	Jun 24,2022||
|[`in`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/in-cs-operator.md) |Equals to any of the elements |Yes |`"abc" in ("123", "345", "abc")`|v22.7.1.1-clib	Jun 24,2022||
|[`!in`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-in-cs-operator.md) |Not equals to any of the elements |Yes | `"bca" !in ("123", "345", "abc")` |v22.7.1.1-clib	Jun 24,2022||
|[`in~`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/inoperator.md) |Equals to any of the elements |No | `"Abc" in~ ("123", "345", "abc")` |v22.12.3.6-stable-ibm,, Jan 26, 2023||
|[`!in~`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-in-operator.md) |Not equals to any of the elements |No | `"bCa" !in~ ("123", "345", "ABC")` |v22.12.3.6-stable-ibm,, Jan 26, 2023||
|[`matches regex`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/regex-operator.md) |LHS contains a match for RHS |Yes |`"Fabrikam" matches regex "b.*k"`|v22.7.1.1-clib	Jun 24,2022||
|[`startswith`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startswith-operator.md) |RHS is an initial subsequence of LHS |No |`"Fabrikam" startswith "fab"`|v22.7.1.1-clib	Jun 24,2022||
|[`!startswith`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-startswith-operator.md) |RHS isn't an initial subsequence of LHS |No |`"Fabrikam" !startswith "kam"`|v22.7.1.1-clib	Jun 24,2022||
|[`startswith_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startswith-cs-operator.md)  |RHS is an initial subsequence of LHS |Yes |`"Fabrikam" startswith_cs "Fab"`|v22.7.1.1-clib	Jun 24,2022||
|[`!startswith_cs`](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-startswith-cs-operator.md) |RHS isn't an initial subsequence of LHS |Yes |`"Fabrikam" !startswith_cs "fab"`|v22.7.1.1-clib	Jun 24,2022||

## other operators <a name="other_operators"></a>
|Function Name     |Description    | Available since | Comment|
|-------------------------|--------------------------|---------|---------------------|
|  [between operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/betweenoperator.md) |  |   v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|  [!between operator](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/notbetweenoperator.md) |  |  23.2.4.14-1-stable-ibm,	Mar 18,2023| |
|  [in/!in operators](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/inoperator.md) | subquery, set | v22.7.1.2-clib	Jul,20,2022| (subquery need to be wraped with bracket inside bracket) like: `Customers \| where Age in ((Customers\|project Age\|where Age < 30))`| 
# Scalar functions <a name="Scalar_functions"></a>

## IBM-KQL functions <a name="IBM-KQL_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[lookup()]()|Map calls directly to dictGet(), dictGetOrDefault() depending on parameters.|v23.2.1.2538-stable-ibm, Feb 28, 2023|| 


## Binary functions <a name="Binary_functions"></a>

|Function Name     |Description    | Available since | Comment|
|-------------------------|--------------------------|---------|---------------------|
|[binary_and()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-andfunction.md)|Returns a result of the bitwise and operation between two values.|v22.8.1.3-clib,	Aug 18,2022||
|[binary_not()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-notfunction.md)|Returns a bitwise negation of the input value.|v22.8.1.3-clib,	Aug 18,2022||
|[binary_or()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-orfunction.md)|Returns a result of the bitwise or operation of the two values.|v22.8.1.3-clib,	Aug 18,2022||
|[binary_shift_left()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-shift-leftfunction.md)|Returns binary shift left operation on a pair of numbers: a << n.|v22.8.1.3-clib,	Aug 18,2022||
|[binary_shift_right()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-shift-rightfunction.md)|Returns binary shift right operation on a pair of numbers: a >> n.|v22.8.1.3-clib,	Aug 18,2022||
|[binary_xor()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-xorfunction.md)|Returns a result of the bitwise xor operation of the two values.|v22.8.1.3-clib,	Aug 18,2022||
|[bitset_count_ones()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/bitset-count-onesfunction.md)|Returns the number of set bits in the binary representation of a number.|v22.8.1.3-clib,	Aug 18,2022||

## Conversion functions <a name="Conversion_functions"></a>

|Function Name     |Description    |Available since | Comment|
|-------------------------|-----------------------------------|------|---------------|
|[tobool()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/toboolfunction.md)|Converts input to boolean (signed 8-bit) representation.|v22.8.1.3-clib,	Aug 18,2022||
|[todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todatetimefunction.md)|Converts input to datetime scalar.|v22.8.1.3-clib,	Aug 18,2022||
|[todouble()/toreal()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todoublefunction.md)|Converts the input to a value of type real. (todouble() and toreal() are synonyms.)|v22.8.1.3-clib,	Aug 18,2022||
|[toint()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tointfunction.md)|Converts the input to an integer value (signed 32-bit) number representation.|v22.8.1.3-clib,	Aug 18,2022||
|[tolong()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tolongfunction.md)|Converts the input value to a long (signed 64-bit) number representation.|v22.8.1.3-clib,	Aug 18,2022||
|[todecimal()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todecimalfunction.md)|Converts the input to a decimal number representation.|v22.8.1.3-clib,	Aug 18,2022||
|[tostring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tostringfunction.md)|Converts input to a string representation.|v22.8.1.3-clib,	Aug 18,2022||
|[totimespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/totimespanfunction.md)|Converts input to timespan scalar.|v22.8.1.4-clib,	Aug 31,2022||

## DateTime/timespan functions <a name="DateTime_functions"></a>

|Function Name     |Description            |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[ago()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/agofunction.md)|Subtracts the given timespan from the current UTC clock time.|v22.8.1.4-clib, Aug 31,2022||
|[datetime_add()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/datetime-addfunction.md)|Calculates a new datetime from a specified datepart multiplied by a specified amount, added to a specified datetime.|v22.8.1.3-clib,	Aug 18,2022||
|[datetime_diff()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/datetime-difffunction.md)|Returns the end of the year containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[datetime_part()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/datetime-partfunction.md)|Extracts the requested date part as an integer value.|v22.8.1.3-clib,	Aug 18,2022||
|[dayofmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dayofmonthfunction.md)|Returns the integer number representing the day number of the given month.|v22.8.1.3-clib,	Aug 18,2022||
|[dayofweek()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dayofweekfunction.md)|Returns the integer number of days since the preceding Sunday, as a timespan.|v22.8.1.3-clib,	Aug 18,2022||
|[dayofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dayofyearfunction.md)|Returns the integer number represents the day number of the given year.|v22.8.1.3-clib,	Aug 18,2022||
|[endofday()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofdayfunction.md)|Returns the end of the day containing the date, shifted by an offset, if provided.|v22.8.1.4-clib,	Aug 31,2022||
|[endofmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofmonthfunction.md)|Returns the end of the month containing the date, shifted by an offset, if provided.|v22.8.1.4-clib,	Aug 31,2022||
|[endofweek()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofweekfunction.md)|Returns the end of the week containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[endofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofyearfunction.md)|Returns the end of the year containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[format_datetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-datetimefunction.md)|Formats a datetime parameter based on the format pattern parameter.|v22.8.1.3-clib,	Aug 18,2022||
|[format_timespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-timespanfunction.md)|Formats a format-timespan parameter based on the format pattern parameter.|v22.8.1.3-clib,	Aug 18,2022||
|[getmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/getmonthfunction.md)|Get the month number (1-12) from a datetime.|v22.8.1.3-clib,	Aug 18,2022||
|[getyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/getyearfunction.md)|Returns the year part of the datetime argument.|v22.8.1.3-clib,	Aug 18,2022||
|[hourofday()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hourofdayfunction.md)|Returns the integer number representing the hour number of the given date.|v22.8.1.3-clib,	Aug 18,2022||
|[make_datetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-datetimefunction.md)|Creates a datetime scalar value from the specified date and time.|v22.8.8.4-clib	Nov 18,2022
|[make_timespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-timespanfunction.md)|Creates a timespan scalar value from the specified time period.|v22.8.1.4-clib,	Aug 31,2022||
|[monthofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/monthofyearfunction.md)|Returns the integer number represents the month number of the given year.|v22.8.1.3-clib,	Aug 18,2022||
|[now()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/nowfunction.md)|Returns the current UTC clock time, optionally offset by a given timespan.|v22.8.1.3-clib,	Aug 18,2022||
|[startofday()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofdayfunction.md)|Returns the start of the day containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[startofmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofmonthfunction.md)|Returns the start of the month containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[startofweek()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofweekfunction.md)|Returns the start of the week containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[startofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofyearfunction.md)|Returns the start of the year containing the date, shifted by an offset, if provided.|v22.8.1.3-clib,	Aug 18,2022||
|[todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todatetimefunction.md)|Converts input to datetime scalar.|v22.8.1.4-clib,	Aug 31,2022||
|[totimespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/totimespanfunction.md)|Converts input to timespan scalar.|v22.8.1.4-clib,	Aug 31,2022||
|[unixtime_microseconds_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-microseconds-todatetimefunction.md)|Converts unix-epoch microseconds to UTC datetime.|v22.8.1.4-clib,	Aug 31,2022||
|[unixtime_milliseconds_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-milliseconds-todatetimefunction.md)|Converts unix-epoch milliseconds to UTC datetime.|v22.8.1.4-clib,	Aug 31,2022||
|[unixtime_nanoseconds_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-nanoseconds-todatetimefunction.md)|Converts unix-epoch nanoseconds to UTC datetime.|v22.8.1.4-clib,	Aug 31,2022||
|[unixtime_seconds_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-seconds-todatetimefunction.md)|Converts unix-epoch seconds to UTC datetime.|v22.8.1.3-clib,	Aug 18,2022||
|[weekofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/weekofyearfunction.md)|Returns an integer representing the week number.|v22.8.1.3-clib,	Aug 18,2022||

## Dynamic/array functions <a name="Dynamic_functions"></a>

|Function Name     |Description            |Available since | Comment|
|-------------------------|--------------------------|------------|-----------------|
|[array_concat()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayconcatfunction.md)|Concatenates a number of dynamic arrays to a single array.|v22.8.1.4-clib,	Aug 31,2022||
|[array_iif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayifffunction.md)|Applies element-wise iif function on arrays.|v22.8.1.4-clib,	Aug 31,2022||
|[array_index_of()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayindexoffunction.md)|Searches the array for the specified item, and returns its position.|v22.8.1.4-clib,	Aug 31,2022||
|[array_length()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraylengthfunction.md)|Calculates the number of elements in a dynamic array.|v22.8.1.3-clib	Aug 18,2022||
|[array_reverse()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array-reverse-function.md)|Reverses the order of the elements in a dynamic array.|v22.8.4.84-clib, Sep 15,2022||
|[array_rotate_left()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_rotate_leftfunction.md)|Rotates values inside a dynamic array to the left.|v22.8.4.84-clib, Sep 15,2022||
|[array_rotate_right()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_rotate_rightfunction.md)|Rotates values inside a dynamic array to the right.|v22.8.4.84-clib, Sep 15,2022||
|[array_shift_left()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_shift_leftfunction.md)|Shifts values inside a dynamic array to the left.|v22.8.4.84-clib, Sep 15,2022||
|[array_shift_right()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_shift_rightfunction.md)|Shifts values inside a dynamic array to the right.|v22.8.4.84-clib, Sep 15,2022||
|[array_slice()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayslicefunction.md)|Extracts a slice of a dynamic array.|v22.8.1.4-clib,	Aug 31,2022
|[array_sort_asc()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraysortascfunction.md)|Sorts a collection of arrays in ascending order.|v22.8.1.4-clib,	Aug 31,2022|[deviation or limitations](#Deviation_array_sort)  
|[array_sort_desc()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraysortdescfunction.md)|Sorts a collection of arrays in descending order.|v22.8.1.4-clib	Aug 31,2022|[deviation or limitations](#Deviation_array_sort)  
|[array_split()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraysplitfunction.md)|Builds an array of arrays split from the input array.|v22.8.1.4-clib,	Aug 31,2022
|[array_sum()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array-sum-function.md)|Calculates the sum of a dynamic array.|v22.8.1.3-clib,	Aug 18,2022
|[jaccard_index()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/jaccard-index-function.md)|Computes the [Jaccard index](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/https://en.wikipedia.org/wiki/Jaccard_index) of two sets.|v22.8.4.84-clib,	Sep 15,2022||
|[repeat()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/repeatfunction.md)|Generates a dynamic array holding a series of equal values.|v22.8.4.84-clib, Sep 15,2022||
|[set_difference()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/setdifferencefunction.md)|Returns an array of the set of all distinct values that are in the first array but aren't in other arrays.|v22.8.4.84-clib, Sep 15,2022||
|[set_has_element()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sethaselementfunction.md)|Determines whether the specified array contains the specified element.|v22.8.4.84-clib, Sep 15,2022||
|[set_intersect()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/setintersectfunction.md)|Returns an array of the set of all distinct values that are in all arrays.|v22.8.4.84-clib, Sep 15,2022||
|[set_union()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/setunionfunction.md)|Returns an array of the set of all distinct values that are in any of provided arrays.|v22.8.4.84-clib, Sep 15,2022||
|[zip()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/zipfunction.md)|The zip function accepts any number of dynamic arrays. Returns an array whose elements are each an array with the elements of the input arrays of the same index.|v22.8.4.84-clib, Sep 15,2022||



## Flow control functions <a name="Flow_control_functions"></a>

|Function Name            |Description              |Available since | Comment|
|-------------------------|--------------------------|-------------|-----------------|
|[toscalar()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/toscalarfunction.md)|Returns a scalar constant value of the evaluated expression.| v23.2.4.14-1-stable-ibm, Mar 18, 2023||

## Mathematical functions <a name="Math_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[abs()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/abs-function.md)|Calculates the absolute value of the input.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[acos()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/acosfunction.md)|Returns the angle whose cosine is the specified number (the inverse operation of cos()).|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[asin()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/asinfunction.md)|Returns the angle whose sine is the specified number (the inverse operation of sin()).|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[atan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/atanfunction.md)|Returns the angle whose tangent is the specified number (the inverse operation of tan()).|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[atan2()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/atan2function.md)|Calculates the angle, in radians, between the positive x-axis and the ray from the origin to the point (y, x).|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[cos()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/cosfunction.md)|Returns the cosine function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[cot()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/cotfunction.md)|Calculates the trigonometric cotangent of the specified angle, in radians.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[degrees()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/degreesfunction.md)|Converts angle value in radians into value in degrees, using formula degrees = (180 / PI) * angle-in-radians.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[exp()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/exp-function.md)|The base-e exponential function of x, which is e raised to the power x: e^x.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[exp10()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/exp10-function.md)|The base-10 exponential function of x, which is 10 raised to the power x: 10^x.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[exp2()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/exp2-function.md)|The base-2 exponential function of x, which is 2 raised to the power x: 2^x.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[gamma()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/gammafunction.md)|Computes gamma function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[isfinite()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isfinitefunction.md)|Returns whether input is a finite value (isn't infinite or NaN).|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[isinf()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isinffunction.md)|Returns whether input is an infinite (positive or negative) value.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[isnan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnanfunction.md)|Returns whether input is Not-a-Number (NaN) value.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[log()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/log-function.md)|Returns the natural logarithm function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[log10()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/log10-function.md)|Returns the common (base-10) logarithm function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[log2()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/log2-function.md)|Returns the base-2 logarithm function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[loggamma()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/loggammafunction.md)|Computes log of absolute value of the gamma function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[not()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/notfunction.md)|Reverses the value of its bool argument.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[pi()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/pifunction.md)|Returns the constant value of Pi (π).|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[pow()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/powfunction.md)|Returns a result of raising to power.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[radians()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/radiansfunction.md)|Converts angle value in degrees into value in radians, using formula radians = (PI / 180) * angle-in-degrees.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[rand()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/randfunction.md)|Returns a random number.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[range()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/rangefunction.md)|Generates a dynamic array holding a series of equally spaced values.|v23.2.1.2538-stable-ibm, Feb 28, 2023|[deviation or limitations](#Deviation_range)  |
|[round()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/roundfunction.md)|Returns the rounded source to the specified precision.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[sign()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/signfunction.md)|Sign of a numeric expression.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[sin()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sinfunction.md)|Returns the sine function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[sqrt()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sqrtfunction.md)|Returns the square root function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[tan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tanfunction.md)|Returns the tangent function.|v23.2.1.2538-stable-ibm, Feb 28, 2023||



## Rounding functions <a name="Rounding_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[bin()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binfunction.md)|Rounds values down to an integer multiple of a given bin size.|v22.8.1.4-clib,Aug 31,2022||
|[bin_at()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binatfunction.md)|Rounds values down to a fixed-size "bin", with control over the bin's starting point. (See also bin function.)|v22.8.1.3-clib,Aug 18,2022||
|[ceiling()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ceilingfunction.md)|Calculates the smallest integer greater than, or equal to, the specified numeric expression.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[floor()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/floorfunction.md)|Rounds values down to an integer multiple of a given bin size.|v23.2.1.2538-stable-ibm, Feb 28, 2023||

## Conditional functions <a name="Conditional_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[case()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/casefunction.md)|Evaluates a list of predicates and returns the first result expression whose predicate is satisfied.|v22.8.8.4-clib, Nov 10,2022||
|[iif()/iff()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/iiffunction.md)|Evaluates the first argument (the predicate), and returns the value of either the second or third arguments, depending on whether the predicate evaluated to true (second) or false (third).|v22.12.3.6-clib,	Jan 26,2023||
|[max_of()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/max-offunction.md)|Returns the maximum value of several evaluated numeric expressions.|v23.2.1.2538-stable-ibm, Feb 28, 2023||
|[min_of()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/min-offunction.md)|Returns the minimum value of several evaluated numeric expressions.|v23.2.1.2538-stable-ibm, Feb 28, 2023||



## String functions <a name="String_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[base64_encode_tostring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64_encode_tostringfunction.md)|Encodes a string as base64 string.|v22.7.1.1-clib,Jun 24,2022||
|[base64_encode_fromguid()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64-encode-fromguid-function.md)|Encodes a GUID as base64 string.|v22.8.1.3-clib	Aug 18,2022||
|[base64_decode_tostring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64_decode_tostringfunction.md)|Decodes a base64 string to a UTF-8 string.|v22.8.1.3-clib,Aug 18,2022||
|[base64_decode_toarray()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64_decode_toarrayfunction.md)|Decodes a base64 string to an array of long values.|v22.8.1.3-clib,	Aug 18,2022||
|[base64_decode_toguid()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64-decode-toguid-function.md)|Decodes a base64 string to a GUID.|v22.8.1.3-clib,	Aug 18,2022||
|[countof()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/countoffunction.md)|Counts occurrences of a substring in a string. Plain string matches may overlap; regex matches don't.|v22.7.1.2-clib,Jul,20,2022||
|[extract()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractfunction.md)|Get a match for a regular expression from a text string.|v22.7.1.2-clib,Jul,20,2022||
|[extract_all()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractallfunction.md)|Get all matches for a regular expression from a text string.|v22.7.1.2-clib,Jul,20,2022||
|[extractjson()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractjsonfunction.md)|Get a specified element out of a JSON text using a path expression.|v22.8.6.72-clib,Oct 12,2022||
|[has_any_index()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-any-index-function.md)|Searches the string for items specified in the array and returns the position of the first item found in the string.|v22.8.1.3-clib,	Aug 18,2022||
|[indexof()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/indexoffunction.md)|Function reports the zero-based index of the first occurrence of a specified string within input string.|v22.7.1.2-clib,Jul,20,2022||
|[indexof_regex()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/indexofregexfunction.md)|Returns the zero-based index of the first occurrence of a specified lookup regular expression within the input string|v23.3.xx, Mar 18,2022||
|[isascii()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isascii.md)|Returns true if the argument is an empty string or is null.|v23.3.1.2825-lts-ibm,	Apr 14,2023||
|[isempty()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isemptyfunction.md)| check if the argument is a valid ascii string.|v22.7.1.1-clib,	Jun 24,2022||
|[isnotempty()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnotemptyfunction.md)|Returns true if the argument isn't an empty string or a null.|v22.7.1.1-clib	Jun 24,2022
|[isnotnull()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnotnullfunction.md)|Returns true if the argument is not null.|v22.7.1.1-clib,	Jun 24,2022||
|[isutf8()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isutf8.md)|check if the argument is a valid utf8 string..|v23.3.1.2825-lts-ibm,	Apr 14,2023||
|[isnull()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnullfunction.md)|Evaluates its sole argument and returns a bool value indicating if the argument evaluates to a null value.|v22.7.1.1-clib,	Jun 24,2022||
|[make_string()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makestringfunction.md)|Returns the string generated by the Unicode characters.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[new_guid()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/newguidfunction.md)|Returns a random GUID (Globally Unique Identifier).|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[parse_command_line()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-command-line.md)|Parses a Unicode command line string and returns an array of the command line arguments.|v22.8.6.72-clib,	Oct 12,2022||
|[parse_csv()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parsecsvfunction.md)|Splits a given string representing comma-separated values and returns a string array with these values.|v22.8.6.72-clib,	Oct 12,2022||
|[parse_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv4function.md)|Converts input to long (signed 64-bit) number representation.|v22.7.1.2-clib,	Jul,20,2022||
|[parse_ipv4_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv4-maskfunction.md)|Converts input string and IP-prefix mask to long (signed 64-bit) number representation.|v22.7.1.2-clib,	Jul,20,2022||
|[parse_ipv6()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv6function.md)|Converts IPv6 or IPv4 string to a canonical IPv6 string representation.|v22.7.1.2-clib,	Jul,20,2022|
|[parse_ipv6_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv6-maskfunction.md)|Converts IPv6 or IPv4 string and netmask to a canonical IPv6 string representation.|v22.8.1.3-clib,	Aug 18,2022||
|[parse_json()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parsejsonfunction.md)|Interprets a string as a JSON value) and returns the value as dynamic.|v22.8.6.72-clib,	Oct 12,2022||
|[parse_url()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parseurlfunction.md)|Parses an absolute URL string and returns a dynamic object contains all parts of the URL.|v22.8.1.1-clib,	Aug 3,2022||
|[parse_urlquery()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parseurlqueryfunction.md)|Parses a url query string and returns a dynamic object contains the Query parameters.|v22.8.1.1-clib,	Aug 3,2022||
|[parse_version()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-versionfunction.md)|Converts input string representation of version to a comparable decimal number.|	v22.8.6.72-clib,	Oct 12,2022||
|[replace_regex()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/replace-regex-function.md)|Replace all regex matches with another string.|v22.8.1.3-clib,	Aug 18,2022||
|[reverse()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/reversefunction.md)|Function makes reverse of input string.|	v22.8.6.72-clib,	Oct 12,2022||
|[split()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/splitfunction.md)|Splits a given string according to a given delimiter and returns a string array with the contained substrings.|v22.7.1.2-clib,	Jul,20,2022||
|[strcat()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strcatfunction.md)|Concatenates between 1 and 64 arguments.|v22.7.1.1-clib,	Jun 24,2022||
|[strcat_delim()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strcat-delimfunction.md)|Concatenates between 2 and 64 arguments, with delimiter, provided as first argument.|v22.7.1.2-clib,	Jul,20,2022||
|[strcmp()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strcmpfunction.md)|Compares two strings.|v22.8.1.1-clib,	Aug 3,2022||
|[strlen()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strlenfunction.md)|Returns the length, in characters, of the input string.|v22.7.1.1-clib,	Jun 24,2022||
|[strrep()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strrepfunction.md)|Repeats given string provided number of times (default - 1).|v22.7.1.1-clib,	Jun 24,2022||
|[strrep()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strrepfunction.md)|Repeats given string provided number of times (default - 1).|v22.7.1.1-clib,	Jun 24,2022||
|[strrep()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strrepfunction.md)|Repeats given string provided number of times (default - 1).|v22.7.1.1-clib,	Jun 24,2022||
|[substring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/substringfunction.md)|Extracts a substring from a source string starting from some index to the end of the string.|v22.7.1.1-clib,	Jun 24,2022||
|[string_size()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/stringsizefunction.md)|Returns the size, in bytes, of the input string.|v23.2.4.14-1-stable-ibm,	Mar 18, 2023||
|[strrep()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strrepfunction.md)|Repeats given string provided number of times (default - 1).|v22.7.1.1-clib,	Jun 24,2022||
|[to_utf8()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/toutf8function.md)|Returns a dynamic array of the unicode characters of an input string (the inverse operation of make_string)|v23.2.4.14-1-stable-ibm,	Mar 18, 2023||
|[tolower()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tolowerfunction.md)|Converts the input string to lower case.|v22.7.1.1-clib,	Jun 24,2022||
|[toupper()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/toupperfunction.md)|Converts a string to upper case.|v22.7.1.1-clib,	Jun 24,2022||
|[translate()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/translatefunction.md)|Replaces a set of characters ('searchList') with another set of characters ('replacementList') in a given a string.|v22.8.1.3-clib,	Aug 18,2022||
|[trim()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/trimfunction.md)|Removes all leading and trailing matches of the specified regular expression.|v22.8.1.3-clib,	Aug 18,2022||
|[trim_end()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/trimendfunction.md)|Removes trailing match of the specified regular expression.|v22.8.1.3-clib,	Aug 18,2022
|[trim_start()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/trimstartfunction.md)|Removes leading match of the specified regular expression.|v22.8.1.3-clib,	Aug 18,2022
|[url_decode()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/urldecodefunction.md)|The function converts encoded URL into a regular URL representation.|v22.7.1.1-clib,	Jun 24,2022||
|[url_encode()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/urlencodefunction.md)|The function converts characters of the input URL into a format that can be transmitted over the Internet.|v22.7.1.1-clib,	Jun 24,2022||

## IPv4/IPv6 functions <a name="IP_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[ipv4_compare()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-comparefunction.md)|Compares two IPv4 strings.|v22.8.1.3-clib,	Aug 18,2022||
|[ipv4_is_in_range()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-is-in-range-function.md)|Checks if IPv4 string address is in IPv4-prefix notation range.|v22.7.1.2-clib,	Jul,20,2022||
|[ipv4_is_match()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-is-matchfunction.md)|Matches two IPv4 strings.|v22.8.1.3-clib,	Aug 18,2022||
|[ipv4_is_private()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-is-privatefunction.md)|Checks if IPv4 string address belongs to a set of private network IPs.|v22.7.1.2-clib,	Jul,20,2022||
|[ipv4_netmask_suffix](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-netmask-suffix-function.md)|Returns the value of the IPv4 netmask suffix from IPv4 string address.|v22.7.1.2-clib,	Jul,20,2022||
|[parse_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv4function.md)|Converts input string to long (signed 64-bit) number representation.|v22.7.1.2-clib,	Jul,20,2022||
|[parse_ipv4_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv4-maskfunction.md)|Converts input string and IP-prefix mask to long (signed 64-bit) number representation.|v22.8.1.3-clib,	Aug 18,2022||
|[ipv6_compare()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv6-comparefunction.md)|Compares two IPv4 or IPv6 strings.|v22.8.1.3-clib,	Aug 18,2022||
|[ipv6_is_match()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv6-is-matchfunction.md)|Matches two IPv4 or IPv6 strings.|v22.7.1.2-clib,	Jul,20,2022||
|[parse_ipv6()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv6function.md)|Converts IPv6 or IPv4 string to a canonical IPv6 string representation.|v22.7.1.2-clib,	Jul,20,2022||
|[parse_ipv6_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv6-maskfunction.md)|Converts IPv6 or IPv4 string and netmask to a canonical IPv6 string representation.|v22.8.1.3-clib,	Aug 18,2022||
|[format_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-ipv4-function.md)|Parses input with a netmask and returns string representing IPv4 address.|v22.8.1.3-clib,	Aug 18,2022||
|[format_ipv4_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-ipv4-mask-function.md)|Parses input with a netmask and returns string representing IPv4 address as CIDR notation.|v22.8.1.3-clib,	Aug 18,2022||


## IPv4 text match functions <a name="IPv4_macth_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[has_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-ipv4-function.md)|Searches for an IPv4 address in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[has_ipv4_prefix()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-ipv4-prefix-function.md)|Searches for an IPv4 address or prefix in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[has_any_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-any-ipv4-function.md)|Searches for any of the specified IPv4 addresses in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[has_any_ipv4_prefix()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-any-ipv4-prefix-function.md)|Searches for any of the specified IPv4 addresses or prefixes in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||

## IPv6 text match functions <a name="IPv6_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[has_ipv6()]()|Searches for an IPv6 address in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[has_ipv6_prefix()]()|Searches for an IPv6 address or prefix in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[has_any_ipv6()]()|Searches for any of the specified IPv6 addresses in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||
|[has_any_ipv6_prefix()]()|Searches for any of the specified IPv6 addresses or prefixes in a text.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||

## Type functions <a name="Type_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[gettype()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/gettypefunction.md)|Returns the runtime type of its single argument.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||




## Hash functions <a name="Hash_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
|[hash()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hashfunction.md)|Returns a hash value for the input value.|v23.2.4.14-1-stable-ibm,	Mar 18,2023|[deviation or limitations](#Deviation_hash)  |
|[hash_sha256()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sha256hashfunction.md)|Returns a SHA256 hash value for the input value.|v23.2.4.14-1-stable-ibm,	Mar 18,2023||




# Aggregation function  <a name="Aggregation_functions"></a>



## Binary functions <a name="Binary_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
| [binary_all_and()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-all-and-aggfunction.md) | Returns aggregated value using the binary AND of the group. |v22.8.1.1-clib,	Aug 3,2022||
| [binary_all_or()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-all-or-aggfunction.md) | Returns aggregated value using the binary OR of the group. |v22.8.1.1-clib,	Aug 3,2022||
| [binary_all_xor()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-all-xor-aggfunction.md) | Returns aggregated value using the binary XOR of the group. |v22.8.1.1-clib,	Aug 3,2022||

## Dynamic functions <a name="AGG_Dynamic_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
| [make_list()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makelist-aggfunction.md), [make_list_if()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makelistif-aggfunction.md) | Returns a list of all the values within the group without/with a predicate. |	v22.8.1.1-clib,	Aug 3,2022||
| [make_list_with_nulls()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-list-with-nulls-aggfunction.md) | Returns a list of all the values within the group, including null values. |v22.8.1.1-clib,	Aug 3,2022||
| [make_set()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makeset-aggfunction.md), [make_set_if()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makesetif-aggfunction.md) | Returns a set of distinct values within the group without/with a predicate. |v22.8.1.1-clib,	Aug 3,2022||

## Row selector functions <a name="Row_Selector_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
| [arg_max()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arg-max-aggfunction.md) | Returns one or more expressions when the argument is maximized. |	v22.7.1.1-clib,	Jun 24,2022|[deviation or limitations](#Deviation_arg_max)  |
| [arg_min()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arg-min-aggfunction.md) | Returns one or more expressions when the argument is minimized. |	v22.7.1.1-clib,	Jun 24,2022|[deviation or limitations](#Deviation_arg_max)  |
| [take_any()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/take-any-aggfunction.md), [take_anyif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/take-anyif-aggfunction.md) | Returns a random non-empty value for the group without/with a predicate.|v23.3.1.2825-lts-ibm,Apr, 14,2023 |[deviation or limitations](#Deviation_take_any)  

## Statistical functions <a name="Statistical_functions"></a>

|Function Name     |Description             |Available since | Comment|
|-------------------------|--------------------------|----------|--------------------|
| [avg()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/avg-aggfunction.md) | Returns an average value across the group. |	v22.7.1.1-clib,	Jun 24,2022||
| [avgif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/avgif-aggfunction.md) | Returns an average value across the group (with predicate). |	v22.7.1.1-clib,	Jun 24,2022||
| [count()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/count-aggfunction.md), [countif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/countif-aggfunction.md) | Returns a count of the group without/with a predicate. |v22.7.1.1-clib	Jun 24,2022
| [count_distinct()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/count-distinct-aggfunction.md), [count_distinctif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/count-distinctif-aggfunction.md) | Returns a count of unique elements in the group without/with a predicate. |v22.12.3.6-clib,	Jan 26,2023||
| [dcount()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dcount-aggfunction.md), [dcountif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dcountif-aggfunction.md) | Returns an approximate distinct count of the group elements without/with a predicate. |v22.7.1.1-clib	Jun 24,2022
| [hll()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hll-aggfunction.md) | Returns the HyperLogLog (HLL) results of the group elements, an intermediate value of the `dcount` approximation. |v23.3.1.2825-lts-ibm,	Apr 14,2023|[deviation or limitations](#Deviation_hll)   
| [hll_merge()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hll-merge-aggfunction.md) | Returns a value for merged HLL results. |v23.3.1.2825-lts-ibm,	Apr 14,2023|[deviation or limitations](#Deviation_hll)   
| [dcount_hll](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dcount-hllfunction.md) | Calculates the distinct count from results generated by hll or hll_merge. |v23.3.1.2825-lts-ibm,	Apr 14,2023|[deviation or limitations](#Deviation_hll)   
| [max()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/max-aggfunction.md), [maxif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/maxif-aggfunction.md) | Returns the maximum value across the group without/with a predicate. |v22.7.1.1-clib	Jun 24,2022||
| [min()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/min-aggfunction.md), [minif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/minif-aggfunction.md) | Returns the minimum value across the group without/with a predicate. |v22.7.1.1-clib	Jun 24,2022||
| [percentile()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md) | Returns a percentile estimation of the group. |v22.8.1.4-clib,	Aug 31,2022||
| [percentiles()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md) | Returns percentile estimations of the group. |v22.8.1.4-clib,	Aug 31,2022||
| [percentiles_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md) | Returns the percentile approximates of the array. |v22.8.1.4-clib,	Aug 31,2022||
| [percentilesw()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md) | Returns the weighted percentile approximate of the group. |v22.8.1.4-clib,	Aug 31,2022||
| [percentilesw_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md) | Returns the weighted percentile approximate of the array. |v22.8.1.4-clib,	Aug 31,2022||
| [stdev()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/stdev-aggfunction.md), [stdevif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/stdevif-aggfunction.md) | Returns the standard deviation across the group for a population that is considered a sample without/with a predicate. |v22.8.1.4-clib,	Aug 31,2022||
| [stdevp()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/stdevp-aggfunction.md) | Returns the standard deviation across the group for a population that is considered representative. |v22.8.1.4-clib,	Aug 31,2022||
| [sum()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sum-aggfunction.md), [sumif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sumif-aggfunction.md) | Returns the sum of the elements within the group without/with a predicate. |v22.8.1.4-clib,	Aug 31,2022||
| [variance()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/variance-aggfunction.md), [varianceif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/varianceif-aggfunction.md) | Returns the variance across the group without/with a predicate. |v22.12.3.6-clib,	Jan 26,2023||
| [variancep()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/variancep-aggfunction.md) | Returns the variance across the group for a population that is considered representative. |v22.12.3.6-clib,	Jan 26,2023||

# Description, deviation or limitations <a name="Deviation_or_limitations"></a>
**Due to the differecne and limitation of ClickHouse, some KQL feratures implemented for ClickHouse may have some limations or different behaviours from ADX,
some can be improved in the future**  

## KQL-dialect setting  <a name="Deviation_dialect"></a> 
-  The config setting to allow modify dialect setting.  

    Set dialect setting in server configuration XML at user level(`users.xml`). This sets the dialect at server startup and CH will do query parsing for all users with `default` profile according to dialect value.

    For example: `<profiles> <!-- Default settings. --> <default> <load_balancing>random</load_balancing> <dialect>kusto_auto</dialect> </default>`  

-  Query can be executed with HTTP client as below once dialect is set in users.xml `echo "KQL query" | curl -sS "http://localhost:8123/?" --data-binary @-`

-  To execute the query using clickhouse-client , Update clickhouse-client.xml as below and connect clickhouse-client with --config-file option   
 `clickhouse-client --config-file=<config-file path>`  
 `<config> <dialect>kusto_auto</dialect> </config>`  

- OR pass dialect setting with '--'. For example :` clickhouse-client --dialect='kusto_auto' -q "KQL query"`


## join operator <a name="Deviation_join"></a>  

- columns  
    ADX : common columns are duplicatedc in output  
    KQL-CH : only one column for common columns
- column name
    ADX : column with same name (not common) ->column1 KQL-CH : column with same name (not common) -> right_.column
- filters
    ADX: Kusto is optimized to push filters that come after the join, towards the appropriate join side, left or right, when possible  
    KQL-CH: because in the domanin of KQL, does not know the schema of tables, so the push need to manually done by user, like:  

    `t1|join kind = innerunique t2 on key | where value == 'val1.2'`

    need to chang as the fowllowing by user(if user want) :  

    `t1| where value == 'val1.2' | join kind = innerunique t2 on key`

- semi join flavor
    ADX : only returns left side or right side columns  
    KQL-CH : returns columns from both side  
- join hints : not supported yet  
- Shuffle join and summarize are out of scope. 

## make-series operator <a name="Deviation_make-series"></a> 
- MakeSeriesParameters  
    MakeSeriesParameters is not supported  


## mv-expand operator <a name="Deviation_mv-expand"></a> 
- bagexpansion  
  bagexpansion parameter is not used. becasue only the  array is supported  
## summarize operator <a name="Deviation_summarize"></a> 
- SummarizeParameters  
    SummarizeParameters is not supported  
- behaviour (same as ADX):   
    - if bin is used , the column should be in select list if no alias include  
    - if no column included in aggregate functions, ( like count() ), should has alias with fun name + '',e.g count 
    - if column name included in aggregate functions, should have fun name + "_" + column name , like count(Age) -> count_Age  
    - if argument of an aggregate functions is an exprision, Columns1 ... Columnsn should be used as alias  
## top-hitters operator <a name="Deviation_top-hitters"></a> 
- algorithm.  
    currently implemented according to this statement:  
    ```
    The first syntax (no SummingExpression) is conceptually equivalent to:

    T | summarize C = count() by ValueExpression | top NumberOfValues by C desc    
    ```
    will do inprovement using **Count-Min-Sketch** algorithm later.  

## dynamic data type <a name="Deviation_dynamic"></a>  
suppport:  
- Null.
- scalar data types: bool, datetime, guid, int, long, real, string, and timespan.
- array   
**same type of array only**

not supported yet: 
- property bag 

## array_sort_desc() , array_sort_asc()<a name="Deviation_array_sort"></a>  
- ADX :  
null will be returned for every array that differs in length from the first one.  
- KQL-ClickHouse  
`[null]` will be returned for every array that differs in length from the first one.
## range() function <a name="Deviation_range"></a>  
- ADX:   
    return NULL if range is empty  
    The maxamum number of elements of array is 1,048,576  
- KQL-ClickHouse  
    return empty array `[]` if range is empty  
    The maxamum number of elements of array is 1000000   
## arg_max(),arg_min() function <a name="Deviation_arg_max"></a>  
 - `*`  is not currently a supported argument.

## take_any(),take_anyif() function <a name="Deviation_take_any"></a>  
 - `*`  is not currently a supported argument.

## lookup() function <a name="Deviation_lookup"></a>  
- it's an IBM specific suggested implementation. Supports simple keys only. Do not suppoer RANGE_HASHED 

## hash() function <a name="Deviation_hash"></a>  
- ClickHouse will attempt to fit a number within the smallest data type possible. As a result Int32 data types not cast with KQL int() may not match ADX results.  

## KQL sub-query <a name="Deviation_subquery"></a> 
- KQL sub-query:
    Multiple columns in sub-query works in KQL ADX but only the first column is effective, while not working in ClickHouse. this fixed issue. e.g.  

    `Customers | where FirstName in ((Customers|project FirstName, LastName))`

    limitation:  the select * noit work in sub-querym because there's no individual column.

## kql() KQL table function <a name="Deviation_tablefunction"></a> 
- create table  
    `CREATE TABLE kql_table4 ENGINE = Memory AS select *, now() as new_column From kql(Customers | project LastName,Age);`
- insert into table  
    create a tmp table:
    ```
    CREATE TABLE temp
    (    
        FirstName Nullable(String),
        LastName String, 
        Age Nullable(UInt8)
    ) ENGINE = Memory;

    INSERT INTO temp select * from kql(Customers|project FirstName,LastName,Age);  
    ```
- Select from kql()  
    `Select * from kql(Customers|project FirstName)`

## hll family functions <a name="Deviation_hll"></a>  
ClickHouse has a built-in aggregate function [uniqCombined64](https://clickhouse.com/docs/en/sql-reference/aggregate-functions/reference/uniqcombined64) which implements the HyperLogLog approximation. When combined with [combinators](https://clickhouse.com/docs/en/sql-reference/aggregate-functions/combinators) it's possible to achieve an effect similar to that of the KQL functions in question.

Mapping comes out to:
* `hll` -> `uniqCombined64State`
* `hll_if` -> `uniqCombined64IfState`
* `hll_merge` -> `uniqCombined64MergeState`
* `dcount_hll` -> `uniqCombined64Merge`

However, significant differences exist:
* In ClickHouse, accuracy values must align completely, while in KQL this aspect is a lot more liberal since intermediate results of different accuracies can be merged together.
* Results from `uniqCombined64IfState` cannot be merged with `uniqCombined64MergeState`, since `uniqCombined64IfMergeState` must be used to that end and `uniqCombined64IfMerge` as opposed to `uniqCombined64Merge` to do the calculation of the final result.

Initial limitations arising from the differences mentioned above:
* no support for `hll_if`
* only accuracy level of 4 is supported and that's the default
* intermediate results are binary as opposed to KQL's array-like output
