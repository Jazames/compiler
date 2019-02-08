//Symbol Table Notes:

/*
We already know that we need to keep track of a few things:
  Register Poolat
  Value
  Identifiers
    Type, value, name, scope, address
    Can be implemented as a map<id, stuff>

This map of ids and information is the symbol table. 

May actually want to do a vector<map<id, stuff> > so that maps with the appropriate scope of variables can be pushed onto the vector. 

With the register pool, may want to create a handy little class to manage the registers that automatically deletes them after they pass out of scope.

Want a class that manages information about types. 
  It has three subclasses, 
    one that handles primitives, 
    one that handles arrays, 
    and one that handles structures. 
  It should also have a virtual function that returns the size.
    STRONGLY RECCOMMENDED TO MAKE EVERY PRIMITIVE 4 BYTES. THIS MAKES ALIGNMENT EASY.

To store in the symbol table:
  i -> int, $gp,0 
  identifier -> type, $base_pointer,offset
  j -> int, $global_pointer,4


Also recommend to put comments in the generated MIPS assembly. It makes life easier. 
Aggressively optimize for ease of implementation. 


Need a function to getTheeIntoARegister. 
  Are you already in a register? return that register
  Else, get a register and load. 

When evaluating Binary operators, 
  if both are constant, perform the operation, then put it into a register. 
  If not both constant, put each into a register and perform the operation.  


*/




