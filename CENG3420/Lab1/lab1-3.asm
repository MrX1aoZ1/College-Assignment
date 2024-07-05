# CENG3420 Lab 1-2 
# 1155194804 Wu Chun Hei
.global _start

.data	
arr:	.word 0         

.text
_start:

	li a7, 5            	# read the user input (the size of the array, noted as "n") 
	ecall

	addi sp, sp, -4		# Reserve a stack to store the value of n
	sw a0, 0(sp)
	
	lw t2, 0(sp)			# t2 is the value of i (int i = n)	

	la s0, arr			# Load the address of arr to s0
	
	jal ReadArr			# Start reading the user input
		
	# After reading the array			

	lw t1, 0(sp)		# Return the value in stack to n 
	
	la s0, arr 
	addi s10, s0, 0	# Put address of arr[0] to s10, used as "front"
			
	slli t1, t1, 2	 	# t1 = n * 4 - 4
	addi t1, t1, -4
	
	add s11, s0, t1	# Put address of arr[n-1] to s11, used as "end"
	
	addi sp, sp -12	# Reserve a stack
	sw s10, 0(sp)		# Store s10, s11, s0 into the stack
	sw s11, 4(sp)		
	sw s0, 8(sp)
	
	jal Quicksort		# Start quicksort
	
	lw s10, 0(sp)		# Load s10, s11, s0 from the stack
	lw s11, 4(sp)
	lw s0, 8(sp)
	addi sp, sp, 12	# Free the stack
			
	lw t1, 0(sp)		# Load n from the stack
    	jal PrintArr		# Print the sorted array
    	
    	j end
    	
ReadArr:
	addi sp, sp -4		# Reserve a stack to store the return address
	sw ra, 0(sp)		# Store the return address to the stack

	addi s10, s0, 0	# Make a copy of s0 to s10

    	readLoop:
        	beqz t2 endReadArr  	# if (i == 0), end the loop

        	li a7, 5            	# Read arr[i]
        	ecall

       	sw a0, 0(s10)       	# Store the read element to the array

        	addi t2, t2, -1		# i--
        	addi s10, s10, 4		# Point s10 to the next element of array
        
        	j readLoop           	# Continue the loop

	endReadArr:
    		lw ra, 0(sp)			# Load the return address from the stack
		addi sp, sp, 4			# Free the stack
		jr ra				# Return with return address ra

Quicksort:
	# s10 = front ; s11 = end ; a3 = pivot
	addi sp, sp, -4				# Reserve a stack to store the return address
	sw ra, 0(sp)					# Store the return address to the stack
    	
	bge s10, s11, quicksortReturn		# if (end <= front); end quicksort and return

	jal Partition
	
	# Quicksort(arr, front, pivot - 1 )
	
	addi sp, sp, -20		# Reserve a stack
	sw ra, 0(sp)			# Store ra, s10, s11, s0, a3 into the stack
	sw s10, 4(sp)
	sw s11, 8(sp)
	sw s0, 12(sp)
	sw a3, 16(sp)

	addi s11, a3, -4		# i = i - 1
    	
	jal Quicksort			# Do Quicksort recursion

	lw ra, 0(sp)			# Load ra, s10, s11, s0, a3 from the stack
	lw s10, 4(sp)
	lw s11, 8(sp)
	lw s0, 12(sp)
	lw a3, 16(sp)
	addi sp, sp, 20		# Free the stack space
        
	# Quicksort(arr, pivot + 1, end )
	
	addi sp, sp, -20		# Reserve a stack
	sw ra, 0(sp)			# Store ra, s10, s11, s0, a3 into the stack
	sw s10, 4(sp)
	sw s11, 8(sp)
	sw s0, 12(sp)
	sw a3, 16(sp)

	addi s10, a3, 4		# i = i + 1
    	
	jal Quicksort			# Do Quicksort recursion

	lw ra, 0(sp)			# Load ra, s10, s11, s0, a3 from the stack
	lw s10, 4(sp)
	lw s11, 8(sp)
	lw s0, 12(sp)
	lw a3, 16(sp)
	addi sp, sp, 20		# Free the stack space

	quicksortReturn:			# Return to the previous "Quicksort" or "_start"
        	lw ra, 0(sp)			# Loed the return address from the stack
    		addi sp, sp, 4			# Free the stack space
		jr ra				# Return with return address ra



Partition:
	# s9: pivot; s10: pointer of front; s11: pointer of end; 
	
	addi sp, sp, -4
	sw ra, 0(sp)

	lw s9, 0(s11)     		# Obtain the value of pivot and set it to s9
	addi a3, s10, -4  		# int* i = front - 1
	addi a4, s10, 0	 	# int* j = front 
	
	forLoop:
		ble s11, a4, afterforLoop  	# If address of arr[j] >= arr[end], ends the for loop
		lw t3, 0(a4)   			# Store the value in a4 to t3

		ble s9, t3, nextloop		# if(arr[j] >= pivot), skip to nextloop 
		
		addi a3, a3, 4		# i++
		lw t0, 0(a3) 		# Swap arr[i] and arr[j]
		lw t1, 0(a4)       
		sw t1, 0(a3) 
		sw t0, 0(a4) 
        
	nextloop:
		addi a4, a4, 4		# j++ and continue the next loop
		j forLoop
	
	afterforLoop:
		addi a3, a3, 4		# i++
		lw t0, 0(a3) 		# Swap arr[i] and arr[end]
		lw t1, 0(s11)       
		sw t1, 0(a3) 
		sw t0, 0(s11) 
		
        	lw ra, 0(sp)		# Load the return address from the stack to ra
        	addi sp, sp, 4		# Free the stack
        	jr ra			# Return to the Quicksort function

PrintArr:
	la s0, arr 
	addi t4, s0, 0		# Copy address of arr[0] to t4 

	lw t1, 0(sp)		# Load n to t1
			
	slli t1, t1, 2		# t1 = n * 4 - 4
	addi t1, t1, -4
		
	add t5, s0, t1		# Copy address of arr[n-1] to t5
	
	li a7, 11		# Print '\n' for breaking a line
	li a0, '\n'
	ecall
		
	printArrLoop:
		li a7, 1		# Print arr[i]
		lw a0, 0(t4)
		ecall

		ble t5, t4, endPrintArr		# Not printing the " " after printing the last element
	
		li a7, 11		# Print ' ' after printing arr[i]
		li a0, ' '
		ecall
		
		addi t4, t4, 4		# Point t4 to the next element of array
		j printArrLoop		# Print the next element of the array
		
	endPrintArr:	
		li a7, 11		# Print '\n' for breaking a line
		li a0, '\n'
		ecall
		
		jr ra			# Return to the main function
		
				
end:
	addi sp, sp, 4		# Release the space for storing the value of the size of the array 
	li a7, 10 		# Exit the program with code 0
	ecall				
	
# End of the Code
