

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



activation record needs:
	local variables -> above frame pointer because only the function cares about these. 
	return address -> needs to be below the frame pointer because only the caller knows this.
		also needs to be the same after call as they were before function call
	frame pointer can be either above or below 
		also needs to be the same after call as they were before function call
	somewhere to spill registers -> Can be in either place, but recommended below, because the caller already knows what registers it is using. 
		also needs to be the same after call as they were before function call
	return value  -> below frame pointer because the caller needs this. 
	parameters -> below frame pointer because the caller needs to set these up. 




//Dr. Sundbergs recommended layout: 

locals
				<- fp 
params 
return 
spill 



Function calls by reference: 
LValues should probabably be able to keep track of whether they are references or copies. 
	//James thinks it should be put wherever the LValue emit code lives. Which hopefully is in the LValue. 
	//If a function is passed a non-lvalue where it should be given pass by reference, then an error should be thrown. 









//Swap mips example:

.glbl main 
main: 
	la $gp, GA 
	j realmain
swap:
	addi$sp, $sp, -4
	lw $t0, 0($fp)
	lw $t0, 0($t0)
	sw $t0, -4($fp)
	lw $t0, 4($fp)
	lw $t0, 0($t0) #doing the swap somewhere here
	lw $t1, 0($fp)
	sw $t0, 0($t1)
	lw $t1, 4($fp)
	sw $t0, 0($t1)
	addi $sp, $sp, 4
	jr $ra
realmain:
	#initial setup
	li $to, 42
	sw $t0, 0($gp)
	li $0, 24
	sw $50, 4($gp)


	addi $sp $sp -16
	sw $ra 12($sp)
	sw $fp 8($sp)
	addi $t0, $gp, 0
	sw $t0, 0($p)
	addi $t0, $gp, 4
	sw $t0, 4($gp)
	ori $fp, $sp, 0
	jal swap 
	lw $ra, 12($sp)
	lw $fp, 8($sp)
	addi $sp, $sp, 16

.data
.align 4
GA:


//Swap again


//source code:

type
	point = array [1:2] of integer (size 8)

var
	point a; (0 $gp)
	point b; (8 $gp)

proc swap(ref point a (0 $fp), ref point b(8 $fp))
var
	point t;
begin	
	t:= a;
	a:= b;
	b:= t;
end

begin
	a[1] := 15;
	a[2] := 42;
	b[1] := 33;
	b[2] := 47;

	swap(a,b)
end.

//Symbol Table notes
addresses of variables given in parenthesis after varibale declarations. 




//output assembly
.globl main 
main: j realmain
swap: 
	$addi $sp, $sp, -8 # a @ 0($fp), b @ 4($sp)
	lw $t0, 0($fp) #address of a
	lw $t1, 0($t0) 
	sw $t1, -8($fp)
	lw $t1, 4($t0)
	sw $t1, -4($fp) # t:= a;
	lw $t0, 0($fp) $address of a
	lw $t1, 4($fp) #address of b
	lw $t2, 0($t1)
	sw $t2, 0($t0)
	lw $t2, 4($t1)
	sw $t2, 4($t1)
	sw $t2, 4($t0) # a:= b
	lw $t0, 4($fp) address of b
	lw $t1, -8($fp)
	sw $t1, 0($fp)
	lw $t2, -4($fp)
	sw $t2, r($t0) #b := t
	addi $sp, $sp, 8
	jr $ra

realmain:
	la $gp, GArea
	li $t0, 15
	sw $t0, 0($gp) #a[1] := 15
	li $t0, 42
	sw $t0, 4($gp) #a[1] := 42
	li $t0, 33
	sw $t0, 8($gp) #a[1] := 33
	li $t0, 47
	sw $t0, 12($gp) #a[1] := 47

	#function call
	addi $sp, $sp -16
	sw $ra, 8($sp)
	sw $fp, 12($sp)
		#local variables
	addi $t0, $gp, 0 #address of a
	sw $t0, 0($sp)
	addi $t0, $gp, 8 #address of b
	sw $t0, 4($sp)
		#adjust frame pointer
	move $fp, $sp 
	jal swap
	lw $ra, 8($sp)
	lw $fp, 12($sp)
  addi $sp, $sp, 16
.data
.align 4
GArea:



