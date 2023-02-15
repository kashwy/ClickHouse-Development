# Dev Test Sheet.

## String operators:

|Operator|Case-Sensitive|Example (yields true)|ClickHouse --|
|---|---|---|---|
|==|Yes| "aBc" == "aBc"| `==` |
|!=|Yes| "abc" != "ABC"| `!=` |
|=~|`No`| "abc" =~ "ABC"|  |
|!~|`No`| "aBc" !~ "xyz"|  |
|contains|`No`| "FabriKam" contains "BRik"| A  `ilike` '%b%'  |
|!contains|`No`| "Fabrikam" !contains "xyz"| A `not ilike` '%b%' |
|contains_cs|Yes| "FabriKam" contains_cs "Kam"| A `like` '%b%'|
|!contains_cs|Yes| "Fabrikam" !contains_cs "Kam"| A `not like` '%b%'|
|endswith|`No`|  "Fabrikam" endswith "Kam"| A  `ilike` '%b' |
|!endswith|`No`|  "Fabrikam" !endswith "brik"| A  `not ilike` '%b' |
|endswith_cs|Yes| "Fabrikam" endswith_cs "kam"| `endsWith`(haystack, pattern) |
|!endswith_cs|Yes|  "Fabrikam" !endswith_cs "brik"| `not endsWith`(haystack, pattern)  |
|has|`No`|  "North America" has "america"|  `hasTokenCaseInsensitive`(haystack, pattern) |
|!has|`No`|  "North America" !has "amer"|  `not hasTokenCaseInsensitive`(haystack, pattern)   |
|has_all|`No` |"North and South America" has_all("south", "north")|  |
|**has_any**|`No`  |"North America" has_any("south", "north")|  |
|has_cs|Yes|  "North America" has_cs "America"| `hasToken`(haystack, pattern)|
|!has_cs|Yes|  "North America" !has_cs "amer"|  `hasToken`(haystack, pattern) |
|hasprefix|`No`  |"North America" hasprefix "ame"| A `ilike` 'b%'|
|!hasprefix|`No`  |"North America" !hasprefix "mer"| A `not ilike` 'b%' |
|hasprefix_cs|Yes  |"North America" hasprefix_cs "Ame"| `startsWith`(haystack, pattern) |
|!hasprefix_cs|Yes  |"North America" !hasprefix_cs "CA"| `not startsWith`(haystack, pattern) |
|hassuffix|`No`|  "North America" hassuffix "ica"|  A `ilike` '%b' |
|!hassuffix|`No`|  "North America" !hassuffix "americ"|  A `not ilike` '%b' |
|hassuffix_cs|Yes|  "North America" hassuffix_cs "ica"| `endsWith`(haystack, pattern) |
|!hassuffix_cs|Yes|  "North America" !hassuffix_cs "icA"| `not endsWith`(haystack, pattern) |
|in|Yes|  "abc" in ("123", "345", "abc")| `in` |
|!in|Yes|  "bca" !in ("123", "345", "abc")| `not in` |
|in~|`No`|  "Abc" in~ ("123", "345", "abc")|  |
|!in~|`No`|  "bCa" !in~ ("123", "345", "ABC")|  |
|matches regex|Yes| "Fabrikam" matches regex "b.*k"| `match`(haystack, pattern)  |
|startswith|`No`|  "Fabrikam" startswith "fab"| A `ilike` 'b%' |
|!startswith|`No`|  "Fabrikam" !startswith "kam"| A `not ilike` 'b%' |
|startswith_cs|Yes|"Fabrikam" startswith_cs "Fab"| `startsWith`(haystack, pattern) |
|!startswith_cs|Yes|"Fabrikam" !startswith_cs "fab"| `not startsWith`(haystack, pattern) |

## regular test
| input | Sql result|expected | pass(Yes/NO)|Action|
|---|---|---|---|---|
|Customers \| where FirstName == 'Peter'|SELECT * FROM Customers WHERE FirstName = 'Peter'|-|-|-|
|Customers \| where FirstName != 'Peter'|FROM Customers WHERE FirstName != 'Peter'|-|-|-|
|Customers \| where FirstName =~ 'Peter'|-|-|-|-|
|Customers \| where FirstName !~ 'Peter'|-|-|-|-|
|Customers \| where FirstName contains 'pet'|SELECT * FROM Customers WHERE FirstName ILIKE '%Peter%'|-|-|-|
|Customers \| where FirstName !contains 'pet'|SELECT * FROM Customers WHERE NOT (FirstName ILIKE '%pet%')|-|-|-|
|Customers \| where FirstName contains_cs 'Pet'|SELECT * FROM Customers WHERE FirstName LIKE '%Pet%'|-|-|-|
|Customers \| where FirstName !contains_cs 'Pet'|SELECT * FROM Customers WHERE NOT (FirstName LIKE '%Pet%')|-|-|-|
|Customers \| where FirstName endswith 'er'|SELECT * FROM Customers WHERE FirstName ILIKE '%er'|-|-|-|
|Customers \| where FirstName !endswith 'pet'|SELECT * FROM Customers WHERE NOT (FirstName ILIKE '%pet')|-|-|-|
|Customers \| where FirstName endswith_cs 'pet'|SELECT * FROM Customers WHERE endsWith(FirstName, 'pet')|-|-|-|
|Customers \| where FirstName !endswith_cs 'pet'|SELECT * FROM Customers WHERE NOT endsWith(FirstName, 'pet')|-|-|-|
|Customers \| where Education has 'School'|SELECT * FROM Customers WHERE hasTokenCaseInsensitive(Education, 'School')|-|-|-|
|Customers \| where Education !has 'School'|SELECT * FROM Customers WHERE NOT hasTokenCaseInsensitive(Education, 'School')|-|-|-|
|Customers \| where Education has_all ('High', 'School')|-|-|-|-|
|Customers \| where Education has_any ('High', 'School')|-|-|-|-|
|Customers \| where Education has_cs 'School'|SELECT * FROM Customers WHERE hasToken(Education, 'School')|-|-|-|
|Customers \| where Education !has_cs 'School'|SELECT * FROM Customers WHERE NOT hasToken(Education, 'School')|-|-|-|
|Customers \| where Education hasprefix 'School'|-|-|-|-|
|Customers \| where Education !hasprefix 'School'|-|-|-|-|
|Customers \| where Education hasprefix_cs 'School'|-|-|-|-|
|Customers \| where Education !hasprefix_cs 'School'|-|-|-|-|
|Customers \| where Education hassuffix 'School'|-|-|-|-|
|Customers \| where Education !hassuffix 'School'|-|-|-|-|
|Customers \| where Education hassuffix_cs 'School'|-|-|-|-|
|Customers \| where Education !hassuffix_cs 'School'|-|-|-|-|
|Customers \| where FirstName in ('pet','Angel')|SELECT * FROM Customers WHERE FirstName IN ('pet', 'Angel')|-||-|
|Customers \| where FirstName !in ('pet','Angel')|SELECT * FROM Customers WHERE FirstName NOT IN ('pet', 'Angel')|-|-|-|
|Customers \| where FirstName in~ ('pet','Angel')|-|-|-|-|
|Customers \| where FirstName !in~ ('pet','Angel')|-|-|-|-|
|Customers \| where FirstName matches regex 'P.*r'|SELECT * FROM Customers WHERE match(FirstName, 'P.*r')|-|-|-|
|Customers \| where FirstName startswith 'pet'|SELECT * FROM Customers WHERE FirstName ILIKE 'pet%'|-|-|-|
|Customers \| where FirstName !startswith 'pet'|SELECT * FROM Customers WHERE NOT (FirstName ILIKE 'pet%')|-|-|-|
|Customers \| where FirstName startswith_cs 'Pet'|SELECT * FROM Customers WHERE startsWith(FirstName, 'Pet')|-|-|-|
|Customers \| where FirstName !startswith_cs 'Pet'|SELECT * FROM Customers WHERE NOT startsWith(FirstName, 'Pet')|-|-|-|