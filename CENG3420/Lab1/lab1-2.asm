# CENG3420 Lab 1-2 
# 1155194804 Wu Chun Hei
.global _start

.data	
arr: .word -1 22 8 35 5 4 11 2 1 78

.text
_start:
    	la s0, arr     # load address of the start of the array to s0

   	# Swap 8 and the last number
    	lw t0, 8(s0) 	# Load word of arr[2]("8") to a0 from memory
    	lw t1, 36(s0) 	# Load word of arr[9]("78") to a1 from memory
    	sw t0, 36(s0)	# Store word of arr[2]("8") from a1 to memory
    	sw t1, 8(s0) 	# Store word of arr[9]("78") from a0 to memory
    
    	addi s10, s0, 0		# Put address of arr[0] to s10, used as "front"
	addi s11, s0, 36		# Put address of arr[9] to s11, used as "end"

	jal Partition	# Do one partition
	
	j PrintArr	# Print the array

Partition:
    	# s9: pivot; s10: pointer of front; s11: pointer of end; 
    	lw s9, 0(s11)     	# Obtain the value of pivot and set it to s9
	addi a3, s10, -4  	# int* i = front - 1
	addi a4, s10, 0	# int* j = front 
	
	forLoop:
		ble s11, a4, afterforLoop  	# If address of *j >= *end, ends the for loop
		
		lw t3, 0(a4)   			# Store the value in a4 to t3
		ble s9, t3, nextloop		# if(*j >= pivot), skip to nextloop 
		
		addi a3, a3, 4		# i++
		lw t0, 0(a3) 		# Swap arr[i] and arr[j]
		lw t1, 0(a4)       
		sw t1, 0(a3) 
		sw t0, 0(a4) 
        
	nextloop:
		addi a4, a4, 4		# j++ and go to the next loop
		j forLoop
	
	afterforLoop:
		addi a3, a3, 4		# i++
		lw t0, 0(a3) 		# Swap arr[i] and arr[end]
		lw t1, 0(s11)       
		sw t1, 0(a3) 
		sw t0, 0(s11) 
		
		jalr zero, 0(ra)	# Return to the main function
	
PrintArr:	
	addi t4, s0, 0   		# Copy address of arr[0] to t4 
	addi t5, s0, 36		# Copy address of arr[9] to t5 

	printArrLoop:			# Start printing the array line by line
        	li a7, 1
		lw a0, 0(t4)
		ecall

		beq t4, t5, printArrEnd # Not printing the '\n' after printing the last element
	
		li a7, 11
		li a0, '\n'
		ecall
		
		addi t4, t4, 4		# Point t4 to the next element of array
		j printArrLoop
	
	printArrEnd:	
		j end			# Finised printing the array and end the program
end:
	li a7, 10 	# Exit the program with code 0
	ecall

# End of the Code
