#Programa que calcula iterativamente o fatorial de um número digitado pelo usuário
#utilizando funções para fazer a leitura do número, calcular o fatorial
# e imprimi-lo na saída.

#Autor: Lucas Dúckur Nunes Andreolli
#N° USP: 15471518



				
		.data
		.align 0
str_numero: 	.asciz "Digite o número de entrada: "
str_resposta: 	.asciz "O fatorial de "
str_eh:     	.asciz " é: "
		.text
		.align 2
		.globl main
	
main:
	#Pede um inteiro de entrada ao usuário, faz a leitura e
	#armazena o número em s0 e a0
	jal leitura
		
	#Calcula o fatorial do parâmetro armazenado em a0
	jal fatorial
	
	#Printa o resultado junto das strings definidas como dados do programa
	jal printa_resultado
	
	#Encerra o programa
	li a7, 10
	ecall
	

#Parâmetro da função: --
#Retorno da função: valor digitado pelo usuário, armazenado em s0 (para uso posterior) e
#em a0 (parâmetro da função fatorial)
leitura:
	#Pede ao usuário que digite um número
	li a7, 4
	la a0, str_numero
	ecall
	
	#Lê o número e o armazena em s0
	li a7, 5
	ecall
	mv s0, a0
	
	jr ra

#Parâmetro da função: inteiro no registrador a0
#Retorno da função: fatorial do inteiro de parâmetro (em a0) armazenado no registrador a1								
fatorial:
	li a1, 1 #Inicializa a1, onde o resultado do fatorial será armazenado
	mv t0, a0 #Carrega o número de parâmetro em t0
	
	fatorial_loop:
		beq t0, zero, end_fatorial_loop #Enquanto o contador for diferente de 0, repita o loop
		mul a1, a1, t0  #Multiplica o resultado pelo valor atual de t0
		addi t0, t0, -1 #Decrementa o valor de t0
		j fatorial_loop 
		
	end_fatorial_loop:
		jr ra
	
	

#Parâmetro da função: --
#Retorno da função: --	
printa_resultado:
	#Printa a string "str_numero"
	li a7, 4
	la a0, str_resposta
	ecall
	
	#Printa o número
	li a7, 1
	mv a0, s0
	ecall
	
	#Printa a string "str_eh"
	li a7, 4
	la a0, str_eh 
	ecall
	
	#Printa o resultado
	li a7, 1
	mv a0, a1
	ecall
	
	jr ra
	
	
	
	
	

	
	
	  
	
	
	
	
	
	