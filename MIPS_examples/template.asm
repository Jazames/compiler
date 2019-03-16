.globl main
.text
main:
  la $gp, GlobalArea 
  li $t0, 13 #put the number 13 in a register so that it can print something. 
  
  #now print it out. 
  move $a0, $t0
  li $v0, 1
  syscall

.data
  #put constants here
  

GlobalArea: #point the global pointer to here, and use memory below this point for the heap. 





