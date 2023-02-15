# Kusto Query Language Support in ClickHouse Test Plan - phase 1    


# Table of Contents   
[Overview](#overview)   

[Test process](#TestProcess)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Manual testing](#TestProcess01)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Functional test](#TestProcess02)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Performance test](#TestProcess03)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Integration Tests](#TestProcess04)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Stress test](#TestProcess05)           
[Test Cases for KQL](#test000)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Description](#test00)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[1.  Query only has table name](#test01)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[2.  Query has Column Selection ](#test02)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.  Query has limit](#test03)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[4.  Query has second limit with bigger value](#test04)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[5.  Query has second limit with smaller value](#test05)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[6.  Query has second Column selection](#test06)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[7.  Query has second Column selection with extra column](#test07)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[8.  Query with desc sort ](#test08)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[9.  Query with asc sort](#test09)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[10.  Query with sort (without keyword asc desc)](#test10)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[11.  Query with sort 2 Columns with different direction](#test11)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[12.  Query with second sort](#test12)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[13.  Test String Equals (`==`)](#test13)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[14.  Test String Not equals (`!=`)](#test14)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[15.  Test Filter using a list (`in`)](#test15)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[16.  Test Filter using a list (`!in`)](#test16)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[17.  Test Filter using common string operations (`contains_cs`)](#test17)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[18.  Test Filter using common string operations (`startswith_cs`)](#test18)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[19.  Test Filter using common string operations (`endswith_cs`)](#test19)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[20. Test Filter using numerical equal (`==`)](#test20)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[21. Test Filter using numerical great and less (`>` , `<`)](#test21)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[22. Test Filter using multi where](#test22)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[23.  Test Aggregation `count()` ](#test23)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[24.  Test Aggregation `sum()` ](#test24)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[25.  Test Aggregation `avg()` ](#test25)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[26.  Test Aggregation `min()` ](#test26)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[27.  Test Aggregation `max()` ](#test27)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[28.  Test Aggregation by time intervals (`bin`) ](#test28)    


# Overview:<a name="overview"></a>    



 This is the phase 1 test plan for the Kusto Query Language support in the ClickHouse.

 The requirement document can be found here:  
 https://github.ibm.com/ClickHouse/issue-repo/blob/master/docs/features/KQL/phase1/phase1-KQL-requirements.md
 
 The design document can be found here:  
 https://github.ibm.com/ClickHouse/issue-repo/blob/master/docs/features/KQL/phase1/phase1-KQL-design.md


# Test process:<a name="TestProcess"></a>    
## &nbsp;&nbsp;&nbsp;&nbsp;Manual testing:<a name="TestProcess01"></a>    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Use manual test to verify the correctness of the SQL and result, generate test SQL files for the functional test.    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Start clickhouse server and clickhouse client    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Change directory to `programs/clickhouse-server` and run it with `./clickhouse-server`.    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Run `programs/clickhouse-client/clickhouse-client`. (in another terminal)    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Run SQLs in the test cases in the client, check the correctness, and save the correct SQL to .sql file    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;If the expected result of a test is a server error. use the following format:    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`Customers | project FirstName,LastName,Occupation | take 3 | project FirstName,LastName,Education; -- { serverError 42 }` 

## &nbsp;&nbsp;&nbsp;&nbsp;Functional test<a name="TestProcess02"></a>    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Each functional test sends one or multiple queries to the running ClickHouse server and compares the result with reference.


&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;create the test files with formated name, The name of the test starts with a five-digit prefix followed by a descriptive name, such as `01847_kql_table_only.sh`. To choose the prefix, find the largest prefix already present in the directory, and increment it by one.    

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Put the test files create in manual testing in the `tests/queries/0_stateless` directory and then generate .reference file in the following way:    
 `clickhouse-client -n --testmode < 01847_kql_table_only.h > 01847_kql_table_only.reference`

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Run th test like:
`<path to clickhouse-client> tests/clickhouse-test 01847_kql_table_only`

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Testing a Distributed Query will be added if neceedssary.   

## &nbsp;&nbsp;&nbsp;&nbsp;Performance test<a name="TestProcess03"></a>    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To be added if necessary.   

## &nbsp;&nbsp;&nbsp;&nbsp;Integration Tests<a name="TestProcess04"></a>    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To be added if necessary.   

## &nbsp;&nbsp;&nbsp;&nbsp;Stress test<a name="TestProcess05"></a>           
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To be added if necessary.    

# Test Cases for KQL in Phase 1<a name="test000"></a>    

## Description:<a name="test00"></a>    

These test cases are for manual tests. and functional tests. we wil use a table for test as :


The test cases are created to cover as much as possible according to the  description of the issue #8687 and existing ARRAY JOIN behavior.   



use a Customer table for test:

|FirstName|	LastName	|Occupation	|Education|Age|
|---|---|---|---|---|
|Theodore|Diaz|Skilled Manual|Bachelors|28|
|Stephanie|Cox|Management|Bachelors|33|
|Peter|Nara|Skilled Manual|Graduate Degree|26|
|Latoya|Shen|Professional|Graduate Degree|25|
|Joshua|Lee|Professional|Partial College|26|
|Edward|Hernandez|Skilled Manual|High School|36|
|Dalton|Wood|Professional|Partial College|42|
|Christine|Nara|Skilled Manual|Partial College|33|
|Cameron|Rodriguez|Professional|Partial College|28|
|Angel|Stewart|Professional|Partial College|46|

```sql
DROP TABLE IF EXISTS Customers;
CREATE TABLE Customers
(    
    FirstName Nullable(String),
    LastName String, 
    Occupation String,
    Education String,
    Age UInt8
) ENGINE = Memory;

INSERT INTO Customers VALUES  ('Theodore','Diaz','Skilled Manual','Bachelors',28);
INSERT INTO Customers VALUES  ('Stephanie','Cox','Management','Bachelors',33);
INSERT INTO Customers VALUES  ('Peter','Nara','Skilled Manual','Graduate Degree',26);
INSERT INTO Customers VALUES  ('Latoya','Shen','Professional','Graduate Degree',25);
INSERT INTO Customers VALUES  ('Joshua','Lee','Professional','Partial College',26);
INSERT INTO Customers VALUES  ('Edward','Hernandez','Skilled Manual','High School',36);
INSERT INTO Customers VALUES  ('Dalton','Wood','Professional','Partial College',42);
INSERT INTO Customers VALUES  ('Christine','Nara','Skilled Manual','Partial College',33);
INSERT INTO Customers VALUES  ('Cameron','Rodriguez','Professional','Partial College',28);
INSERT INTO Customers VALUES  (NULL,'Stewart','Professional','Partial College',46);
```

## **Test Table Query,Column Selection, limit**

 1. **Query only has table name:**<a name="test01"></a>    
    `Test Query`: 
    ```
    Customer
    ```
    `Expected result:`  

    |FirstName|	LastName	|Occupation	|Education|Age|
    |---|---|---|---|---|
    |Theodore|Diaz|Skilled Manual|Bachelors|28|
    |Stephanie|Cox|Management|Bachelors|33|
    |Peter|Nara|Skilled Manual|Graduate Degree|26|
    |Latoya|Shen|Professional|Graduate Degree|25|
    |Joshua|Lee|Professional|Partial College|26|
    |Edward|Hernandez|Skilled Manual|High School|36|
    |Dalton|Wood|Professional|Partial College|42|
    |Christine|Nara|Skilled Manual|Partial College|33|
    |Cameron|Rodriguez|Professional|Partial College|28|
    |Angel|Stewart|Professional|Partial College|46|

2. **Query has Column Selection**<a name="test02"></a>
    `Test Query`:
    ```kusto
    Customers
    | project FirstName,LastName,Occupation    
    ```
   `Expected result:` 
    |FirstName|LastName|Occupation  |  
    |---|---|---|
    |Theodore|Diaz|Skilled Manual   |
    |Stephanie|Cox|Management       |
    |Peter|Nara|Skilled Manual      |
    |Latoya|Shen|Professional       |
    |Joshua|Lee|Professional        |
    |Edward|Hernandez|Skilled Manual|
    |Dalton|Wood|Professional       |
    |Christine|Nara|Skilled Manual  |
    |Cameron|Rodriguez|Professional |
    |Angel|Stewart|Professional     |

 3. **Query has limit**<a name="test03"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5
    ```
    and 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | limit 5
    ```
    `Expected result:` ( all row and all columns )

    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Theodore|Diaz|Skilled Manual   |
    |Stephanie|Cox|Management       |
    |Peter|Nara|Skilled Manual      |
    |Latoya|Shen|Professional       |
    |Joshua|Lee|Professional        |

 4. **Query has second limit with bigger value**<a name="test04"></a>  
     `Test Query`: 
    ```
    Customers2 | project FirstName,LastName,Occupation | take 5 | take 7
    ```
    `Expected result:` ( without affecting the first limit)
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Theodore|Diaz|Skilled Manual   |
    |Stephanie|Cox|Management       |
    |Peter|Nara|Skilled Manual      |
    |Latoya|Shen|Professional       |
    |Joshua|Lee|Professional        |

 5. **Query has second limit with smaller value**<a name="test05"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5
    | take 3
    ```
    `Expected result:` ( take the smaller limit)
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Theodore|Diaz|Skilled Manual   |
    |Stephanie|Cox|Management       |
    |Peter|Nara|Skilled Manual      |

 6. **Query has second Column selection**<a name="test06"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 3
    | project FirstName,LastName
    ```
    `Expected result:` ( take the less columns)  
    |FirstName|LastName|
    |---|---|
    |Theodore|Diaz|
    |Stephanie|Cox|
    |Peter|Nara|

 7. **Query has second Column selection with extra column**<a name="test07"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 3
    | project FirstName,LastName,Education
    ```
    `Expected result:` ( raise exception) 
    ```
     Error 
    'project' operator: Failed to resolve expression named 'Education'
    ```


## **Test Query with sort**  

8. **Query with desc sort**<a name="test08"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    | sort by FirstName desc
    ```
    and 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    | order by Occupation desc
    ```
    `Expected result:` 
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Theodore|Diaz|Skilled Manual  |
    |Peter|Nara|Skilled Manual     |
    |Latoya|Shen|Professional      |
    |Joshua|Lee|Professional       |
    |Stephanie|Cox|Management      |

9. **Query with asc sort**<a name="test09"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    | sort by Occupation asc
    ```
    `Expected result:` 
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Stephanie|Cox|Management      |
    |Joshua|Lee|Professional       |
    |Latoya|Shen|Professional      |
    |Peter|Nara|Skilled Manual     |
    |Theodore|Diaz|Skilled Manual  |

10. **Query with sort (without keyword asc desc)**<a name="test10"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    | sort by FirstName  
    ```
    and 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    | order by Occupation 
    ```
    `Expected result:` (default is desc)
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Theodore|Diaz|Skilled Manual  |
    |Peter|Nara|Skilled Manual     |
    |Latoya|Shen|Professional      |
    |Joshua|Lee|Professional       |
    |Stephanie|Cox|Management      |

11. **Query with sort 2 Columns with different direction**<a name="test11"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    |sort by Occupation asc, LastName desc
    ```
    `Expected result:`  
    |FirstName|LastName|Occupation   |
    |---|---|---|
    |Stephanie|Cox|Management        |
    |Latoya|Shen|Professional        |
    |Joshua|Lee|Professional         |
    |Peter|Nara|Skilled Manual       |
    |Theodore|Diaz|Skilled Manual    |    

12. **Query with second sort**<a name="test12"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | take 5 
    |sort by Occupation desc
    |sort by Occupation asc
    ```
    `Expected result:` (take the result of last sort)
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Stephanie|Cox|Management      |
    |Joshua|Lee|Professional       |
    |Latoya|Shen|Professional      |
    |Peter|Nara|Skilled Manual     |
    |Theodore|Diaz|Skilled Manual  |


## **Test Query with filter (where Case-Sensitive)**


13. **Test String Equals (`==`)**<a name="test13"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | where Occupation == 'Skilled Manual'
    ```
    `Expected result:`  
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Theodore|Diaz|Skilled Manual     |
    |Peter|Nara|Skilled Manual        |
    |Edward|Hernandez|Skilled Manual  |
    |Christine|Nara|Skilled Manual    |

14. **Test String Not equals (`!=`)**<a name="test14"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation    
    | where Occupation != 'Skilled Manual'
    ```
    `Expected result:`  
    |FirstName|LastName|Occupation  |
    |---|---|---|
    |Stephanie|Cox|Management       |
	|Latoya|Shen|Professional       |
	|Joshua|Lee|Professional        |
	|Dalton|Wood|Professional       |
	|Cameron|Rodriguez|Professional |
	|Angel|Stewart|Professional     |

15. **Test Filter using a list (`in`)**<a name="test15"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education    
    | where Education in  ('Bachelors','High School')
    ```
    `Expected result:`  

	|FirstName|LastName|Occupation|Education        |
    |---|---|---|---|
	|Theodore|Diaz|Skilled Manual|Bachelors         |
	|Stephanie|Cox|Management|Bachelors             |
	|Edward|Hernandez|Skilled Manual|High School    |

16. **Test Filter using a list (`!in`)**<a name="test16"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education    
    | where Education !in  ('Bachelors','High School')
    ```
    `Expected result:`  

	|FirstName|LastName|Occupation|Education        |
    |---|---|---|---|
	|Peter|Nara|Skilled Manual|Graduate Degree      |
	|Latoya|Shen|Professional|Graduate Degree       |
	|Joshua|Lee|Professional|Partial College        |
	|Dalton|Wood|Professional|Partial College       |
	|Christine|Nara|Skilled Manual|Partial College  |
	|Cameron|Rodriguez|Professional|Partial College |
	|Angel|Stewart|Professional|Partial College     |

17. **Test Filter using common string operations (`contains_cs`)**<a name="test17"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education  
    | where Education contains_cs   'Coll'
    ```
    `Expected result:`  

	|FirstName|LastName|Occupation|Education        |
    |---|---|---|---|
	|Joshua|Lee|Professional|Partial College        |
	|Dalton|Wood|Professional|Partial College       |
	|Christine|Nara|Skilled Manual|Partial College  |
	|Cameron|Rodriguez|Professional|Partial College |
	|Angel|Stewart|Professional|Partial College     |

18. **Test Filter using common string operations (`startswith_cs`)**<a name="test18"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education
    | where Occupation startswith_cs  'Prof'
    ```
    `Expected result:`  

	|FirstName|LastName|Occupation|Education        |
    |---|---|---|---|
	|Latoya|Shen|Professional|Graduate Degree       |
	|Joshua|Lee|Professional|Partial College        |
	|Dalton|Wood|Professional|Partial College       |
	|Cameron|Rodriguez|Professional|Partial College |
	|Angel|Stewart|Professional|Partial College     |

19. **Test Filter using common string operations (`endswith_cs`)**<a name="test19"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education
    | where FirstName endswith_cs   'a'
    ```
    `Expected result:`  

	|FirstName|LastName|Occupation|Education        |
    |---|---|---|---|
    |Latoya|Shen|Professional|Graduate Degree|
    |Joshua|Lee|Professional|Partial College|

20. **Test Filter using numerical equal (`==`)**<a name="test20"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education,Age
    | where Age == 26
    ```
    `Expected result:`  
	|FirstName|LastName|Occupation|Education        |Age|
    |---|---|---|---|---|
    |Joshua   |Lee     |Professional  |Partial College| 26|
    |Peter    |Nara    |Skilled Manual|Graduate Degree| 26|

21. **Test Filter using numerical great and less (`>` , `<`)**<a name="test21"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education,Age
    | where Age > 30 and Age < 40
    ```
    `Expected result:`  
	|FirstName|LastName|Occupation|Education        |Age|
    |---|---|---|---|---|
    |Stephanie|Cox      |Management    |Bachelors      | 33|
    |Edward   |Hernandez|Skilled Manual|High School    | 36|
    |Christine|Nara     |Skilled Manual|Partial College| 33|

22. **Test Filter using multi where**<a name="test22"></a>  
     `Test Query`: 
    ```
    Customers
    | project FirstName,LastName,Occupation,Education,Age
    | where Age > 30 
    | where Occupation == 'Professional'
    ```
    `Expected result:`  
	|FirstName|LastName|Occupation|Education        |Age|
    |---|---|---|---|---|
    |Dalton   |Wood    |Professional|Partial College| 42|
    |Angel    |Stewart |Professional|Partial College| 46|

## **Test Query with Aggregation**

23. **Test Aggregation `count()`**<a name="test23"></a>  
     `Test Query`: 
    ```
    Customers
    |summarize count() by Occupation
    ```
    `Expected result:`  
    |Occupation	|count_|
    |---|---|
    |Skilled Manual|4|
    |Management|	1|
    |Professional|	5|

24. **Test Aggregation `sum()`**<a name="test24"></a>  
     `Test Query`: 
    ```
    Customers
    |summarize  sum(Age) by Occupation
    ```
    `Expected result:`  
    |Occupation	|total_age|
    |---|---|
    |Skilled Manual|123|
    |Management|	33|
    |Professional|	167|

25. **Test Aggregation `avg()`**<a name="test25"></a>  
     `Test Query`: 
    ```
    Customers
    |summarize avg(Age) by Occupation
    ```
    `Expected result:`  
    |Occupation	|avg_age|
    |---|---|
    |Skilled Manual|30.75|
    |Management|	33|
    |Professional|	33.4|

26. **Test Aggregation `min()`**<a name="test26"></a>  
     `Test Query`: 
    ```
    Customers
    |summarize min(Age) by Occupation
    ```
    `Expected result:`  
    |Occupation	|min_age|
    |---|---|
    |Skilled Manual|26|
    |Management|	33|
    |Professional|	25|

27. **Test Aggregation `max()`**<a name="test27"></a>  
     `Test Query`: 
    ```
    Customers
    |summarize  max(Age) by Occupation
    ```
    `Expected result:`  
    |Occupation	|min_age|
    |---|---|
    |Skilled Manual|36|
    |Management|	33|
    |Professional|	46|

28. **Test Aggregation by time intervals (`bin`)**<a name="test28"></a>  
     `Test Query`: 
    ```
    Customers
    |summarize count() by bin(Age, 10) 
    ```
    `Expected result:`  
    |Age	|count_|
    |---|---|
    |20|5|
    |30|3|
    |40|2|