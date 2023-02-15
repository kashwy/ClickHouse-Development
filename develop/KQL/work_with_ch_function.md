# Working with ClickHouse Functions

## Why:
Difficulties when implementing KQL function with SQL.
- difficult to handle data or expression from DB, e.g. columns
- solve the problem of if statement. e.g array_sort_asc(arg1,arg2,...argn), argn can be a condition.
- logic of loop 
- process different type of input arguments.
- ...
## Add new ClickHosue function:

- create a class from IFunction:
    ```
    class FunctionKqlArraySort : public IFunction
    {
    public:
        static constexpr auto name = "kql_array_sort_asc";
        ...
        static FunctionPtr create(ContextPtr context) 
        {
            return std::make_shared<FunctionKqlArraySort>(context); 
        }
        DataTypePtr getReturnTypeImpl(const ColumnsWithTypeAndName & arguments) const override
        {...}
        ColumnPtr executeImpl(const ColumnsWithTypeAndName & arguments, const DataTypePtr & result_type, size_t input_rows_count) const override
        {...}
    }
    ```
    the name is the function name in ClickHouse, e.g `kql_array_sort_asc`
- register function  
    ```
    REGISTER_FUNCTION(KqlArraySort)
    {
        factory.registerFunction<FunctionKqlArraySort>();
    }
    ```
    Add the new function to the function factory, called by `registerFunctions()` when server start.
- implement  `getReturnTypeImpl` and `executeImpl`: (explain in example)  
 `getReturnTypeImpl` is being called before execution, it validate the input arguments and set the data type of the ouput.  
 e.g: the n-1 args must be array for array_sort_asc(arg1..argn)

    `executeImpl` is the routine to implement the logic of the function.

## Tips

the functions in clichouse are dealing with Columns, DataTypes, there are some chalenges to working with them
- call exsting functions:  
    create instance from FunctionFactory, e.g.  
    ```auto fun_zip = FunctionFactory::instance().get("arrayZip", context);```  
    then build and excute with argumets:  
    ```auto zipped = fun_zip->build(args)->execute(args, result_type, input_rows_count);```
- arguments: 
    the colument arguments passed to functions is a vector of `ColumnWithTypeAndName`  
    so construct `ColumnWithTypeAndName(column, datatype, name)` and put in the vector

- type casting : 
use `checkAndGetDataType` to cast type, e.g :
    ```
    const DataTypeArray * array_type = checkAndGetDataType<DataTypeArray>(arguments[index].type.get());
    ```
- constant column   
    create from datatype, .e.g:   
    `DataTypeUInt8().createColumnConst(1, toField(UInt8(1)))`  
- const column and full column  
    some type columns cannot have const column inside, convert to full column, e.g.  
    ```
    tuple_columns[i] = tuple_columns[i]->convertToFullColumnIfConst();
    ```

- null value :
    it need to be nullable: 
    ```
    auto null_type = std::make_shared<DataTypeNullable>(std::make_shared<DataTypeInt8>());
    null_type->createColumnConstWithDefaultValue(input_rows_count)
    ```
- check condition:  
    use if function of ClickHouse  
    ```
    static bool check_condition (const ColumnWithTypeAndName & condition, ContextPtr context, size_t input_rows_count)
    {
        ColumnsWithTypeAndName if_columns(
        {
            condition,
            {DataTypeUInt8().createColumnConst(1, toField(UInt8(1))), std::make_shared<DataTypeUInt8>(), ""},
            {DataTypeUInt8().createColumnConst(1, toField(UInt8(2))), std::make_shared<DataTypeUInt8>(), ""}
        });
        auto if_res = FunctionFactory::instance().get("if", context)->build(if_columns)->execute(if_columns, std::make_shared<DataTypeUInt8>(), input_rows_count);
        auto result = if_res->getUInt(0);
        return (result == 1);
    }
    ```
## Example  and implementation for KQL:

`src/Functions/Kusto/KqlArraySort.cpp`

KQL function:  array_sort_asc()  

`array_sort_asc(array1[, ..., argumentN],nulls_last)`

the last argument `nulls_last` is optional.  
Returns: 
- 1 same number of arrays as in the input, first array sorted in ascending order
- 2 the remaining arrays ordered to match the reordered first array.
- 3 null will be returned for every array that differs in length from the first one

duo to the array in ClickHouse is not nullable, so the case 3 will return `[null]` instead of `null`  
for example:  
`array_sort_asc(dynamic([2,1,3]),dynamic([10,11,12]),dynamic([100,200])) -> [1,2,3],[11,10,12],[null]`  



### **getReturnTypeImpl**  

- validate input arguments:  
    must have at least one argument  
    n-1 arguments must be array   
- set output DataType  
    we want to have a tuple of array with nullable value:  

```
    DataTypePtr getReturnTypeImpl(const ColumnsWithTypeAndName & arguments) const override
    {
        if (arguments.empty())
            throw Exception("Function " + getName() + " needs at least one argument; passed " + toString(arguments.size()) + "."
                , ErrorCodes::NUMBER_OF_ARGUMENTS_DOESNT_MATCH);

        auto array_count = arguments.size();

        if (!isArray(arguments.at(array_count - 1).type))
            --array_count;

        DataTypes nested_types;
        for (size_t index = 0; index < array_count ; ++index)
        {
            const DataTypeArray * array_type = checkAndGetDataType<DataTypeArray>(arguments[index].type.get());
            if (!array_type)
                throw Exception("Argument " + toString(index + 1) + " of function " + getName()
                    + " must be array. Found " + arguments[0].type->getName() + " instead.", ErrorCodes::ILLEGAL_TYPE_OF_ARGUMENT);
            nested_types.emplace_back(array_type->getNestedType());
        }

        DataTypes data_types(array_count);

        for (size_t i = 0; i < array_count; ++i)
            data_types[i] = std::make_shared<DataTypeArray>(makeNullable(nested_types[i]));

        return std::make_shared<DataTypeTuple>(data_types);
    }
```

### **executeImpl**

implementation also call CH function natively. the process:
- zip array to tuple:  
    `[2, 1, 3], [10, 12, 13] -> ([2, 10],[1, 12],[3, 13])`
- sort the tuple:  
    `([2, 10], [1, 12], [3, 13]) -> ([1, 12], [2, 10], [3, 13])`
- untuple:  
    `([1, 12] ,[2, 10], [3, 13]) -> [1, 2, 3], [12, 10, 13]`

the founctions used:  
```
FunctionFactory::instance().get("arrayZip", context)   
FunctionFactory::instance().get("arraySort", context)   
FunctionFactory::instance().get("tupleElement", context)   
```  
for handling the nulls in array , the follwoing functions also used:  
```
FunctionFactory::instance().get("indexOf", context)  
FunctionFactory::instance().get("arraySlice", context)  
FunctionFactory::instance().get("arrayConcat", context)  
``` 
## Demo

```
CREATE TABLE visit(pageid UInt8, ip_country Array(Nullable(String)), hit Array(Int64),duration Array(Int64)) ENGINE = Memory;
INSERT INTO visit VALUES (1,['CA', 'US','FR','Eng'], [21,12,13,20],[100,500,306,109]);
INSERT INTO visit VALUES (2,['Japan', 'Gem','FR','Eng'], [31,22,33,10],[210,450,310,286]);
INSERT INTO visit VALUES (3,['CA', 'Gem','Japan','Eng'], [11,10,23,11],[210,450,310]);
INSERT INTO visit VALUES (4,['CA', 'Gem',null,'Eng'], [11,10,23,11],[210,450,310,550]);
INSERT INTO visit VALUES (5,['FR', null,'US','Eng'], [11,10,23,11],[210,450,310,550]);

┌─pageid─┬─ip_country─────────────┬─hit───────────┬─duration──────────┐
│      1 │ ['CA','US','FR','Eng'] │ [21,12,13,20] │ [100,500,306,109] │
└────────┴────────────────────────┴───────────────┴───────────────────┘
┌─pageid─┬─ip_country─────────────────┬─hit───────────┬─duration──────────┐
│      2 │ ['Japan','Gem','FR','Eng'] │ [31,22,33,10] │ [210,450,310,286] │
└────────┴────────────────────────────┴───────────────┴───────────────────┘
┌─pageid─┬─ip_country─────────────────┬─hit───────────┬─duration──────┐
│      3 │ ['CA','Gem','Japan','Eng'] │ [11,10,23,11] │ [210,450,310] │
└────────┴────────────────────────────┴───────────────┴───────────────┘
┌─pageid─┬─ip_country──────────────┬─hit───────────┬─duration──────────┐
│      4 │ ['CA','Gem',NULL,'Eng'] │ [11,10,23,11] │ [210,450,310,550] │
└────────┴─────────────────────────┴───────────────┴───────────────────┘
┌─pageid─┬─ip_country─────────────┬─hit───────────┬─duration──────────┐
│      5 │ ['FR',NULL,'US','Eng'] │ [11,10,23,11] │ [210,450,310,550] │
└────────┴────────────────────────┴───────────────┴───────────────────┘
```

**SELECT kql_array_sort_asc(ip_country, hit, duration)
FROM visit**

 **visit | project array_sort_asc(ip_country, hit, duration)**
```

Query id: 7c06d015-9f3a-42c0-952e-309facb86f25

┌─kql_array_sort_asc(ip_country, hit, duration)─────────────┐
│ (['CA','Eng','Gem',NULL],[11,11,10,23],[210,550,450,310]) │
└───────────────────────────────────────────────────────────┘
┌─kql_array_sort_asc(ip_country, hit, duration)────────────────┐
│ (['Eng','FR','Gem','Japan'],[10,33,22,31],[286,310,450,210]) │
└──────────────────────────────────────────────────────────────┘
┌─kql_array_sort_asc(ip_country, hit, duration)────────────┐
│ (['CA','Eng','FR','US'],[21,20,13,12],[100,109,306,500]) │
└──────────────────────────────────────────────────────────┘
┌─kql_array_sort_asc(ip_country, hit, duration)─────┐
│ (['CA','Eng','Gem','Japan'],[11,11,10,23],[NULL]) │
└───────────────────────────────────────────────────┘
┌─kql_array_sort_asc(ip_country, hit, duration)────────────┐
│ (['Eng','FR','US',NULL],[11,11,23,10],[550,210,310,450]) │
└──────────────────────────────────────────────────────────┘
```

with the last argument of condition:  **visit | project pageid, array_sort_asc(ip_country, hit, duration, pageid > 4)**  

```
┌─pageid─┬─kql_array_sort_asc(ip_country, hit, duration, greater(pageid, 4))─┐
│      1 │ (['CA','Eng','FR','US'],[21,20,13,12],[100,109,306,500])          │
└────────┴───────────────────────────────────────────────────────────────────┘
┌─pageid─┬─kql_array_sort_asc(ip_country, hit, duration, greater(pageid, 4))─┐
│      2 │ (['Eng','FR','Gem','Japan'],[10,33,22,31],[286,310,450,210])      │
└────────┴───────────────────────────────────────────────────────────────────┘
┌─pageid─┬─kql_array_sort_asc(ip_country, hit, duration, greater(pageid, 4))─┐
│      3 │ (['CA','Eng','Gem','Japan'],[11,11,10,23],[NULL])                 │
└────────┴───────────────────────────────────────────────────────────────────┘
┌─pageid─┬─kql_array_sort_asc(ip_country, hit, duration, greater(pageid, 4))─┐
│      4 │ ([NULL,'CA','Eng','Gem'],[23,11,11,10],[310,210,550,450])         │
└────────┴───────────────────────────────────────────────────────────────────┘
┌─pageid─┬─kql_array_sort_asc(ip_country, hit, duration, greater(pageid, 4))─┐
│      5 │ (['Eng','FR','US',NULL],[11,11,23,10],[550,210,310,450])          │
└────────┴───────────────────────────────────────────────────────────────────┘
```


filter with sort result of null **visit | where isnull((array_sort_asc(ip_country, hit, duration).3)[0])**

```
SELECT *
FROM visit
WHERE ((kql_array_sort_asc(ip_country, hit, duration).3)[if(0 >= 0, 0 + 1, 0)]) IS NULL

Query id: 74c248ea-482d-4086-84dd-e6d89eb42e62

┌─pageid─┬─ip_country─────────────────┬─hit───────────┬─duration──────┐
│      3 │ ['CA','Gem','Japan','Eng'] │ [11,10,23,11] │ [210,450,310] │
└────────┴────────────────────────────┴───────────────┴───────────────┘
```


## How functions being called

    Parser 
     Interpreter
        ExpressionAnalyzer  -> get actions.
            InDepthNodeVisitor 
                visit each node of AST.
                    is a function node ? (if (const auto * node = ast->as<ASTFunction>()))
                ActionsDAG::addFunction
                        (function name :IFunctionOverloadResolver)
                    build function
                        getReturnType
                            ...
                        execute for constant

there are several calsses related with funtios. the diagram may helpful for understanding the relationships.

[function related classes](https://github.ibm.com/ClickHouse/issue-repo/blob/master/images/functions.png)
    
