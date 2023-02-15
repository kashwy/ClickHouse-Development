## 1 ADX KQL error code and mesage.
|code|Message|  
|----|----|  
|KS100|The pattern must start with a column name or *|
|KS101|The column name must follow a string literal|
|KS102|A string literal must follow a *|
|KS103|Using * after parsing a string column is ambiguous.|
|KS104|Invalid pattern part.|
|KS105|The name must be a single identifier only.|
|KS106|The operator '{name}' is not defined for the operand type {argumentTypes[0].Name}.|
|KS106|The operator '{name}' is not defined for the operand types {list}.|
|KS107|A value of type '{type.Name}' expected.|
|KS107|A value of type {list} expected.|
|KS108|Scalar value expected.|
|KS109|Column name expected.|
|KS110|Column rename assignment expected.|
|KS111|Table expected.|
|KS112|A table or scalar value expected.|
|KS113|A table with only one column expected.|
|KS114|Database expected.|
|KS115|Cluster expected.|
|KS116|The value of type '{type.Name}' is not allowed in this context.|
|KS117|The function '{functionName}' requires an argument list.|
|KS118|No arguments expected.|
|KS118|1 argument expected.|
|KS118|{count} arguments expected.|
|KS119|The function '{functionName}' expects no arguments.|
|KS119|The function '{functionName}' expects 1 argument.|
|KS119|The function '{functionName}' expects {count} arguments.|
|KS120|The function '{functionName}' expects between {min} and {max} arguments.|
|KS121|The function call has an incorrect number of arguments.|
|KS122|The scalar function '{name}' is not defined.|
|KS123|The aggregate function '{name}' is not defined.|
|KS124|The plug-in function '{name}' is not defined.|
|KS125|The plug-in function '{name}' is not enabled.|
|KS126|The plug-in function '{name}' is not allowed in this context.|
|KS127|The function '{name}' is not compatible with arguments ({types})|
|KS128|The name '{name}' does not refer to a function.|
|KS129|The expression must be a constant.|
|KS130|The expression must be a constant or identifier.|
|KS131|The expression must be a literal.|
|KS132|The expression must be a literal scalar value.|
|KS133|The expression value must not be empty.|
|KS134|The expression value must be an integer.|
|KS135|The expression value must be an real or decimal number.|
|KS136|The expression value must be an integer or dynamic.|
|KS137|The expression value must be a number.|
|KS137|The expression value must be a number or boolean true/false.|
|KS138|The argument value must be summable: a number, timespan or datetime.|
|KS139|The multi-valued expression cannot be assigned to a variable.|
|KS140|The expression must be the value: {values[0]}|
|KS140|The expression must be one of the values: {list}|
|KS141|The expression must have the type {types[0].Name}.|
|KS141|The expression must have one of the types: {list}.|
|KS142|The name '{name}' does not refer to any known column, table, variable or function.|
|KS143|The function '{name}' is not defined.|
|KS144|The aggregate function '{name}' is not allowed in this context.|
|KS145|The column '{name}' must exist on both sides of the join.|
|KS146|The name '{name}' refers to more than one column or variable|
|KS147|The element access operator [] is not allowed in this context.|
|KS148|A column name cannot be inferred for this expression.|
|KS149|The expression does not have multiple named values.|
|KS150|The name does not have a corresponding expression.|
|KS160|The name '{name}' is not a valid type name.|
|KS170|The syntax is not a valid column declaration.|
|KS171|A column with the name '{name}' is already declared.|
|KS172|The syntax is not a valid type expression.|
|KS173|Incorrect number of data values. The values should appear in multiples of {multiple}.|
|KS174|The operator cannot be the first operator in a query.|
|KS175|The operator must be the first operator in the query.|
|KS176|Query operator expected.|
|KS177|The query operator '{name}' is not allowed in the current context.|
|KS178|The type '{intervalType.Name}' is not an appropriate interval type for '{rangeType.Name}'|
|KS179|The name '{name}' is not a recognized parameter for this operator.|).WithSeverity(DiagnosticSeverity.Warning);
|KS180|The parameter '{name}' is already specified.|
|KS181|The name '{name}' does not refer to a table.|
|KS182|The join condition must be either the name of a column common to both tables or in the form $left.<column> == $right.<column>.|
|KS183|The join condition operand must be: {prefix}.<column>|
|KS184|The expression refers to more than one column.|
|KS185|The pack(*) expression must be the last item in the list.|
|KS185|The number of values must equal the number of parameters.|
|KS186|A path value can only be specified when a path name is part of the declaration.|
|KS187|A path value is expected.|
|KS188|No pattern matches the specified arguments.|
|KS189|Default value expected.|
|KS190|The table has no columns|
|KS191|The * syntax is not allowed here.|
|KS192|The * syntax must be the last argument.|
|KS193|Named arguments are not supported for this function.|
|KS194|Compound named arguments are not supported.|
|KS195|All arguments after an unordered named argument must be named.|
|KS196|The argument name does not refer to a declared parameter.|
|KS197|The argument for parameter '{parameterName}' is missing.|
|KS198|The incomplete fragment is unexpected.|
|KS199|No columns are currently in scope.|
|KS200|Failure in expansion of '{name}': {errors}|
|KS201|A variable with the name '{name}' has already been declared.|
|KS202|Materialized view name must be a string literal|
|KS203|Failure in analysis '{analyzerName}': {message}|
|KS204|The name '{name}' does not refer to any known table, tabular variable or function.|
|KS205|The fuzzy union operand '{name}' does not refer to any known table, tabular variable or function.|)
|KS206|The argument value must be orderable: a number, timespan, datetime, string or boolean.|
|KS207|The name '{name}' either does not refer to a reachable cluster or no schema from it is currently available.|
|KS208|The name '{name}' does not refer to any known database.|
|KS209|The name '{name}' does not refer to any known external table.|
|KS210|The name '{name}' does not refer to any known materialized view.|
|KS211|The name '{name}' does not refer to any known function.|
|KS213|Client parameters are not supported or enabled.|
|KS214|Raw guid literals are not allowed in this context, use guid(...) instead.|
|KS215|Decimal values are not supported in dynamic objects.|
|KS300|Missing command.|


## 2 In our current implemention 

currently the KQL error handling are very limited. most error and exeptions are passed to ClikHouse, and handled by ClickHouse.

Only part of KQL parsing errors are captuerd: 

|code|code number|Message|
|---|---|---|
|ErrorCodes::SYNTAX_ERROR  	|62				|Syntax error near {Operator}|
|							|				|Syntax error near {Keyword}|
|							|				|...|
|							|				|other specified messages|
|ErrorCodes::BAD_ARGUMENTS 	|36				|various message for corresponding functions|
|ErrorCodes::NUMBER_OF_ARGUMENTS_DOESNT_MATCH|42|argunments not match message for corresponding functions|
|ErrorCodes::NOT_IMPLEMENTED		|48		|	various message for corresponding tokens|
|ErrorCodes::UNKNOWN_FUNCTION        |46      | message for spercified function|
|ErrorCodes::UNKNOWN_TYPE			|50		|not a supported kusto data type|

and most errors are handle by ClickHouse.

## 3  Task to enhance the erorr handling: 

This is the ticket for this task:

https://zenhub.ibm.com/workspaces/clickhouse-project-61250df53aaf060db4e08052/issues/clickhouse/issue-repo/1589