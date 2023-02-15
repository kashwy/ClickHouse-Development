|Area|Function/Operator|Priority|Easiness|Rank|Completed|Comment| Release |  Date|  
| - | - | - | - | - | - | - | - | -|
||||||||
||count operator|High|Easy||Done||v22.8.6.73-clib|Oct 26,2022|
||make-series operator|LOW|||Done||v22.8.1.4-clib|Aug 31,2022|
||print operator|LOW/Eval|Medium||Done||v22.8.1.1-clib|Aug 3,2022|
||lookup operator|High|Hard||Done||v22.8.9.26-clib|Nov 25,2022|
||top operator|High/Eval|Easy||Done||v22.8.6.73-clib|Oct 26,2022|
||top-hitters operator|High/Eval|Easy||Done||v22.8.6.73-clib|Oct 26,2022|
||join operator|High|Hard||Done||v22.8.9.26-clib|Nov 25,2022|
||top-nested operator|High/Eval||200 - 2022Dec|Done||v22.12 clib|Jan 26,2023|
||facet operator|||200 - 2023Jan|||
||range operator|Med/Eval|Medium|300 - 2023Jan|||v22.12 clib|Jan 26,2023|
||mv-apply operator|High|Hard|300 - GA Candidate|||
||parse operator|High|Hard|400 - GA Candidate|||
||parse-kv operator|Low|Medium-Hard|400 - GA Candidate|||
||parse-where operator|Low|Hard|400 - GA Candidate|||
||Let statement|High|Hard|300 - Post GA|||
||getschema operator|Low|Hard|Post GA|||
||invoke operator|Med|Hard|Post GA|||
||datatable operator|High|Easy|Post GA|||
||sample operator|LOW/Eval|Medium|Post GA|||
||sample-distinct operator|LOW/Eval|Medium|Post GA|||
||search operator|High/Eval|Medium-Hard|Post GA|||
||union operator|Low/Eval|Medium-Hard|Post GA|||
||toscalar()|High/Eval|Medium|Post GA|||
||reduce|LOW/Eval|Medium|Post GA|||
||materialize|Medium|Hard|Post GA|||
||as||Medium|Post GA|||
||with|||Post GA|||
||||||||
|String|reverse()||Easy||Done||v22.8.6.72-cli|	Oct 12,2022|
||[extractjson()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/extractjsonfunction.md)||Medium||Done||v22.8.6.72-clib|Oct 12,2022|
||[=~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/equals-operator.md)||Hard|300 - 2022Dec|||v22.12 clib|Jan 26,2023|
||[!~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-equals-operator.md)||Hard|300 - 2022Dec|||v22.12 clib|Jan 26,2023|
||[in~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/inoperator.md)||Hard|300 - 2022Dec|||v22.12 clib|Jan 26,2023|
||[!in~](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/not-in-operator.md)||Hard|300 - 2022Dec|||v22.12 clib|Jan 26,2023|
||||||||
|Dynamic|array\_reverse()||Easy||Done||v22.8.4.84-clib|Sep 15,2022|
||array\_rotate\_left()||Easy||Done||v22.8.4.84-clib|Sep 15,2022|
||array\_rotate\_right()||Easy||Done||v22.8.4.84-clib|Sep 15,2022|
||array\_shift\_left()||Easy||Done||v22.8.4.84-clib|Sep 15,2022|
||array\_shift\_right()||Easy||Done||v22.8.4.84-clib|Sep 15,2022|
||jaccard\_index()|EVAL|Hard||Done||v22.8.4.84-clib|Sep 15,2022|
||zip()|EVAL|Easy|300 - 2022Dec|Done|only arrays of the same type are supported|v22.8.4.84-clib|Sep 15,2022|
||bag\_keys()||Medium|Post GA|||
||bag\_merge()||Medium|Post GA|||
||bag\_remove\_keys()||Medium|Post GA|||
||treepath()|EVAL|Hard|Post GA|||
||||||||
|Window Functions|next()|MED|Medium|Post GA|||
||prev()|MED|Medium|Post GA|||
||row\_cumsum()|MED|Medium|Post GA|||
||row\_number()|MED|Medium|Post GA|||
||serialize operator|MED|Medium|Post GA|||
||row\_rank()|MED|Hard|Post GA|||
||row\_window\_function()|MED|Hard|Post GA|||
||||||||
|Conditional|[iff/iif](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/iiffunction)|High|Easy|300 - 2022Dec|Done||v22.12 clib|Jan 26,2023|
||[case()](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/casefunction)|High|Easy||Done||v22.8.8.4-clib|Nov 10,2022|
||[coalesce()](https://docs.microsoft.com/en-us/azure/data-explorer/kusto/query/coalescefunction)|Defer|Hard|Post GA|||
||||||||
|Time Series|time series analysis||||||
||series\_add()|LOW|Hard|Post GA|||
||[series\_fir()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-firfunction.md)|Eval|Hard|Post GA|||
||[series\_iir()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-iirfunction.md)|Eval|Hard|Post GA|||
||[series\_fit\_line()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-linefunction.md)|Eval|Hard|Post GA|||
||[series\_fit\_line\_dynamic()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-line-dynamicfunction.md)|Eval|Hard|Post GA|||
||[series\_fit\_2lines()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-2linesfunction.md)|Eval|Hard|Post GA|||
||[series\_fit\_2lines\_dynamic()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fit-2lines-dynamicfunction.md)|Eval|Hard|Post GA|||
||[series\_outliers()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-outliersfunction.md)|Eval|Hard|Post GA|||
||[series\_periods\_detect()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-periods-detectfunction.md)|Eval|Hard|Post GA|||
||[series\_periods\_validate()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-periods-validatefunction.md)|Eval|Hard|Post GA|||
||[series\_stats\_dynamic()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-stats-dynamicfunction.md)|Eval|Hard|Post GA|||
||[series\_stats()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-statsfunction.md)|Eval|Hard|Post GA|||
||[series\_fill\_backward()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-backwardfunction.md)|Eval|Hard|Post GA|||
||[series\_fill\_const()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-constfunction.md)|Eval|Hard|Post GA|||
||[series\_fill\_forward()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-forwardfunction.md)|Eval|Hard|Post GA|||
||[series\_fill\_linear()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/series-fill-linearfunction.md)|Eval|Hard|Post GA|||
||series\_outliers()|LOW|Hard|Post GA|||
||series\_pearson\_correlation()|LOW|Hard|Post GA|||
||series\_seasonal()|LOW|Hard|Post GA|||
||series\_decompose()|LOW|Hard|Post GA|||
||series\_decompose\_anomalies()|LOW|Hard|Post GA|||
||series\_decompose\_forecast()|LOW|Hard|Post GA|||
||series\_subtract()|LOW|Hard|Post GA|||
||series\_multiply()|LOW|Hard|Post GA|||
||series\_divide()|LOW|Hard|Post GA|||
||series\_equals()|LOW|Hard|Post GA|||
||series\_greater()|LOW|Hard|Post GA|||
||series\_greater\_equals()|LOW|Hard|Post GA|||
||series\_less()|LOW|Hard|Post GA|||
||series\_less\_equals()|LOW|Hard|Post GA|||
||series\_not\_equals()|LOW|Hard|Post GA|||
||||||||
|Aggregation|[count_distinct](https://learn.microsoft.com/en-us/azure/data-explorer/kusto/query/count-distinct-aggfunction)|High|||Done||v22.11.2.31-clib|Dec 09,2022|
||[count_distinctif](https://learn.microsoft.com/en-us/azure/data-explorer/kusto/query/count-distinctif-aggfunction)|High|||Done||v22.11.2.31-clib|Dec 09,2022|
||[take\_any()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/take-any-aggfunction.md)|Defer|Hard|200 - 2023Jan|||v22.12 clib|Jan 26,2023|
||[take\_anyif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/take-anyif-aggfunction.md)|Defer|Hard|200 - 2023Jan|||v22.12 clib|Jan 26,2023|
||[buildschema()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/buildschema-aggfunction.md)|Defer|Hard|Post GA|||
||[make_bag()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-bag-aggfunction.md)|Defer|Hard|Post GA|||
||[make_bag_if()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/make-bag-if-aggfunction.md)|Defer|Hard|Post GA|||
||[percentiles_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md)|Med|Hard|Post GA|||
||[percentilesw_array()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/percentiles-aggfunction.md)|Med|Hard|Post GA|||
||[variance()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/variance-aggfunction.md)|Defer|Hard|Post GA|||
||[varianceif()](https://github.com/microsoft/Kusto-Query-Language/blob/master/doc/varianceif-aggfunction.md)|Defer|Hard|Post GA|||
||||||||
|IPv4/IPv6|has\_any\_ipv4()|High|Medium|400 - 2023Jan|||
||has\_ipv4\_prefix()|High|Medium|400 - 2023Jan|||
||has\_any\_ipv4()|High|Medium|400 - 2023Jan|||
||has\_any\_ipv4\_prefix()|High|Medium|400 - 2023Jan|||
||has\_any\_ipv6()|High|Medium\_hard|not in doc - 2023Jan |||
||has\_ipv6\_prefix()|High|Medium\_hard|not in doc - 2023Jan |||
||has\_any\_ipv6()|High|Medium\_hard|not in doc - 2023Jan |||
||has\_any\_ipv6\_prefix()|High|Medium\_hard|not in doc - 2023Jan|||
||||||||
|Push to Next - OuT of Scope|consume operator|||||
||evaluate operator|||||
||externaldata operator|||||
||find operator|||||
||fork operator|||||
||partition operator|||||
||reduce operator|||||
||render operator|||||
||||||||
|Plugins|rolling\_percentile()|Hard||||
