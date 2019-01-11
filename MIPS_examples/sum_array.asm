.data
	array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
	array_length: .word 20
.text
	lw $t1, array_length
	mul $t1, $t1, 4 #multiply the array length by 4 because that's how many bytes there are. 
	li $t2, 0 #Starting index
	li $t0, 0 #starting sum
	
	loop:
	lw $t3, array($t2)
	add $t0, $t0, $t3 #sum array 
	add $t2, $t2, 4 #increment index by 4 since each thing is a word, not a byte. 
	blt $t2, $t1 loop
	
	#if get to here, then everything was summed
	
	
	#now print it out. 
	move $a0, $t0
	li $v0, 1
	syscall