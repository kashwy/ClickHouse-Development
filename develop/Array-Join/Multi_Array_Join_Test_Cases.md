# Multiple ARRAY JOIN (Cartesian Product of Arrays) Test Cases    


&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[Description](#test00)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[1. Multiple ARRAY JOIN of 2 arrays whithout empty array](#test01)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[2. Multiple ARRAY JOIN of 2 arrays whithout empty array  (LEFT JOIN)](#test02)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3. Multiple ARRAY JOIN of 2 arrays with empty array](#test03)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[4. Multiple ARRAY JOIN of 2 arrays with empty array (LEFT JOIN case 1)](#test04)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[5. Multiple ARRAY JOIN of 2 arrays with empty array (LEFT JOIN case 2)](#test05)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[6. Multiple ARRAY JOIN of 2 arrays with empty array (LEFT JOIN case 3)](#test06)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[7. Multiple ARRAY JOIN of 2 arrays with alias](#test07)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[8. Multiple ARRAY JOIN of 2 arrays with referring a none exsit alias](#test08)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[9. Multiple ARRAY JOIN of 2 arrays with Nullable array](#test09)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[10. Multiple ARRAY JOIN of 2 arrays with JOIN](#test10)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[11. Multiple ARRAY JOIN of 3 arrays whithout empty array](#test11)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[12. Multiple ARRAY JOIN 2 of 3 arrays](#test12)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[13. Multiple ARRAY JOIN with ARRAY JOIN multiple arrays](#test13)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[14. Multiple ARRAY JOIN with Nested Data Structure](#test14)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[15. Multiple ARRAY JOIN with Nested Data Structure include empty items](#test15)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[16. Multiple ARRAY JOIN with Nested Data Structure include empty items (LEFT JOIN)](#test16)  
## Description:<a name="test00"></a>    
The test cases are created to cover as much as possible according to the  description of the issue #8687 and existing ARRAY JOIN behaviour.   

MULTIPLE ARRAY JOIN is to produce cartesian product of arrays, the test cases try to cover:   
-  MULTIPLE ARRAY JOIN of 2 arrays.    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To prove the correctness of at least 2 array     

-  MULTIPLE ARRAY JOIN of 3 arrays.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To prove the correctness more than 2 array    

-  MULTIPLE ARRAY JOIN of Nested Data Structure.    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;To prove the correctness on Nested Data Structure.    

- Some behaviour that may affect MULTIPLE ARRAY JOIN:  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Like : ARRAY JOIN with JOIN,  ARRAY JOIN with Nullable etc.    
 
## 1. Multiple ARRAY JOIN of 2 arrays whithout empty array:<a name="test01"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
    </pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|Steak  |Wine       |
           1|Steak  |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);

SELECT * FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks;

DROP TABLE IF EXISTS test_multi_array_join;
```
    
    

## 2. Multiple ARRAY JOIN of 2 arrays whithout empty array  (LEFT JOIN):<a name="test02"></a>    
Test Case:  `LEFT ARRAY JOIN arr1 ARRAY JOIN arr2`, `ARRAY JOIN arr1 LEFT ARRAY JOIN arr2`, `LEFT ARRAY JOIN arr1 LEFT ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
    </pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|Steak  |Wine       |
           1|Steak  |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);

SELECT * FROM test_multi_array_join LEFT ARRAY JOIN meals ARRAY JOIN drinks;
SELECT * FROM test_multi_array_join ARRAY JOIN meals LEFT ARRAY JOIN drinks;
SELECT * FROM test_multi_array_join LEFT ARRAY JOIN meals LEFT ARRAY JOIN drinks;

DROP TABLE IF EXISTS test_multi_array_join;
```
    
    
    
    

## 3. Multiple ARRAY JOIN of 2 arrays with empty array:<a name="test03"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|
           3|['Lamb']                    |[]                   |
           4|[]                          |['coca','soda']      |

&nbsp;
&nbsp;
&nbsp;
    </pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|Steak  |Wine       |
           1|Steak  |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);
INSERT INTO test_multi_array_join VALUES (3, ['Lamb'],[]);
INSERT INTO test_multi_array_join VALUES (4, [],['coca','soda']);  

SELECT * FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks;
DROP TABLE IF EXISTS test_multi_array_join; 
```
    
    

## 4. Multiple ARRAY JOIN of 2 arrays with empty array (LEFT JOIN case 1):<a name="test04"></a>    
Test Case:  `LEFT ARRAY JOIN arr1 ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|
           3|['Lamb']                    |[]                   |
           4|[]                          |['coca','soda']      |

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
    </pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|Steak  |Wine       |
           1|Steak  |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
           4|       |coca       |
           4|       |soda       |
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);
INSERT INTO test_multi_array_join VALUES (3, ['Lamb'],[]);
INSERT INTO test_multi_array_join VALUES (4, [],['coca','soda']);  

SELECT * FROM test_multi_array_join LEFT ARRAY JOIN meals ARRAY JOIN drinks;
DROP TABLE IF EXISTS test_multi_array_join; 
```
    

## 5. Multiple ARRAY JOIN of 2 arrays with empty array (LEFT JOIN case 2):<a name="test05"></a>    
Test Case:  `ARRAY JOIN arr1 LEFT ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|
           3|['Lamb']                    |[]                   |
           4|[]                          |['coca','soda']      |

&nbsp;
&nbsp;
&nbsp;


</pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|Steak  |Wine       |
           1|Steak  |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
           3|Lamb   |           | 
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);
INSERT INTO test_multi_array_join VALUES (3, ['Lamb'],[]);
INSERT INTO test_multi_array_join VALUES (4, [],['coca','soda']);  

SELECT * FROM test_multi_array_join ARRAY JOIN meals LEFT ARRAY JOIN drinks;
DROP TABLE IF EXISTS test_multi_array_join; 
```




## 6. Multiple ARRAY JOIN of 2 arrays with empty array (LEFT JOIN case 3):<a name="test06"></a>    
Test Case:  `LEFT ARRAY JOIN arr1 LEFT ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|
           3|['Lamb']                    |[]                   |
           4|[]                          |['coca','soda']      |

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
</pre>
</td>
<td>

<pre>

restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|Steak  |Wine       |
           1|Steak  |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
           3|Lamb   |           |
           4|       |coca       |
           4|       |soda       |  

</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);
INSERT INTO test_multi_array_join VALUES (3, ['Lamb'],[]);
INSERT INTO test_multi_array_join VALUES (4, [],['coca','soda']);  

SELECT * FROM test_multi_array_join LEFT ARRAY JOIN meals LEFT ARRAY JOIN drinks;
DROP TABLE IF EXISTS test_multi_array_join; 
```



## 7. Multiple ARRAY JOIN of 2 arrays with alias:<a name="test07"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2 as alias`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
    </pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks               |d          |
------------+-------+---------------------+-----------+
           1|Salmon |['Wine','Beer']      |Wine       |
           1|Salmon |['Wine','Beer']      |Beer       |
           1|Steak  |['Wine','Beer']      |Wine       |
           1|Steak  |['Wine','Beer']      |Beer       |  
           1|Chicken|['Wine','Beer']      |Wine       |
           1|Chicken|['Wine','Beer']      |Beer       |
           2|Sushi  |['Tea','Apple Juice']|Tea        |
           2|Sushi  |['Tea','Apple Juice']|Apple Juice|
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);

SELECT  restaurantid,meals, drinks, d FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks as d;

DROP TABLE IF EXISTS test_multi_array_join;
```
    

## 8. Multiple ARRAY JOIN of 2 arrays with referring a none exsit alias:<a name="test08"></a>    
Test Case:  `SELECT alia FROM table ARRAY JOIN arr1 ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|

</pre>
</td>
<td>

<pre>
Code: 42. DB::Exception: ARRAY JOIN requires an argument
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);

SELECT  restaurantid,meals, drinks, d FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks;

DROP TABLE IF EXISTS test_multi_array_join;
```


## 9. Multiple ARRAY JOIN of 2 arrays with Nullable array:<a name="test09"></a>    
Test Case:  ` ARRAY JOIN arr1 ARRAY JOIN arr2` (arr1 is Nullable)
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                  |drinks               |
------------+-----------------------+---------------------+
           1|['Salmon','','Chicken']|['Wine','Beer']      |
           2|['Sushi']              |['Tea','Apple Juice']|

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
</pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |
------------+-------+-----------+
           1|Salmon |Wine       |
           1|Salmon |Beer       |
           1|       |Wine       |
           1|       |Beer       |
           1|Chicken|Wine       |
           1|Chicken|Beer       |
           2|Sushi  |Tea        |
           2|Sushi  |Apple Juice|
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(Nullable(String)), drinks Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', null,'Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);

SELECT  restaurantid,meals, drinks, d FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks;

DROP TABLE IF EXISTS test_multi_array_join;
```



## 10. Multiple ARRAY JOIN of 2 arrays with JOIN:<a name="test10"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
Table 1:
restaurantid|meals                       |drinks               |
------------+----------------------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']      |
           2|['Sushi']                   |['Tea','Apple Juice']|

</pre>
<pre>
Table 2:
restaurantid|chef|
------------+----+
           1|John|
           2|Bob |
</pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks     |chef|
------------+-------+-----------+----+
           1|Salmon |Wine       |John|
           1|Salmon |Beer       |John|
           1|Steak  |Wine       |John|
           1|Steak  |Beer       |John|
           1|Chicken|Wine       |John|
           1|Chicken|Beer       |John|
           2|Sushi  |Tea        |Bob |
           2|Sushi  |Apple Juice|Bob |
&nbsp;
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;
DROP TABLE IF EXISTS test_multi_array_join2;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String)) ENGINE Memory;
CREATE TABLE test_multi_array_join2 (restaurantid UInt8, chef String) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice']);

INSERT INTO test_multi_array_join2 VALUES (1, 'John');
INSERT INTO test_multi_array_join2 VALUES (2, 'Bob');

SELECT restaurantid,meals,drinks, chef FROM test_multi_array_join JOIN test_multi_array_join2 b on a.restaurantid = b.restaurantid  ARRAY JOIN meals ARRAY JOIN drinks;

DROP TABLE IF EXISTS test_multi_array_join;
```
    
    

## 11. Multiple ARRAY JOIN of 3 arrays whithout empty array:<a name="test11"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2 ARRAY JOIN arr3`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks         |desserts            |
------------+----------------------------+---------------+--------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']|['Ice Cream','Cake']|
           2|['Sushi']                   |['Tea','coffe']|['Cookie']          |

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
    </pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks|desserts |
------------+-------+------+---------+
           1|Salmon |Wine  |Ice Cream|
           1|Salmon |Wine  |Cake     |
           1|Salmon |Beer  |Ice Cream|
           1|Salmon |Beer  |Cake     |
           1|Steak  |Wine  |Ice Cream|
           1|Steak  |Wine  |Cake     |
           1|Steak  |Beer  |Ice Cream|
           1|Steak  |Beer  |Cake     |
           1|Chicken|Wine  |Ice Cream|
           1|Chicken|Wine  |Cake     |
           1|Chicken|Beer  |Ice Cream|
           1|Chicken|Beer  |Cake     |
           2|Sushi  |Tea   |Cookie   |
           2|Sushi  |coffe |Cookie   |
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String), desserts Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer'],['Ice Cream','Cheese Cake']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','Apple Juice'],['Cookie']);

SELECT * FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks ARRAY JOIN desserts;

DROP TABLE IF EXISTS test_multi_array_join;
```
    

## 12. Multiple ARRAY JOIN 2 of 3 arrays:<a name="test12"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2 of (arr1,arr2,arr3)
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks         |desserts             |
------------+----------------------------+---------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']|['Ice Cream','Cake'] |
           2|['Sushi']                   |['Tea','coffe']|['Cookie','Tiramisu']|

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
</pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks|desserts             |
------------+-------+------+---------------------+
           1|Salmon |Wine  |['Ice Cream','Cake'] |
           1|Salmon |Beer  |['Ice Cream','Cake'] |
           1|Steak  |Wine  |['Ice Cream','Cake'] |
           1|Steak  |Beer  |['Ice Cream','Cake'] |
           1|Chicken|Wine  |['Ice Cream','Cake'] |
           1|Chicken|Beer  |['Ice Cream','Cake'] |
           2|Sushi  |Tea   |['Cookie','Tiramisu']|
           2|Sushi  |coffe |['Cookie','Tiramisu']|
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String), desserts Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer'],['Ice Cream','Cake']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','coffe'],['Cookie','Tiramisu']);

SELECT * FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks, desserts;

DROP TABLE IF EXISTS test_multi_array_join;
```    
    

## 13. Multiple ARRAY JOIN with ARRAY JOIN multiple arrays:<a name="test13"></a>    
Test Case:  `ARRAY JOIN arr1 ARRAY JOIN arr2, arr3` (arr2 and arr3 must have same size)
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
restaurantid|meals                       |drinks         |desserts             |
------------+----------------------------+---------------+---------------------+
           1|['Salmon','Steak','Chicken']|['Wine','Beer']|['Ice Cream','Cake'] |
           2|['Sushi']                   |['Tea','coffe']|['Cookie','Tiramisu']|

&nbsp;
&nbsp;
&nbsp;
&nbsp;
&nbsp;
</pre>
</td>
<td>

<pre>
restaurantid|meals  |drinks|desserts |
------------+-------+------+---------+
           1|Salmon |Wine  |Ice Cream|
           1|Steak  |Wine  |Ice Cream|
           1|Chicken|Wine  |Ice Cream|
           1|Salmon |Beer  |Cake     |
           1|Steak  |Beer  |Cake     |
           1|Chicken|Beer  |Cake     |
           2|Sushi  |Tea   |Cookie   |
           2|Sushi  |coffe |Tiramisu |
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (restaurantid UInt8, meals Array(String), drinks Array(String), desserts Array(String)) ENGINE Memory;

INSERT INTO test_multi_array_join VALUES (1, ['Salmon', 'Steak','Chicken'],['Wine','Beer'],['Ice Cream','Cake']);
INSERT INTO test_multi_array_join VALUES (2, ['Sushi'],['Tea','coffe'],['Cookie','Tiramisu']);

SELECT * FROM test_multi_array_join ARRAY JOIN meals ARRAY JOIN drinks;

DROP TABLE IF EXISTS test_multi_array_join;
```

## 14. Multiple ARRAY JOIN with Nested Data Structure:<a name="test14"></a>    
Test Case:  `ARRAY JOIN nested1 ARRAY JOIN nested2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
  |                person                    |                 properties                |  
id|------------------------------------------+-------------------------------------------|
  |person.name        |person.surname        |properties.key        |properties.value    |
--+-------------------+----------------------+----------------------+--------------------+
 1|['Thomas','Michel']|['Aquinas','Foucault']|['profession','alive']|['philosopher','no']|
 2|['Thomas','Nicola']|['Edison','Tesla']    |['profession','alive']|['inventor','no']   |
&nbsp;
&nbsp;
&nbsp;
&nbsp;
</pre>
</td>
<td>

<pre>
id|person.name|person.surname|properties.key|properties.value|
--+-----------+--------------+--------------+----------------+
 1|Michel     |Foucault      |profession    |philosopher     |
 1|Michel     |Foucault      |alive         |no              |
 1|Thomas     |Aquinas       |profession    |philosopher     |
 1|Thomas     |Aquinas       |alive         |no              |
 2|Nicola     |Tesla         |profession    |inventor        |
 2|Nicola     |Tesla         |alive         |no              |
 2|Thomas     |Edison        |profession    |inventor        |
 2|Thomas     |Edison        |alive         |no              |
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (
    id UInt64, 
    person Nested (name String,surname String ),
    properties Nested (key String,value String)
) Engine=MergeTree ORDER BY id;
 
INSERT INTO test_multi_array_join VALUES (1, ['Thomas', 'Michel'], ['Aquinas', 'Foucault'], ['profession', 'alive'], ['philosopher', 'no']);
INSERT INTO test_multi_array_join VALUES (2, ['Thomas', 'Nicola'], ['Edison', 'Tesla'], ['profession', 'alive'], ['inventor', 'no']);

SELECT * FROM test_multi_array_join ARRAY JOIN person ARRAY JOIN properties order by id, person.name;

DROP TABLE IF EXISTS test_multi_array_join;
```


## 15. Multiple ARRAY JOIN with Nested Data Structure include empty items:<a name="test15"></a>    
Test Case:  `ARRAY JOIN nested1 ARRAY JOIN nested2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
  |                person                    |                 properties                |  
id|------------------------------------------+-------------------------------------------|
  |person.name        |person.surname        |properties.key        |properties.value    |
--+-------------------+----------------------+----------------------+--------------------+
 1|['Thomas','Michel']|['Aquinas','Foucault']|['profession','alive']|['philosopher','no']|
 2|[]                 |[]                    |['profession','alive']|['inventor','no']   |
 3|['Thomas','Nicola']|['Edison','Tesla']    |[]                    |[]                  |

</pre>
</td>
<td>

<pre>
id|person.name|person.surname|properties.key|properties.value|
--+-----------+--------------+--------------+----------------+
 1|Michel     |Foucault      |profession    |philosopher     |
 1|Michel     |Foucault      |alive         |no              |
 1|Thomas     |Aquinas       |profession    |philosopher     |
 1|Thomas     |Aquinas       |alive         |no              |
 &nbsp;
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (
    id UInt64, 
    person Nested (name String,surname String ),
    properties Nested (key String,value String)
) Engine=MergeTree ORDER BY id;
 
INSERT INTO test_multi_array_join VALUES (1, ['Thomas', 'Michel'], ['Aquinas', 'Foucault'], ['profession', 'alive'], ['philosopher', 'no']);
INSERT INTO test_multi_array_join VALUES (2, [], [], ['profession', 'alive'], ['inventor', 'no']);
INSERT INTO test_multi_array_join VALUES (3, ['Thomas', 'Nicola'], ['Edison', 'Tesla'], [], []);

SELECT * FROM test_multi_array_join ARRAY JOIN person ARRAY JOIN properties order by id, person.name;

DROP TABLE IF EXISTS test_multi_array_join;
```


## 16. Multiple ARRAY JOIN with Nested Data Structure include empty items (LEFT JOIN):<a name="test16"></a>    
Test Case:  `LEFT ARRAY JOIN nested1 LEFT ARRAY JOIN nested2`
<table>
<tr>
<th>Table Contents</th>
<th>Expected Result</th>
</tr>
<tr>
<td>
<pre>
  |                person                    |                 properties                |  
id|------------------------------------------+-------------------------------------------|
  |person.name        |person.surname        |properties.key        |properties.value    |
--+-------------------+----------------------+----------------------+--------------------+
 1|['Thomas','Michel']|['Aquinas','Foucault']|['profession','alive']|['philosopher','no']|
 2|[]                 |[]                    |['profession','alive']|['inventor','no']   |
 3|['Thomas','Nicola']|['Edison','Tesla']    |[]                    |[]                  |
&nbsp;
&nbsp;
&nbsp;

</pre>
</td>
<td>

<pre>
id|person.name|person.surname|properties.key|properties.value|
--+-----------+--------------+--------------+----------------+
 1|Michel     |Foucault      |profession    |philosopher     |
 1|Michel     |Foucault      |alive         |no              |
 1|Thomas     |Aquinas       |profession    |philosopher     |
 1|Thomas     |Aquinas       |alive         |no              |
 2|           |              |profession    |inventor        |
 2|           |              |alive         |no              |
 3|Nicola     |Tesla         |              |                |
 3|Thomas     |Edison        |              |                |
</pre>

</td>
</tr>
</table>   

SQL:
```sql
DROP TABLE IF EXISTS test_multi_array_join;

CREATE TABLE test_multi_array_join (
    id UInt64, 
    person Nested (name String,surname String ),
    properties Nested (key String,value String)
) Engine=MergeTree ORDER BY id;
 
INSERT INTO test_multi_array_join VALUES (1, ['Thomas', 'Michel'], ['Aquinas', 'Foucault'], ['profession', 'alive'], ['philosopher', 'no']);
INSERT INTO test_multi_array_join VALUES (2, [], [], ['profession', 'alive'], ['inventor', 'no']);
INSERT INTO test_multi_array_join VALUES (3, ['Thomas', 'Nicola'], ['Edison', 'Tesla'], [], []);

SELECT * FROM test_multi_array_join LEFT ARRAY JOIN person LEFT ARRAY JOIN properties order by id, person.name;

DROP TABLE IF EXISTS test_multi_array_join;
```