Like SQL/T-SQL language, the Kusto language engine will first parse the coming script into an Abstract Syntax Tree(AST), and performs semantic pass over the AST.
Check names, see if the reference table, functions,pre-defined variables exist in the database and query context.
Verify the user has the permissions to access the relevant entity.
Check data type and reference, e.g. is an int function dealing a string?
After the semantic pass, the query engine will build an initial Relational Operators Tree(RelOp Tree) based on the AST. (T-SQL in SQL Server undergoes similar processes.)
Next, the Kusto engine will further attempt to optimize the query by applying one or multiple predefined rewriting rules.
The query engine will replace the table access with an extent union structure.
Push down filters, if the filter predicates involves no extend command, all filters will be push down to the tree leaf. This is why Script A and Script B uses almost the same time. Because after query optimization, both A and B share the same RelOp Tree.
Aggregations ops are split into the “leaf”.
Top n operators are replicated to each data extent.