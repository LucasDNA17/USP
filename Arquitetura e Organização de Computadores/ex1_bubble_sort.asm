	.data
	.align 0
espaco:	.asciz " "
	.align 2
vetor:	.space 28
	.text
	.align 2
	.globl main
	
main:
	la s0, vetor #salva o endereço do vetor
	li s1, 6 #MAX - 1
	
	li t0, 7 #contador 
	mv t1, s0  #ponteiro para as posições do vetor
	j leitura
	
	fim_leitura:
		jal ordenacao
		
	j imprimir
	
	the_end:
	li a7, 10
	ecall
	
	 
	 
leitura: 
	loop_leitura:
		li a7, 5
		ecall
		sw a0, (t1)
		addi t1, t1, 4 #atualiza o ponteiro
		addi t0, t0, -1 #atualiza o contador
		bne t0, zero, loop_leitura
		
	j fim_leitura
		
		
ordenacao:
	li t0, 0  #contador externo
	
	
	loop_externo:
		mv a0, s0 #ponteiro para a posição do vetor
		li t1, 0  #contador interno
		sub t2, s1, t0 #limite da iteração: (MAX - 1) - i 
		loop_interno:
			lw a2, 0(a0)
			lw a3, 4(a0)
			blt a3, a2, swap
			
			#Atuali
			za os contadores e ponteiros, mesmo que uma troca ocorra
			continue_loop:
				addi a0, a0, 4 #atualiza o ponteiro
				addi t1, t1, 1 #atualiza o contador interno
				bne t1, t2, loop_interno
				
		
		addi t0, t0, 1
		bne t0, s1, loop_externo 
	
	jr ra		
	
	
	
	swap:
		sw a3, 0(a0)
		sw a2, 4(a0)
		j continue_loop
			



		
imprimir:
	li t0, 7
	mv t1, s0
	
	loop_impressao:
		lw a0, (t1)
		li a7, 1
		ecall
		
		la a0, espaco
		li a7, 4
		ecall
		
		addi t0, t0, -1
		addi t1, t1, 4
		bne t0, zero, loop_impressao
		
	j the_end
		
		
		
	
	
