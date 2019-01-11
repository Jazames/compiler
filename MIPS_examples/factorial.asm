.data
	number: .word 10
.text
	lw $t2, number
	li $t0, 1 #starting value for factorial is 1, not zero 0_0 
	
	loop:
	mul $t0, $t0, $t2
	sub $t2, $t2, 1
	
	bne $t2, $zero, loop
	
	#now print it out. 
	move $a0, $t0
	li $v0, 1
	syscall