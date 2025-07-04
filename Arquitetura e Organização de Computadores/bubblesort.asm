	.data
	.align 2
vector:	.word 4,3,2,1 
	.text
	.globl main
main:
	li t0, 4 
	li t4, 4 #read counter, used later
	la a2, vector
	mv s2, a2 #store till the end the vector's address in s2
	
read_loop:
	beq t0, zero, continue
	li a7, 5
	ecall
	
	sw a0, 0(a2)
	addi a2, a2, 4
	addi t0, t0, -1
	j read_loop


continue:
	li s0, 3  #vector size - 1
	li t0, 0  #external counter
	
external_loop:
	beq t0, s0, print_vector #end of external loop
	
	li t1, 0 #internal counter
	sub t5, s0, t0 #limit of internal loop
	addi t0, t0, 1
	la a1, vector

	j internal_loop


internal_loop:
	beq t1, t5, external_loop
	addi t1, t1, 1 #increments the internal counter
	
	lw t2, (a1)
	lw t3, 4(a1)
	
	blt t3, t2, swap
	addi a1, a1, 4 #updates the vector position pointer
	j internal_loop
		 
swap:
	sw t3, (a1)
	sw t2, 4(a1)
	addi a1, a1, 4 #updates the vector position pointer
	j internal_loop 
	

	
		
print_vector:
	beq t4, zero, the_end
	lw a0, (s2)
	li a7, 1
	ecall
	addi s2, s2, 4
	addi t4, t4, -1
	j print_vector
	
	
the_end:	
	li a7, 10
	ecall
	
	
	
	
	

	
	
	
	
	