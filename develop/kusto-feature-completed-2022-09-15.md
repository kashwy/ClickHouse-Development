| Area      | Function/Operator |  Priority     |  completed | comments  |  
| ------    | ----------------- |    ---------- | ---------- |-----------|
| CTAS      | kql()             | High          | Yes        | |
|         |             |              |             |  |
| KQL-dialect| set dialect='clickhouse'  |             | Yes        | this is default dialect |
| | set dialect='kusto-auto'   |           | Yes        | works for both sql and kql, so kql can be cobined with sql|
| | set dialect='kusto'   |           | Yes        | only works for kql, sql will not wok|
|         |             |              |             |  |
| Subselect | has\_any          | High         | Yes -       |subquery not support yet |
|           | has\_all          | High         | Yes -       | subquery not support yet|
|           | in                | High         | Yes      | (subquery need to be wraped with bracket inside bracket) like: `Customers \| where Age in ((Customers\|project Age\|where Age < 30))` |
|           |materialize        | defer        |             | |
|         |             |              |             |  |
|  Operators  |            |              |             |  |
|    |    print   |        High      |    Yes         |  |
|                          | project     | Med          | Yes        |
|                          | extend     | Med          | Yes        |
|                          | takem, limit     | Med          | Yes        |
|                          | sort by, order by     | Med          | Yes        |
|                          | where     | Med          | Yes        |
|                          | summarize     | Med          | Yes        |
|                          | mv-expand     | Med          | Yes        |
|                          | make-series     | Med          | Yes        |
|   Data Type |             |              |             |  |
|  |bool, boolean|High |Yes | |
|  |datetime, date|High |Yes | |
|  |dynamic|High |Yes |only arrays of elements of the same type  |
|  |guid|High |Yes | |
|  |int|High |Yes | |
|  |long|High |Yes | |
|  |real, double|High |Yes | |
|  |double|High |Yes | |
|  |string|High |Yes | |
|  |timespan, time|High |Yes | |
|  |decimal|High |Yes | |
|         |             |              |             |  |
| Type: timespan           | timespan()  | High         | Yes        | |
| Type: datetime           | datetime()  | High         | Yes      | |
|                          | [ago()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/agofunction.md)  | High         | Yes      | |
|                          | [datetime\_add()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/datetime-addfunction.md)                                          | High         | Yes      |
|                          | [datetime\_part()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/datetime-partfunction.md)                                        | High         | Yes      |
|                          | [datetime\_diff()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/datetime-difffunction.md)                                        | High         | Yes      |
|                          | [dayofmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dayofmonthfunction.md)                                               | High         | Yes        |
|                          | [dayofweek()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dayofweekfunction.md)                                                 | High         | Yes        |
|                          | [dayofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dayofyearfunction.md)                                                 | High         | Yes        |
|                          | [endofday()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofdayfunction.md)                                                   | High         | Yes      |
|                          | [endofmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofmonthfunction.md)                                               | High         | Yes      |
|                          | [endofweek()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofweekfunction.md)                                                 | High         | Yes      |
|                          | [endofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endofyearfunction.md)                                                 | High         | Yes      |
|                          | [format\_datetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-datetimefunction.md)                                    | High         | Yes|
|                          | [format\_timespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-timespanfunction.md)                                    | High         | Yes        |
|                          | [getmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/getmonthfunction.md)                                                   | High         | Yes        |
|                          | [getyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/getyearfunction.md)                                                     | High         | Yes        |
|                          | [hourofday()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hourofdayfunction.md)                                                 | High         | Yes        |
|                          | [make\_datetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-datetimefunction.md)                                        | High         | Yes        |
|                          | [make\_timespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-timespanfunction.md)                                        | High         | Yes      |
|                          | [monthofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/monthofyearfunction.md)                                             | High         | Yes        |
|                          | [now()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/nowfunction.md)                                                             | High         | Yes        |
|                          | [startofday()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofdayfunction.md)                                               | High         | Yes        |
|                          | [startofmonth()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofmonthfunction.md)                                           | High         | Yes        |
|                          | [startofweek()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofweekfunction.md)                                             | High         | Yes        |
|                          | [startofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startofyearfunction.md)                                             | High         | Yes        |
|                          | [todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todatetimefunction.md)                                               | High         | Yes      |
|                          | [totimespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/totimespanfunction.md)                                               | High         | Yes        |
|                          | [unixtime\_microseconds\_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-microseconds-todatetimefunction.md) | High         | Yes        |
|                          | [unixtime\_milliseconds\_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-milliseconds-todatetimefunction.md) | High         | Yes        |
|                          | [unixtime\_nanoseconds\_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-nanoseconds-todatetimefunction.md)   | High         | Yes        |
|                          | [unixtime\_seconds\_todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/unixtime-seconds-todatetimefunction.md)           | High         | Yes      |
|                          | [weekofyear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/weekofyearfunction.md)                                               |              | Yes        |
|         |             |              |             |  |
| Type: String             | String()                                                                                                                                              |              |             |
|                          | [base64\_encode\_tostring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64_encode_tostringfunction.md)                     | Med          | Yes        |
|                          | [base64\_encode\_fromguid()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64-encode-fromguid-function.md)                    | Med          | Yes        |
|                          | [base64\_decode\_tostring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64_decode_tostringfunction.md)                     | Med          | Yes        |
|                          | [base64\_decode\_toarray()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64_decode_toarrayfunction.md)                       | Med          | Yes        |
|                          | [base64\_decode\_toguid()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/base64-decode-toguid-function.md)                        | Med          | Yes        |
|                          | [countof()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/countoffunction.md)                                                     | High         | Yes      |
|                          | [extract()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractfunction.md)                                                     | High         | Yes      |
|                          | [extract\_all()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractallfunction.md)                                             | MED          | Yes      |
|                          | [extractjson()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractjsonfunction.md)                                             | Eval / Defer |             |
|                          | [has\_any\_index()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-any-index-function.md)                                      | High         |       Yes      |
|                          | [indexof()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/indexoffunction.md)                                                     | High         | Yes      |occurrence not supported yet|
|                          | [isempty()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isemptyfunction.md)                                                     | High         | Yes        |
|                          | [isnotempty()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnotemptyfunction.md)                                               | High         | Yes        |
|                          | [isnotnull()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnotnullfunction.md)                                                 | High         | Yes        |
|                          | [isnull()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/isnullfunction.md)                                                       | High         | Yes        |
|                          | [parse\_command\_line()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-command-line.md)                                     | Defer        |             |
|                          | [parse\_csv()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parsecsvfunction.md)                                                 | Defer        |             |
|                          | [parse\_json()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parsejsonfunction.md)                                               | Defer        |             |
|                          | [parse\_url()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parseurlfunction.md)                                                 | High         | Yes        |
|                          | [parse\_urlquery()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parseurlqueryfunction.md)                                       | High         | Yes        |
|                          | [parse\_version()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-versionfunction.md)                                        | Defer        |             |
|                          | [replace\_regex()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/replace-regex-function.md)                                       | High         | Yes        |
|                          | [reverse()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/reversefunction.md)                                                     | Defer        |             |
|                          | [split()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/splitfunction.md)                                                         | High         | Yes      |
|                          | [strcat()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strcatfunction.md)                                                       | High         | Yes      |
|                          | [strcat\_delim()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strcat-delimfunction.md)                                          | High         | Yes      |
|                          | [strcmp()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strcmpfunction.md)                                                       | High         | Yes        |
|                          | [strlen()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strlenfunction.md)                                                       | High         | Yes        |
|                          | [strrep()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/strrepfunction.md)                                                       | High         | Yes        |
|                          | [substring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/substringfunction.md)                                                 | High         | Yes        |
|                          | [toupper()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/toupperfunction.md)                                                     | High         | Yes        |
|                          | [translate()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/translatefunction.md)                                                 | High         | Yes        |
|                          | [trim()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/trimfunction.md)                                                           | High         | Yes        |
|                          | [trim\_end()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/trimendfunction.md)                                                   | High         | Yes        |
|                          | [trim\_start()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/trimstartfunction.md)                                               | High         | Yes        |
|                          | [url\_decode()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/urldecodefunction.md)                                               | High         | Yes        |
|                          | [url\_encode()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/urlencodefunction.md)                                               | High         | Yes        |
|                          | [\==](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/equals-cs-operator.md)                                                        | High         | Yes        |
|                          | [!=](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-equals-cs-operator.md)                                                     | High         | Yes        |
|                          | [\=~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/equals-operator.md)                                                           | High         |         |
|                          | [!~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-equals-operator.md)                                                        | High         |         |
|                          | [contains](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/contains-operator.md)                                                    | High         | Yes        |
|                          | [!contains](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-contains-operator.md)                                               | High         | Yes        |
|                          | [contains\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/contains-cs-operator.md)                                             | High         | Yes        |
|                          | [!contains\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-contains-cs-operator.md)                                        | High         | Yes        |
|                          | [endswith](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endswith-operator.md)                                                    | High         | Yes        |
|                          | [!endswith](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-endswith-operator.md)                                               | High         | Yes        |
|                          | [endswith\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/endswith-cs-operator.md)                                             | High         | Yes        |
|                          | [!endswith\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-endswith-cs-operator.md)                                        | High         | Yes        |
|                          | [has](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-operator.md)                                                              | High         | Yes        |
|                          | [!has](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-has-operator.md)                                                         | High         | Yes        |
|                          | [has\_all](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-all-operator.md)                                                     | High         | Yes        |
|                          | [has\_any](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-anyoperator.md)                                                      | High         | Yes        |
|                          | [has\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/has-cs-operator.md)                                                       | High         | Yes        |
|                          | [!has\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-has-cs-operator.md)                                                  | High         | Yes        |
|                          | [hasprefix](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hasprefix-operator.md)                                                  | High         | Yes |
|                          | [!hasprefix](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hasprefix-operator.md)                                             | High         | Yes |
|                          | [hasprefix\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hasprefix-cs-operator.md)                                           | High         | Yes |
|                          | [!hasprefix\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hasprefix-cs-operator.md)                                      | High         | Yes |
|                          | [hassuffix](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hassuffix-operator.md)                                                  | High         | Yes |
|                          | [!hassuffix](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hassuffix-operator.md)                                             | High         | Yes |
|                          | [hassuffix\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/hassuffix-cs-operator.md)                                           | High         | Yes |
|                          | [!hassuffix\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-hassuffix-cs-operator.md)                                      | High         | Yes      |
|                          | [in](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/in-cs-operator.md)                                                             | High         | Yes        |
|                          | [!in](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-in-cs-operator.md)                                                        | High         | Yes        |
|                          | [in~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/inoperator.md)                                                                | High         |   |
|                          | [!in~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-in-operator.md)                                                          | High         |   |
|                          | [matches regex](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/regex-operator.md)                                                  | High         | Yes        |
|                          | [startswith](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startswith-operator.md)                                                | High         | Yes        |
|                          | [!startswith](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-startswith-operator.md)                                           | High         | Yes        |
|                          | [startswith\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/startswith-cs-operator.md)                                         | High         | Yes        |
|                          | [!startswith\_cs](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-startswith-cs-operator.md)                                    | High         | Yes        |
|                          |                                                                                                                                                       |              |             |
| Type Dynamic (Array/Set) | [array\_concat()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayconcatfunction.md)                                           | MED          | Yes        |
|                          | [array\_iif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayifffunction.md)                                                 | High         | Yes      |
|                          | [array\_index\_of()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayindexoffunction.md)                                       | High         | Yes        |Supports only basic lookup. Do not support start_index, length and occurrence|
|                          | [array\_length()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraylengthfunction.md)                                           | Hugh         | Yes        |
|                          | [array\_reverse()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array-reverse-function.md)                                       | Defer        |   Yes          |
|                          | [array\_rotate\_left()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_rotate_leftfunction.md)                               | Defer        |   Yes          |
|                          | [array\_rotate\_right()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_rotate_rightfunction.md)                             | Defer        |     Yes        |
|                          | [array\_shift\_left()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_shift_leftfunction.md)                                 | Defer        |    Yes         |
|                          | [array\_shift\_right()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array_shift_rightfunction.md)                               | Defer        |     Yes        |
|                          | [array\_slice()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arrayslicefunction.md)                                             | MED          | Yes        |
|                          | [array\_sort\_asc()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraysortascfunction.md)                                       | High         | Yes -         |
|                          | [array\_sort\_desc()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraysortdescfunction.md)                                     | High         | Yes -        |
|                          | [array\_split()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arraysplitfunction.md)                                             | MED          | Yes        |
|                          | [array\_sum()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/array-sum-function.md)                                               | High         | Yes        |
|                          | [bag\_keys()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/bagkeysfunction.md)                                                   | Defer        |             |
|                          | [bag\_merge()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/bag-merge-function.md)                                               | Defer        |             |
|                          | [bag\_remove\_keys()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/bag-remove-keys-function.md)                                  | Defer        |             |
|                          | [jaccard\_index()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/jaccard-index-function.md)                                       | Defer        |     Yes        |
|                          | [pack()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/packfunction.md)                                                           | MED          |       |
|                          | [pack\_all()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/packallfunction.md)                                                   | MED          |       |
|                          | [pack\_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/packarrayfunction.md)                                               | MED          | Yes      |only arrays of elements of the same type |
|                          | [repeat()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/repeatfunction.md)                                                       | MED          | Yes        |if count is constant value 0, null will be return ed as specified in KQL doc, if count is 0 of a result of expression or column, an array with null  `[null]` will be returned|
|                          | [set\_difference()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/setdifferencefunction.md)                                       | MED          | Yes      | 
|                          | [set\_has\_element()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sethaselementfunction.md)                                     | MED          | Yes      |
|                          | [set\_intersect()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/setintersectfunction.md)                                         | MED          | Yes      |
|                          | [set\_union()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/setunionfunction.md)                                                 | MED          | Yes      |
|                          | [treepath()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/treepathfunction.md)                                                   | Defer        |             |
|                          | [zip()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/zipfunction.md)                                                             | Defer        |     Yes        |only arrays of elements of the same type |
|                          | [mv-expand](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/mvexpandoperator.md)                                                    | Eval/ Defer  |     Yes        |array only (bag is not supported)|
|                          | [mv-apply](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/mv-applyoperator.md)                                                     | Eval/ Defer  |             |
|                          |                                                                                                                                                       |              |             |
| Casting/Conversion       |                                                                                                                                                       |              |             |
|                          | [tobool()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/toboolfunction.md)                                                       | High         | Yes        |
|                          | [todatetime()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todatetimefunction.md)                                               | High         | Yes        |
|                          | [todouble()/toreal()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/todoublefunction.md)                                          | High         | Yes        |
|                          | [tostring()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/tostringfunction.md)                                                   | High         | Yes        |
|                          | [totimespan()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/totimespanfunction.md)                                               | High         | Yes        |
|                          |                                                                                                                                                       |              |             |
| Conditional              |                                                                                                                                                       |              |             |
|                          | [iff/iif](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/iiffunction)                                                               | High         |          |
|                          | [case()](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/casefunction)                                                               | High         |          |
|                          | [coalesce()](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/coalescefunction)                                                       | Defer        |             |
|                          |                                                                                                                                                       |              |             |
| Aggregations             | summarize       | High         | Yes      |`SummarizeParameters` not support yet .   if bin is used , the column should be in select list if no alias include: for aggregate function should has alias with fun name + '' , like count if with column should have column , like count(Age) -> count_Age, if it's a expr, Columns1 ... Columnsn should be used as alias|
|                          | [arg\_max()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arg-max-aggfunction.md)                                                | High         | Yes        |
|                          | [arg\_min()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/arg-min-aggfunction.md)                                                | High         | Yes        |
|                          | [avg()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/avg-aggfunction.md)                                                         | High         | Yes        |
|                          | [avgif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/avgif-aggfunction.md)                                                     | High         | Yes        |
|                          | [binary\_all\_and](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-all-and-aggfunction.md)                                   | MED          | Yes |
|                          | [binary\_all\_or](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-all-or-aggfunction.md)                                     | MED          | Yes |
|                          | [binary\_all\_xor](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-all-xor-aggfunction.md)                                   | MED          | Yes |
|                          | [buildschema()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/buildschema-aggfunction.md)                                         | DEfer        |          |
|                          | [count()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/count-aggfunction.md)                                                     | High         | Yes        |
|                          | [countif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/countif-aggfunction.md)                                                 | High         | Yes        |
|                          | [dcount()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dcount-aggfunction.md)                                                   | High         | Yes |
|                          | [dcountif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/dcountif-aggfunction.md)                                               | High         | Yes |
|                          | [make\_bag()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-bag-aggfunction.md)                                              | Defer        |         |
|                          | [make\_bag\_if()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-bag-if-aggfunction.md)                                       | Defer        |         |
|                          | [make\_list()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makelist-aggfunction.md)                                             | High         | Yes        |
|                          | [make\_list\_if()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makelistif-aggfunction.md)                                       | High         | Yes        |
|                          | [make\_list\_with\_nulls()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-list-with-nulls-aggfunction.md)                    | High         |   Yes ? --       |
|                          | [make\_set()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makeset-aggfunction.md)                                               | High         | Yes        |
|                          | [make\_set\_if()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/makesetif-aggfunction.md)                                         | High         | Yes        |
|                          | [max()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/max-aggfunction.md)                                                         | High         | Yes        |
|                          | [maxif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/maxif-aggfunction.md)                                                     | High         | Yes        |
|                          | [min()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/min-aggfunction.md)                                                         | High         | Yes        |
|                          | [minif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/minif-aggfunction.md)                                                     | High         | Yes        |
|                          | [percentiles()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md)                                         | Med          | Yes        |
|                          | [percentiles\_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md)                                  | Med          |          |
|                          | [percentilesw()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md)                                        | Med          | Yes        |
|                          | [percentilesw\_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md)                                 | Med          |          |
|                          | [stdev()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/stdev-aggfunction.md)                                                     | Med          | Yes      |
|                          | [stdevif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/stdevif-aggfunction.md)                                                 | Med          | Yes      |
|                          | [sum()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sum-aggfunction.md)                                                         | High         | Yes        |
|                          | [sumif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/sumif-aggfunction.md)                                                     | High         | Yes        |
|                          | [take\_any()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/take-any-aggfunction.md)                                              | Defer        |         |
|                          | [take\_anyif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/take-anyif-aggfunction.md)                                          | Defer        |         |
|                          | [variance()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/variance-aggfunction.md)                                               | Defer        |         |
|                          | [varianceif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/varianceif-aggfunction.md)                                           | Defer        |         |
|                          | top-hitters                                                                                                                                           | High         |         |
|                          |                                                                                                                                                       |              |             |
| Time Series              | make-series    | High         | Yes        |`MakeSeriesParameters` not support yet|
|                          | [series\_fir()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-firfunction.md)                                              | Eval         |          |
|                          | [series\_iir()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-iirfunction.md)                                              | Eval         |          |
|                          | [series\_fit\_line()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-linefunction.md)                                   | Eval         |          |
|                          | [series\_fit\_line\_dynamic()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-line-dynamicfunction.md)                  | Eval         |          |
|                          | [series\_fit\_2lines()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-2linesfunction.md)                               | Eval         |          |
|                          | [series\_fit\_2lines\_dynamic()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-2lines-dynamicfunction.md)              | Eval         |          |
|                          | [series\_outliers()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-outliersfunction.md)                                    | Eval         |          |
|                          | [series\_periods\_detect()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-periods-detectfunction.md)                       | Eval         |          |
|                          | [series\_periods\_validate()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-periods-validatefunction.md)                   | Eval         |          |
|                          | [series\_stats\_dynamic()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-stats-dynamicfunction.md)                         | Eval         |          |
|                          | [series\_stats()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-statsfunction.md)                                          | Eval         |          |
|                          | [series\_fill\_backward()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-backwardfunction.md)                         | Eval         |          |
|                          | [series\_fill\_const()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-constfunction.md)                               | Eval         |          |
|                          | [series\_fill\_forward()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-forwardfunction.md)                           | Eval         |          |
|                          | [series\_fill\_linear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-linearfunction.md)                             | Eval         |          |
|                          |                                                                                                                                                       |              |             |
| IPv4/IPv6                |                                                                                                                                                       |              |             |
|                          | [ipv4\_compare()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-comparefunction.md)                                          | High         | Yes      |
|                          | [ipv4\_is\_in\_range()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-is-in-range-function.md)                               | High         | Yes        |
|                          | [ipv4\_is\_match()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-is-matchfunction.md)                                       | High         | Yes      |
|                          | [ipv4\_is\_private()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-is-privatefunction.md)                                   | High         | Yes        |
|                          | [ipv4\_netmask\_suffix](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv4-netmask-suffix-function.md)                            | High         | Yes        |
|                          | [parse\_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv4function.md)                                              | High         | Yes        |
|                          | [parse\_ipv4\_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv4-maskfunction.md)                                   | High         | Yes      |
|                          | [ipv6\_compare()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv6-comparefunction.md)                                          | High         | Yes      |
|                          | [ipv6\_is\_match()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/ipv6-is-matchfunction.md)                                       | High         | Yes      |
|                          | [parse\_ipv6()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv6function.md)                                              | High         | Yes        |
|                          | [parse\_ipv6\_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/parse-ipv6-maskfunction.md)                                   | High         | Yes      |
|                          | [format\_ipv4()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-ipv4-function.md)                                           | High         | Yes      |
|                          | [format\_ipv4\_mask()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/format-ipv4-mask-function.md)                                | High         | Yes      |
|                          |                                                                                                                                                       |              |             |
| Binary Functions         |                                                                                                                                                       |              |             |
|                          | [binary\_and()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-andfunction.md)                                              | MED          | Yes        |
|                          | [binary\_not()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-notfunction.md)                                              | MED          | Yes        |
|                          | [binary\_or()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-orfunction.md)                                                | MED          | Yes        |
|                          | [binary\_shift\_left()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-shift-leftfunction.md)                               | MED          | Yes        |
|                          | [binary\_shift\_right()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-shift-rightfunction.md)                             | MED          | Yes        |
|                          | [binary\_xor()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/binary-xorfunction.md)                                              | MED          | Yes        |
|                          | [bitset\_count\_ones()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/bitset-count-onesfunction.md)                               | MED          | Yes        |
|                          |                                                                                                                                                       |              |             |
| General                  | bin()       | High         | Yes      |
|                   | bin_at()    | High         | Yes      |
|                          | extend     | Med          | Yes        |
|                          | parse                                                                                                                                                 | Defer        |             |
|                          | parse-where                                                                                                                                           | Defer        |             |
