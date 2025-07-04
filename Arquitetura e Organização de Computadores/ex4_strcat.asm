		.data
		.align 0
str_src:	.space 36
str_dst: 	.space 72
		.text
		.globl main
		
main:
	la s0, str_src
	la s1, str_dst
	
	mv a0,s0
	li a1, 35
	jal leitura
	
	mv a1, s1
	jal my_leitura
	
	jal strcat
	
	jal impressao
	
	li a7, 10
	ecall
	
	
	
	
my_leitura:
	li t0, 35
	li t1, 10 #ENTER KEY
	my_leitura_loop:
		beq t0, zero, end_my_leitura_loop
		
		li a7, 12
		ecall
		
		beq a0, t1, end_my_leitura_loop
		sb a0, (a1)
		addi t0, t0, -1
		addi a1, a1, 1
		j my_leitura_loop
		
	end_my_leitura_loop:
		lb zero, (a1)
		jr ra
		
		
		
	
			
leitura:
	li a7, 8
	ecall
	jr ra
	
	
strcat:
	mv a0, s0
	mv a1, s1
	achar_fim:
		lb t0, (a1)
		beq t0, zero, continuar
		addi a1, a1, 1
		j achar_fim
		
	continuar:
		lb t0, (a0)
		sb t0, (a1)
		beq t0, zero, fim_strcat
		
		addi a0, a0, 1
		addi a1, a1, 1
		j continuar
		
	fim_strcat:
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
		
		
		
	
	

