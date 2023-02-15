# Dev Test Sheet.

## 1.  table operator:
Table Name : Customers, Product
| input | Sql result|expected | pass(Yes/NO)|Action|
|---|---|---|---|---|
|Customers|SELECT * FROM Customers|SELECT * FROM Customers| Yes|
|Customers;|SELECT * FROM Customers| SELECT * FROM Customers|Yes|
|Customers \||Syntax error|Syntax error| Yes|
|Customers Product|`SELECT * FROM Customers AS Product`|Syntax error| No |Fix|
|Customers 123|`SELECT * FROM Customers`|Syntax error| No |Fix|
|Customers *-|`SELECT * FROM Customers`|Syntax error| No |Fix|
|Customers()|`SELECT * FROM Customers()`|SELECT * FROM Customers| No |Fix|
|"Customers"|SELECT * FROM Customers|SELECT * FROM Customers| Yes |
|"Customers";|SELECT * FROM Customers|SELECT * FROM Customers| Yes |
|"Customers" \||Syntax error|Syntax error| Yes|
|"Customers|Syntax error|Syntax error| Yes|
|Customers"|Syntax error|Syntax error| Yes|
|**SQL Keywords as table name**||||
|Select|Syntax error|Syntax error| Yes|
|Insert |Syntax error|Syntax error| Yes|
|Create |Syntax error|Syntax error| Yes|
|Alter |Syntax error|Syntax error| Yes|
|System |Syntax error|Syntax error| Yes|
|Show |Syntax error|Syntax error| Yes|
|Grant |Syntax error|Syntax error| Yes|
|Revoke |Syntax error|Syntax error| Yes|
|Attach |Syntax error|Syntax error| Yes|
|Check |Syntax error|Syntax error| Yes|
|Describe|Syntax error|Syntax error| Yes|
|Desc |Syntax error|Syntax error| Yes|
|Detach |Syntax error|Syntax error| Yes|
|Drop |Syntax error|Syntax error| Yes|
|Exists|Syntax error|Syntax error| Yes|
|Kill |Syntax error|Syntax error| Yes|
|Optimize |Syntax error|Syntax error| Yes|
|Set |Syntax error|Syntax error| Yes|
|Truncate |Syntax error|Syntax error| Yes|
|Use |Syntax error|Syntax error| Yes|
|Explain |Syntax error|Syntax error| Yes|
|**Quoted SQL Keywords as table name**||||
|"Select"|SELECT * FROM Select|SELECT * FROM Select| Yes|

## 2 . project Operator

| input | Sql result|expected | pass(Yes/NO)|Action|
|---|---|---|---|---|
|Customers \| project|Syntax error|Syntax error| Yes|
|Customers \| project FirstName|SELECT FirstName FROM Customers|SELECT FirstName FROM Customers| Yes|
|Customers \| project FirstName,|`SELECT FirstName FROM Customers`|Syntax error| No|Fix|
|Customers \| project FirstName, LastName|SELECT FirstName, LastName FROM Customers|SELECT FirstName,LastName FROM Customers| Yes|
|Customers \| project FirstName LastName|`SELECT FirstName FROM Customers`|Syntax error| No|Fix|
|Customers \| project FirstName, LastName \| project FirstName|SELECT FirstName FROM Customers|SELECT FirstName FROM Customers| Yes|
|Customers \| project  LastName \| project FirstName, FirstName|Syntax error|Syntax error| Yes|
|Customers \| project FN = FirstName|`SELECT FN = FirstName FROM Customers`|SELECT FirstName FN FROM Customers| No|Next phase
|Customers \| project oldAge = Age - 2|`SELECT oldAge = (Age - 2) FROM Customers`|SELECT Age - 2 oldAge FROM Customers| No| Next Phase

## 3. limit Operator
| input | Sql result|expected | pass(Yes/NO)|Action|
|---|---|---|---|---|
|Customer \| limit |Syntax error|Syntax error| Yes|
|Customer \| take |Syntax error|Syntax error| Yes|
|Customer \| take xyz|Syntax error|Syntax error| Yes|
|Customer \| limit 5|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| take 5+2 |SELECT * FROM Customers LIMIT 5+2|SELECT * FROM Customers LIMIT 5+2| Yes|
|Customer \| take 5|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| take 5 \||Syntax error|Syntax error| Yes|
|Customer \| limit 5 \| limit 8|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| limit 8 \| limit 5|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| take 5 \| take 8|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| take 8 \| take 5|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| limit 8 \| take 5|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| take 8 \| limit 5|SELECT * FROM Customers LIMIT 5|SELECT * FROM Customers LIMIT 5| Yes|
|Customer \| take 5+2 \| take 3|`SELECT * FROM Customers LIMIT 5+2`|SELECT * FROM Customers LIMIT 3| No|Next Phase
|Customer \| take 4+2 \| take 5-2|`SELECT * FROM Customers LIMIT 4 + 2`|SELECT * FROM Customers LIMIT 5-2| No|Next Phase

## 4. General case
| input | Sql result|expected | pass(Yes/NO)|Action|
|---|---|---|---|---|
|Customers  project FirstName , LastName|`SELECT * FROM Customers AS project`|Syntax error|No|Fix|
|Customers \| FirstName , LastName|Syntax error|Syntax error|Yes| |
|Customers \| project FirstName \| take 5|SELECT FirstName FROM Customers LIMIT 5|SELECT FirstName FROM Customers LIMIT 5|Yes| |
|Customers \| take 5 \| project FirstName|SELECT FirstName FROM Customers LIMIT 5|SELECT FirstName FROM Customers LIMIT 5|Yes| |
|Customers \| project FirstName \| take 5 \| project FirstName|SELECT FirstName FROM Customers LIMIT 5|SELECT FirstName FROM Customers LIMIT 5|Yes| |

## 5. Sort
| input | Sql result|expected | pass(Yes/NO)|Action|
|---|---|---|---|---|
|Customers \| order by FirstName |SELECT * FROM Customers ORDER BY FirstName DESC|SELECT * FROM Customers ORDER BY FirstName DESC|Yes||
|Customers \| order by FirstName desc|SELECT * FROM Customers ORDER BY FirstName DESC|SELECT * FROM Customers ORDER BY FirstName DESC|Yes||
|Customers \| order by FirstName desc nulls first|SELECT * FROM Customers ORDER BY FirstName DESC NULLS FIRST| |Yes||
|Customers \| order by FirstName desc nulls last|SELECT * FROM Customers ORDER BY FirstName DESC NULLS LAST| |Yes||
|Customers \| order by FirstName asc |SELECT * FROM Customers ORDER BY FirstName ASC|SELECT * FROM Customers ORDER BY FirstName ASC|Yes||
|Customers \| order by FirstName asc  nulls first|SELECT * FROM Customers ORDER BY FirstName ASC NULLS FIRST| |Yes||
|Customers \| order by FirstName asc nulls last|SELECT * FROM Customers ORDER BY FirstName ASC NULLS LAST| |Yes||
|Customers \| order by FirstName nulls first |`SELECT * FROM Customers ORDER BY FirstName DESC NULLS LAST`|Syntax error|No|Fix|
|Customers \| order by FirstName nulls last |`SELECT * FROM Customers ORDER BY FirstName DESC NULLS FIRST`|Syntax error|No|Fix|
|Customers \| order by FirstName dsc |`SELECT * FROM Customers ORDER BY FirstName DESC`|Syntax error|No|Fix|
