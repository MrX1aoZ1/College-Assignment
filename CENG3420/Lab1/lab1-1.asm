# CENG3420 Lab 1-1 
# 1155194804 Wu Chun Hei
.global _start

.data	
var1: .word 0
var2: .word 0
var3: .word 0

.text
_start:
# ReadInput1
	li a7, 5
	ecall
	
# Calculate var1
	addi t0, a0, 3 # t0 = a0 + 3
	la t1, var1  # storing t0 to var1
	sw t0, 0(t1)
	
# ReadInput2
	li a7, 5 
	ecall
	
# Calculate var2
	slli t0, a0, 1 # shifting to the left by 1 bit (t0 = a0 * 2)
	la t1, var2 # storing t0 to var2
	sw t0, 0(t1)
	
# ReadInput3
	li a7, 5
	ecall
	
# Calculate var3
	la t2, var1 # load var1 to t1
	lw t1, 0(t2)
	add t0, t1, a0 # t0 = a0 + t1
	la t2, var2 # load var2 to t1
	lw t1, 0(t2)
	add t0, t1, t0 # t0 = t0 + t1
	la t2, var3 # storing t0 to var3
	sw t0, 0(t2)
	
# Printing the result
	li a7, 1 # PrintInt
	la t1, var1 # load var1 to t0
	lw a0, 0(t1)
	ecall
	
	li a7, 11 # PrintChar
	li a0, '\n' 
	ecall
	
	li a7, 1 # PrintInt
	la t1, var2 # load var1 to t0
	lw a0, 0(t1)
	ecall
	
	li a7, 11 # PrintChar
	li a0, '\n'
	ecall
	
	li a7, 1 # PrintInt
	la t1, var3 # load var1 to t0
	lw a0, 0(t1)
	ecall
	
	li a7, 11 # PrintChar
	li a0, '\n'
	ecall
	
# Exit the program
	li a7, 10 # Exit the program with code 0
	ecall
	
# End of the code
