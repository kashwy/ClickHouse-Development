|Operator|Case-Sensitive|Example (yields true)|ClickHouse --|done|
|---|---|---|---|---|
|==|Yes| "aBc" == "aBc"| `==` |Y|
|!=|Yes| "abc" != "ABC"| `!=` |Y|
|=~|`No`| "abc" =~ "ABC"|  |
|!~|`No`| "aBc" !~ "xyz"|  |
|contains|`No`| "FabriKam" contains "BRik"| A  `ilike` '%b%'  |Y|
|!contains|`No`| "Fabrikam" !contains "xyz"| A `not ilike` '%b%' |Y|
|contains_cs|Yes| "FabriKam" contains_cs "Kam"| A `like` '%b%'|Y|
|!contains_cs|Yes| "Fabrikam" !contains_cs "Kam"| A `not like` '%b%'|Y|
|endswith|`No`|  "Fabrikam" endswith "Kam"| A  `ilike` '%b' |Y|
|!endswith|`No`|  "Fabrikam" !endswith "brik"| A  `not ilike` '%b' |Y|
|endswith_cs|Yes| "Fabrikam" endswith_cs "kam"| `endsWith`(haystack, pattern) |Y|
|!endswith_cs|Yes|  "Fabrikam" !endswith_cs "brik"| `not endsWith`(haystack, pattern)  |Y|
|has|`No`|  "North America" has "america"|  `hasTokenCaseInsensitive`(haystack, pattern) |Y|
|!has|`No`|  "North America" !has "amer"|  `not hasTokenCaseInsensitive`(haystack, pattern)   |Y|
|has_all|`No` |"North and South America" has_all("south", "north")|  |
|**has_any**|`No`  |"North America" has_any("south", "north")|  |
|has_cs|Yes|  "North America" has_cs "America"| `hasToken`(haystack, pattern)|Y|
|!has_cs|Yes|  "North America" !has_cs "amer"|  `hasToken`(haystack, pattern) |Y|
|hasprefix|`No`  |"North America" hasprefix "ame"| `ilike` (A,'% b%')|
|!hasprefix|`No`  |"North America" !hasprefix "mer"|  `not ilike`(A, '% b%')|
|hasprefix_cs|Yes  |"North America" hasprefix_cs "Ame"|`startsWith`(A,b) or `like` (A,'% b%') |
|!hasprefix_cs|Yes  |"North America" !hasprefix_cs "CA"| `not like`(A, '% b%') |
|hassuffix|`No`|  "North America" hassuffix "ica"|  A `ilike` '%b' |
|!hassuffix|`No`|  "North America" !hassuffix "americ"|  A `not ilike` '%b' |
|hassuffix_cs|Yes|  "North America" hassuffix_cs "ica"| `endsWith`(haystack, pattern) |
|!hassuffix_cs|Yes|  "North America" !hassuffix_cs "icA"| `not endsWith`(haystack, pattern) |
|in|Yes|  "abc" in ("123", "345", "abc")| `in` |Y|
|!in|Yes|  "bca" !in ("123", "345", "abc")| `not in` |Y|
|in~|`No`|  "Abc" in~ ("123", "345", "abc")|  |
|!in~|`No`|  "bCa" !in~ ("123", "345", "ABC")|  |
|matches regex|Yes| "Fabrikam" matches regex "b.*k"| `match`(haystack, pattern)  |Y|
|startswith|`No`|  "Fabrikam" startswith "fab"| A `ilike` 'b%' |Y|
|!startswith|`No`|  "Fabrikam" !startswith "kam"| A `not ilike` 'b%' |Y|
|startswith_cs|Yes|"Fabrikam" startswith_cs "Fab"| `startsWith`(haystack, pattern) |Y|
|!startswith_cs|Yes|"Fabrikam" !startswith_cs "fab"| `not startsWith`(haystack, pattern) |Y|



String Function
|Function Name|ClickHouse|
|---|---|
|base64_encode_tostring()|  |
|base64_encode_fromguid()|  |
|base64_decode_tostring()|  |
|base64_decode_toarray()|  |
|base64_decode_toguid()|  |
|countof()|  |
|extract()|  |
|extract_all()|  |
|extractjson()|  |
|has_any_index()|  |
|indexof()|  |
|isempty()| empty() |
|isnotempty()| notEmpty() |
|isnotnull()|  isNotNull ()|
|isnull()| isNull() |
|parse_command_line()|  |
|parse_csv()|  |
|parse_ipv4()|  |
|parse_ipv4_mask()|  |
|parse_ipv6()|  |
|parse_ipv6_mask()|  |
|parse_json()|  |
|parse_url()|  |
|parse_urlquery()|  |
|parse_version()|  |
|replace_regex()|  |
|reverse()|  |
|split()|  |
|strcat()|  |
|strcat_delim()|  |
|strcmp()|  |
|strlen()|  |
|strrep()|  |
|substring()|  |
|tolower()| upper() |
|toupper()| upper() |
|translate()|  |
|trim()| trim-- |
|trim_end()| |
|trim_start()| |
|url_decode()| |
|url_encode()| |








### Count all Events    
```kusto 
events 
| count
```
### Take a number of events   
```kusto 
events
| take 5
```
### Index of Item in Array    
```kusto 
events | where array_index_of(event_ids, "some_string_event_ids")==1 | count
```
### Array Contains Item    
```kusto
events | where set_has_element(event_ids, "some_string_event_ids") | count
```
### Project specific Columns    
```kusto
events
| project qid, payload
| take 1
```
### Search for IP and Port    
```kusto
events
| where source_ip_v4=="10.1.1.15" and source_port==80
| take 1
```
### Case insensitive startswith    
```kusto
events 
| where username startswith "User" 
| take 1 
| project username
```
### Case insensitive does not startwith    
```kusto
events 
| where username !startswith "User" 
| take 1 
| project username
```
### Case insensitive endswith    
```kusto
events 
| where username endswith "er4" 
| take 1 
| project username
```
### Case sensitive startwith    
```kusto
events 
| where username startswith_cs "User" 
| take 1 
| project username
```
### Regular Expression search    
```kusto
events 
| where username matches regex ".ser[0-9]+" 
| take 1 
| project username
```
### Case sensitive string equality   
```kusto
events 
| where username == "user1" 
| take 1
```
### Case insensitive string equality   
```kusto
events 
| where username =~ "User1" 
| take 1 
| project username
```
### Case insensitive string in list   
```kusto
events 
| where username in~ ("user1","User2") 
| count
```
### Has all string tokens   
```kusto
events 
| where payload has_all ("Some","event") 
| take 1 
| project payload
```
### Case insensitive has any string tokens   
```kusto
events 
| where payload has_any( "Some","event") 
| take 1 
| project payload
```
### Case insenstive has string token    
```kusto
events 
| where payload has "some" 
| take 1 
| project payload
```
### Case senstive has string token   
```kusto
events 
| where payload has_cs "Some" 
| take 1 
| project payload
```
