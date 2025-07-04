	.data
	.align 0
str_src: .space 32
str_dst: .space 32
	.text
	.globl main
	
main:
	la s0, str_src
	la s1, str_dst
	
	mv a0, s0
	li a1, 31
	
	li a7, 8
	ecall
	
	mv a0, s0
	mv a2, s1
	jal strcpy
	jal impressao
	
	li a7, 10
	ecall
	
strcpy:
	lb t0, (a0)
	sb t0, (a2)
	addi a0, a0, 1
	addi a2, a2, 1 
	bne t0, zero, strcpy
	
	jr ra
	
impressao:
	mv a1, s1
	
	loop_impressao:		
		lb a0, (a1)
		beq a0, zero, end_loop_impressao
		
		addi a1, a1, 1
		li a7, 11
		ecall
		j loop_impressao
	
	end_loop_impressao:
		jr ra