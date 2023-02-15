# KQL Language Core flavors


## Entities
Entity names   
Tables    
Columns    

## Data types
| KQL feature|Syntax|ClickHouse SQL equivalent|
|---|---|---|
|bool|  bool|Boolean| 
|datetime|datetime(value)| Datetime|  
|decimal | | | 
|dynamic  |dynamic( Value )| |
|guid| guid(00000000-0000-0000-0000-000000000000)|UUID|
|int|int|Int32|   
|long|long|Int64|   
|real|real|Float64|   
|string|  |String| 
|timespan|timespan(value)||
|Null values||NULL|

## Functions

## Query statements
Let statement
Query parameters statement
Tabular expression statements

## Tabular operators
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|
|count operator|  |count|
datatable operator   
distinct operator   
evaluate operator  
extend operator  
getschema operator  
invoke operator  
join operator  
limit operator  
order operator  
|project operator|  |Select|Yes|6|
project-away operator  
project-rename operator  
project-reorder operator  
parse operator  
print operator  
range operator  
render operator  
sort operator  
summarize operator  
|take operator || LIMIT|Yes|6|||
top operator  
union operator  
where operator  

## Special functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
database()  
toscalar()

## Scalar operators
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
Bitwise (binary) operators
Datetime/timespan arithmetic
Logical (binary)
Numerical operators
String operators
between operator
!between operator
in/!in operators
## Scalar functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
ago()
bin()
extract()
gettype()
hash()
iif()
indexof()
isempty()
isfinite()
isinf()
isnan()
isnotempty(), notempty()
isnotnull(), notempty()
isnull()
log()
not()
now()
parse_json()
pow()
rand()
split()
strcat()
strlen()
substring()

## Aggregation functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
any()
anyif()
arg_max()
arg_min()
avg()
count()
dcount()
make_list()
make_list_if()
make_list_with_nulls()
make_set()
make_set_if()
max()
maxif()
min()
minif()
percentiles()
stdev()
sum()
variance()
