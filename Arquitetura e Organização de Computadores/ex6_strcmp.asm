	.data
	.align 0
str0:	.space 32
str1:	.space 32
	.text
	.align 2
	.globl main
	
main:
	la s0, str0
	la s1, str1
	
	mv a0, s0
	li a1, 31
	jal leitura
	
	mv a0, s1
	li a1, 31
	jal leitura
	
	mv a0, s0
	mv a2, s1
	jal strcmp
	
	mv a0, a1
	li a7, 1
	ecall
	
	li a7, 10
	ecall
	


strcmp:
	lb t0, (a0)
	lb t2, (a2)
	
	bne t0, t2, strcmp_false
	addi a0, a0, 1
	addi a2, a2, 1
	bne t0, zero, strcmp

	li a1, 1
	jr ra
	
	
strcmp_false:
	li a1, 0
	jr ra 
	
	
	
leitura:
	li a7, 8
	ecall
	jr ra
