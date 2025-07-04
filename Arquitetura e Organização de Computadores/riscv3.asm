	.data
	
	.text
	.align 2
	
	.global main

main:
	addi a7, zero, 5
	ecall
	
	add s0, zero, a0
	add s1, zero, a0
	
loop:
	addi, s3, zero, 1
	beq s1, s3, the_end
	
	
	addi s1, s1, -1
	mul s0, s0, s1
	j loop
	
the_end:
	addi a7, zero, 1
	add a0, s0, zero
	ecall
	
	
	