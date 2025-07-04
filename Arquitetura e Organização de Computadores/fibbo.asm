	.data
	.align 0
str_number: .asciz "Write the number whose factorial will be calculated: "
str_answer: .asciz "The factorial of "
str_is:     .asciz " is: "
	.text
	.align 2
	.globl main
	
main:
	#Ask the user a number
	li a7, 4
	la a0, str_number
	ecall
	
	#Get the number
	li a7, 5
	ecall
	
	#Store the number in s0 and get a register to be the counter and another to be the result
	mv s0, a0
	li t0, 1 #result
	mv t1, s0 #counter
	
loop:
	beq t1, zero, end_loop #stop condition
	
	mul t0, t0, t1
	addi t1, t1, -1
	j loop
	
end_loop:

	#Print "The factorial of "
	li a7, 4
	la a0, str_answer
	ecall
	
	#Print the number chosen
	li a7, 1
	mv a0, s0
	ecall
	
	#Print "is"
	li a7, 4
	la a0, str_is
	ecall	

	#Print the result
	li a7, 1
	mv a0, t0
	ecall
	
	#End the program 
	li a7, 10
	ecall
	
	
	