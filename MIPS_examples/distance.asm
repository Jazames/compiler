.data
	x1: .word 0
	y1: .word 0
	
	x2: .word 434
	y2: .word 454
.text
	lw $t1, x1
	lw $t2, x2
	sub $t0, $t2, $t1
	mul $t0, $t0, $t0
	lw $t1, y1
	lw $t2, y2
	sub $t3, $t2, $t1
	mul $t3, $t3, $t3
	add $t0, $t0, $t3
	
	
	#now print it out. 
	move $a0, $t0
	li $v0, 1
	syscall