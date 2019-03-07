


//while statement

WhileStatement --> while ( Expr ) StatementList


mips structure:

whileBegin
|
| Expression
|
beq expr, 0, whileEnd; //This label needs to be unique, so probably keep track of a global integer that gets tagged onto the end of the lable. 
|
| Statement List
|
j whileBegin
whileEnd




//If Statement

IfStatement --> if Expr then StatementList (elseif Expr then StatementList)* (else Expr then StatementList)? end


|
| Expr
|
bne nextElseIf
|
| StatementList
| 
j ifEnd
nextElseIf
|
| Expr
| 
bne nextElseIf2
|
| StatementList
|
j ifEnd
nextElseIf2
ifEnd
