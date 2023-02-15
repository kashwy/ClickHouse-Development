# KQL Language Full flavors



## Entities
Querying external entities 	
Stored functions
External Tables


## Query statements
Alias statement  
Pattern statement  
Restrict statement  
Set statement  
Batches  

## Tabular operators
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|
as operator  
consume operator  
externaldata operator  
lookup operator  
make-series operator  
mv-apply operator  
mv-expand operator  
partition operator 
sample operator 
sample-distinct operator 
serialize operator 
top-nested operator 

## evaluate operator plugins
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
bag_unpack 
dcount_intersect 
narrow 
pivot 
preview 
python 
R 	
rolling_percentile 	
sql_request 

## Special functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
table()


## Scalar functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
abs()   
acos()  
array_concat()  
array_iif()  
array_length()  
array_slice()  
array_split()  
asin()  
assert()  
atan()  
atan2()  
base64_decode_toarray()  
base64_decode_tostring()  
base64_encode_tostring()  
bag_keys()  
beta_cdf()  
beta_inv()  
beta_pdf()  
bin_auto()  
binary_and()  
binary_not()  
binary_or()  
binary_shift_left()  
binary_shift_right()  
binary_xor()  
case()  
ceiling()  
coalesce()  
column_ifexists()  
cos()  
cot()  
countof()  
datetime_add()  
datetime_part()  
datetime_diff()  
dayofmonth()  
dayofweek()  
dayofyear()  
dcount_hll()  
endofday()  
endofmonth()  
endofweek()  
endofyear()  
exp()  
exp10()  
exp2()  
extract_all()  
extractjson()  
floor()  
format_datetime()  
format_timespan()  
gamma()  
getmonth()  
getyear()  
hash_sha256()  
hll_merge()  
hourofday()  
indexof_regex()  
isascii()  
isutf8()  
log10()  
log2()  
loggamma()  
make_datetime()  
make_string()  
make_timespan()  
max_of()  
min_of()  
monthofyear()  
new_guid()  
pack()  
pack_all()  
pack_array()  
pack_dictionary()  
parse_csv()  
parse_ipv4()  
parse_path()  
parse_url()  
parse_urlquery()  
parse_user_agent()  
parse_version()  
parse_xml()  
percentile_tdigest()  
percentrank_tdigest()  
pi()  
radians()  
range()  
rank_tdigest()  
repeat()  
replace()  
reverse()  
round()  
set_difference()  
set_intersect()  
set_union()  
sign()  
sin()  
sqrt()  
startofday()  
startofmonth()  
startofweek()  
startofyear()  
strcat_array()  
strcat_delim()  
strcmp()  
string_size()  
strrep()  
tan()  
tdigest_merge()  
tolower()  
toupper()  
to_utf8()  
treepath()  
trim()  
trim_end()  
trim_start()  
url_decode()  
url_encode()  
weekofyear()  
zip()  

## Aggregation functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
avgif()  
buildschema()  
countif()  
dcountif()  
hll()  
hll_merge()  
make_bag()  
make_bag_if()  
stdevif()  
stdevp()  
sumif()  
tdigest()  
tdigest_merge()  
varianceif()  
variancep()


## Window functions
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
next()
prev()
row_cumsum()
row_number()

## Rolling window aggregations  
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
rolling_percentile()

# Time Series Analysis  
| KQL feature|Syntax link|ClickHouse SQL equivalent|IBM Stakeholder feature|impact|phase|done| 
|---|---|---|---|---|---|---|  
time series analysis  
make-series operator  
series_add()  
series_decompose()  
series_decompose_anomalies()  
series_decompose_forecast()  
series_divide()  
series_equals()  
series_fill_backward()  
series_fill_const()  
series_fill_forward()  
series_fill_linear()  
series_fir()  
series_fit_line()  
series_fit_line_dynamic()  
series_fit_2lines()  
series_fit_2lines_dynamic()  
series_greater()  
series_greater_equals()  
series_iir()  
series_less()  
series_less_equals()  
series_multiply()  
series_not_equals()  
series_outliers()  
series_pearson_correlation()  
series_periods_detect()  
series_periods_validate()  
series_seasonal()  
series_stats()  
series_stats_dynamic()  
series_subtract()  
