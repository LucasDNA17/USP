#Programa de uma calculadora sequencial.
#Autores:(Nome Completo - Numero USP)
#Lucas Duckur Nunes Andreolli - 15471518
#Pedro Bizon Dania - 11812667
#Yan Trindade Meireles - 13680035
#Luis Guilherme Zanetti - 15652750

			
			.data #Dados do programa
			.align 0  #Alinha a memoria para 2⁰ = 1 bytes, necessario para armazenar as strings.
str_resultado:		.asciz "Resultado: " #String usada para imprimir os resultados das operacoes.
str_err_division:	.asciz "Erro! Divisao por zero!\n" 	#String de mensagem de erro para divisao por zero.
str_err_undo:		.asciz "Erro! Nao ha operacao anterior!\n" 	#String de mensagem de erro para undo invalido.
str_err_operation:	.asciz "Erro! Operacao invalida! Operacoes disponiveis: +,-,*,/,u,f\n"	#String de mensagem de erro para operacao invalida. 
str_err_syntax:		.asciz "\nErro! Sintaxe invalida. Digite a operacao ou operando e pressione a tecla enter.\n"	#String de mensagem de erro para sintaxe invalida.
str_enter:		.asciz "\n"	#String que representa uma quebra de linha
			.align 2 #Alinha a memoria para 2² = 4 bytes, necessario para armazenar palavras. 
p:		.	.word	#Ponteiro para o ultimo bloco de memoria alocado
			.align 2  #Alinha a memoria para 2² = 4 bytes, necessario para armazenar palavras.
			.text #Programa
			.globl main #Inicio do programa
	
#Corpo principal do programa. Realiza a leitura de todas as operacoes a serem feitas.	
main:
	li s9,'f' #caracter de encerramento
	li s8, '+'
	li s7, '-'
	li s6, '*'
	li s5, '/'
	li s4, 'u'
	
	la t1, p
	lw zero, 0(t1) #Inicializa o ponteiro com zero
	
	li a7, 5 
	ecall #Le o primeiro valor 

	mv a2, a0
	jal store_value #Armazena o valor lido na lista encadeada
	
	#Loop de leitura: enquanto o caracter de operacao for diferente de 'f', faca mais uma operacao.
	read_loop:	
		li a7, 12
		ecall #Le um caracter, que e a operacao a ser feita
		mv t1, a0 #Armazene o valor lido em t1
		
		j get_enter #Le a quebra de linha
		
		#Execucao da operacao determinada.
		operacao:
			beq t1, s9, the_end #Se o caracter lido for 'f', encerre o programa
			beq t1, s8, addition #Se o caracter lido for '+', realize a operacao de soma
			beq t1, s7, subtraction  #Se o caracter lido for '-', realize a operacao de subtracao
			beq t1, s6, multiplication  #Se o caracter lido for '*', realize a operacao de multiplicacao
			beq t1, s5, division  #Se o caracter lido for '/', realize a operacao de divisao
			beq t1, s4, undo  #Se o caracter lido for 'u', realize a operacao de "undo"
			j err_operation #O caracter lido nao corresponde a nenhuma operacao
		
		
		j read_loop #Continua a fazer operacoes
	
	#Fim do programa	
	the_end:
		li a7, 10
		ecall #Encerra o programa
		
	
#Funcao store_value: aloca dinamicamente um bloco de memoria de 8 bytes, armazena o valor desejado
#e o endereco do bloco previamente alocado. Se este ultimo nao existir, armazena-se zero no lugar do endereco.
#Parametros: a2 = valor a ser armazenado.
#Retorno: nenhum	
store_value:
	li a0, 8 #Reserva espaco para duas palavras: um valor e um endereco
	li a7, 9 
	ecall #Reserva a memoria 
	
	la t1, p  #Armazena o endereco de p em t1
	lw t2, 0(t1) #Armazena o endereco armazenado em p em t1
	sw a2, (a0) #Armazena o valor desejado no bloco alocado
	sw t2, 4(a0) #Armazena o endereco do ultimo bloco alocado no bloco atual
	
	sw a0, 0(t1) #Atualiza o ponteiro para o bloco alocado
	jr ra #Sai da funcao
	
#Funcao print_value: escreve na saida padrao o inteiro desejado.
#Parametros: a2 = valor a ser escrito
#Retorno: nenhum
print_value:
	la a0, str_resultado
	li a7, 4
	ecall #Imprime a string "Resultado: " na saida padrao
	
	mv a0, a2
	li a7, 1
	ecall	#Escreve na saida padrao o valor
	
	la a0, str_enter
	li a7, 4
	ecall #Imprime na saida padrao uma quebra de linha.

	jr ra #Sai da funcao
	
#Funcao get_value: retorna o valor contido no ultimo bloco de memoria alocado.
#Parametros: nenhum.
#Retorno: a1 = valor contido no ultimo bloco alocado.
get_value:
	la t1, p #Armazena o endereco de p em t1
	lw t2, 0(t1) #Armazena o endereco do ultimo bloco alocado em t2
	lw t3, 0(t2) #Armazena o valor salvo no ultimo bloco alocado em t3
	mv a1, t3 #Move o valor de t3 para a1
	jr ra  #Sai da funcao

#Le um caracter da entrada padrao. Se este caracter for diferente da quebra de linha ('\n'), imprime uma mensagem de erro.
get_enter:
	li a7, 12
	ecall #Le o caracter
	
	#Compara-o com a quebra de linha ('\n')
	li s3, '\n'
	bne a0, s3, err_sintaxe #Se ele nao for a quebra de linha, imprima a mensagem de erro
	
	j operacao #Faca a operacao se a quebra de linha foi lida corretamente
	
#Imprime a mensagem de erro caso o caracter lido apos um caracter de operacao seja diferente da quebra de linha.	
err_sintaxe:
	la a0, str_err_syntax
	li a7, 4
	ecall #Imprime a mensagem de erro "str_err_syntax" na saida padrao
	
	j read_loop #Retorna ao loop de leitura
	
#Le um inteiro, realiza a soma dele com o ultimo valor armazenado na lista encadeada e armazena o resultado nessa lista.		
addition:
	li a7, 5
	ecall #Le um inteiro
	
	mv t0, a0 #Move o inteiro lido para t0
	jal get_value #Armazena o valor do ultimo bloco alocado em a1
	add a2, a1, t0 #Realiza a adicao do valor de t0 e o de a1 e armazena o resultado em a2
	jal store_value #Armazena o valor de a2 na lista encadeada
	jal print_value #Escreve na saida padrao o valor armazenado em a2
	j read_loop #Retorna ao loop de leitura
	
#Le um inteiro, realiza a subtracao dele com o ultimo valor armazenado na lista encadeada e armazena o resultado nessa lista.
subtraction:
	li a7, 5
	ecall  #Le um inteiro
	
	mv t0, a0 #Move o inteiro lido para t0
	jal get_value #Armazena o valor do ultimo bloco alocado em a1
	sub a2, a1, t0 #Realiza a subtracao do valor de a1 e o de t0 e armazena o resultado em a2
	jal store_value #Armazena o valor de a2 na lista encadeada
	jal print_value #Escreve na saida padrao o valor armazenado em a2
	j read_loop #Retorna ao loop de leitura
	
#Le um inteiro, realiza a multiplicacao dele com o ultimo valor armazenado na lista encadeada e armazena o resultado nessa lista.
multiplication:
	li a7, 5
	ecall #Le um inteiro
	
	mv t0, a0 #Move o inteiro lido para t0
	jal get_value #Armazena o valor do ultimo bloco alocado em a1
	mul a2, a1, t0 #Realiza a multiplicacao do valor de a1 e o de t0 e armazena o resultado em a2
	jal store_value #Armazena o valor de a2 na lista encadeada
	jal print_value #Escreve na saida padrao o valor armazenado em a2
	j read_loop #Retorna ao loop de leitura

#Le um inteiro e,caso ele nao seja zero, realiza a divisao dele com o ultimo valor armazenado na lista encadeada e armazena 
#o resultado nessa lista.	
division:
	li a7, 5
	ecall #Le um inteiro
	
	mv t0, a0 #Move o inteiro lido para t0
	beq t0, zero, err_division_by_zero #Se o inteiro lido for zero, trata-se de uma divisao por zero e o erro e tratado
	jal get_value #Armazena o valor do ultimo bloco alocado em a1
	
	div a2, a1, t0 #Realiza a divisao do valor de a1 e o de t0 e armazena o resultado em a2
	jal store_value #Armazena o valor de a2 na lista encadeada
	jal print_value #Escreve na saida padrao o valor armazenado em a2
	j read_loop #Retorna ao loop de leitura
	
#Imprime a mensagem de erro de divisao por zero.	
err_division_by_zero:
	la a0, str_err_division #Armazena o endereco de mensagem de erro "str_err_division"
	li a7, 4
	ecall #Imprime na saida padrao a mensagem de erro

	j read_loop #Retorna ao loop de leitura
	
#Imprime o valor da penultima operacao realizada (caso ela exista) na saida padrao, removendo o ultimo valor da lista encadeada
#e o substituindo pelo penultimo valor.	
undo:
	la t1, p #Armazena o endereco de p em t1
	lw t2, 0(t1) #Armazena o endereco do ultimo bloco alocado em t2
	lw t3, 4(t2) #Armazena o endereco do penultimo bloco alocado em t3
	
	beq t3, zero, err_undo #Se o endereco em t3 for zero ("NULL"), nao ha operacao anterior e o "undo" nao pode ser realizado
	sw zero, 4(t2) #Zera o campo de endereco do bloco atual ("NULL")
	lw a2, 0(t3) #Carrega em a2 o valor armazenado no penultimo bloco alocado 
	
	sw t3, 0(t1) #Atualiza o ponteiro p para o penultimo bloco alocado
	
	jal print_value #Escreve o valor armazenado em a2 na saida padrao
	j read_loop #Retorna ao loop de leitura
	
		
#Imprime a mensagem de erro caso nao haja operacao a ser desfeita.	
err_undo:
	la a0, str_err_undo
	li a7, 4
	ecall #Imprime a mensagem de erro "str_err_undo" na saida padrao
	
	j read_loop #Retorna ao loop de leitura
	
	
#Imprime a mensagem de erro caso o caracter de operacao nao corresponda a nenhuma operacao disponivel.
err_operation:
	la a0, str_err_operation
	li a7, 4
	ecall #Imprime a mensagem de erro "str_err_operation" na saida padrao
	
	j read_loop #Retorna ao loop de leitura
