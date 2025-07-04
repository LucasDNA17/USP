		.data
		.align 0
mem_block:	.space 100 
		.text
		.globl main
	
main:
	#reads string
	la a0, mem_block
	li a1, 99
	li a7, 8
	ecall
	
	li a7, 5
	ecall
	mv s0, a0 #num of bytes to be read
	
	la s1, mem_block #address of mem block
	jal memcpy
	
	mv a0, a1 #address of allocated memory
	mv a2, s0 #size to be read
	jal imprimir
	
	li a7, 10
	ecall
	


memcpy:
	ble a0, zero, end_loop_memcpy 
	
	#a0 - pointer to memory allocated
	li a7, 9
	ecall
	
	mv a1, a0 #addrress to be returned
	mv a3, s1 #pointer to source string
	mv t0, s0 
		
	loop_memcpy:
		ble t0, zero, end_loop_memcpy
		lb t1, (a3)
		sb t1, (a0)
		addi a0, a0, 1
		addi a3, a3, 1
		addi t0, t0, -1
		j loop_memcpy
		
	end_loop_memcpy:
		jr ra
		
		
imprimir:
	mv a3, a0
	mv t0, a2 
	loop_imprimir:
		ble t0, zero, end_loop_imprimir
		lb a0, (a3)
		li a7, 11
		ecall
		
		addi a3, a3, 1
		addi t0, t0, -1
		j loop_imprimir
		
	end_loop_imprimir:
		jr ra
		
			
	
	
	