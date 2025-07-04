	.data
	.align 2
vetor:	.word -7,8,107,11,13
	.text
	.globl main
	
main:
	la s0, vetor
	li s1, 5 #tamanho do vetor
	jal soma

	
	mv a0, a1 
	li a7, 1
	ecall
	
	
	li a7, 10
	ecall
	
	
soma:
	mv a0, s0
	li a1, 0 #resultado
	mv t0, s1 #contador
	loop_soma:
		lw a2, (a0)
		add a1, a1, a2
		addi a0, a0, 4
		addi t0, t0, -1
		
		bne t0, zero, loop_soma
		
	jr ra