

/*
Whenever a function is called, the program passes through the following stages. 

	Pre call

	prologue

	function

	epilogue

	post call
*/

//The easiest thing to implement is to spill every register, and then restore every register as well. 
	//REMEMBER to spill the return address as well. 
	//jal - jump and link - mips command to do function calls. 

//The Frame pointer moves with function calls, but it doesn't move during the lifetime of the function. Or it's as if it didn't move. 

//The frame pointer points into the middle of the activation record. 
	//Everything below the frame pointer is the precall 
		//Suggested to be saved registers and parameters
	//Everything above the frame pointer is the prologue.
		//Suggested to be local variables.  
	
	//Function parameters should be positive offsets from the frame pointer. 
		//That offset information should be put in two places
			//The global symbol table for the function call, so that the caller knows where to put things
			//The local symbol table of the function, so that the function knows where to find its parameters. 
		//RECOMMEND to put return value as one of the local variables. 


#spill some registers to put the on stack, so they can be restored. 
addi: $sp, $sp, -12
sw $t0, 0($sp)
sw $fp, 4($sp)
sw $ra, 8($sp)

#put parameters on the stack
addi $sp, $sp, -4
li $t1, 42
sw $t1, 0($sp)
jal foo 

#function has returned, first thing, move frame pointer
addi $sp, $sp, 4 #restore stack pointer from parameters
lw $t0, 0($sp)
lw $fp, 4($sp)
lw $ra, 8($sp)
addi $sp, $sp, 12 #restore stack pointer from spilled/saved registers. 

foo:
	ori $fp, $sp, $zero
	addi: $sp, $sp, -8
		#This area of the stack is for local variables
		#Do function stuff but accessing the stack instead of the heap, at least for local variables
	addi: $sp, $sp 8 #restore stack pointer
	jr $ra


//EXAMPLE Fibbonanci

Function fibb(var n : integer) : integer
var
	sum : integer
begin 
	if (n < 2) return 1;
	sum := fibb(n-1) + fibb(n-2);
	return sum;
end.

begin
	write(fib(5))
end.

See photo taken on March 18th for assembly. 




//Note, once the stack pointer has been adjusted to make room for the function on the stack, make accesses to local variables based on the frame pointer. 





























