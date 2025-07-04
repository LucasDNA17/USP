	.data
	.align 2
	.text
	.globl main
	
	
main:
	li a7, 5
	ecall
	
	mv s1, a0
	mv t0, s1
	mv t2, s1
	li s0, 0
	j creating_list
	
	the_end:
		li a7, 10
		ecall
	
	
	
creating_list:
	beq t0, zero, impressao
	li a0, 8
	li a7, 9 #reserva memória
	ecall
	
	mv t1, a0
	
	li a7, 5 #número a ser reservado
	ecall 
	sw a0, (t1)
	sw s0, 4(t1)
	
	mv s0, t1
	addi t0, t0, -1
	j creating_list
	

impressao:
	beq t2, zero, the_end
	lw a0, (s0)
	
	li a7, 1 #printa o número
	ecall
	
	lw a0, 4(s0)
	mv s0, a0
	addi t2, t2, -1
	j impressao
	
	
	
	
	
	
	
	