	.data
	.align 0
str:	.space 24 #tamanho maximo da string = 23
	.text
	.globl main
	
main:
	la s0, str #endereço da string
	li s1, 23  #max tamanho
	jal leitura
	
	jal inverte
	
	jal impressao 
	
	li a7,10
	ecall
	
		
leitura:
	mv a0, s0
	mv a1, s1

	li a7, 8
	ecall
	
	jr ra
		
		
		
inverte:
	mv a0, s0
	li a1, 0
	
	mv a2, s0
	acha_fim:
		lb a3, (a2)
		beq a3, zero, loop_inverte
		mv a1, a2
		addi a2, a2, 1
		j acha_fim
		
	loop_inverte:
		ble a1, a0, end_loop_inverte		
		lb t0, (a0)
		lb t1, (a1)
		sb t0, (a1)
		sb t1, (a0)
		addi a1, a1, -1
		addi a0, a0, 1 
		j loop_inverte
		
	end_loop_inverte:
		jr ra
		
		   	
impressao:
	mv a1, s0
	
	loop_impressao:		
		lb a0, (a1)
		beq a0, zero, end_loop_impressao
		
		addi a1, a1, 1
		li a7, 11
		ecall
		j loop_impressao
	
	end_loop_impressao:
		jr ra
		
		
	
		
		
	
	
	
