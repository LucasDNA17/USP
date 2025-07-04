	.data
	.align 0
str:	.space 32
true:	.asciz "Is balanced!"
false:	.asciz "Not balanced!"
debugg:	.asciz "Debugg"
	.align 0
	.text
	.globl main
	
	
main:
	la a0, str
	li a1, 31
	li a7, 8
	ecall
	
	jal isBalanced
	
	beq a1, zero, print_false
	bne a1, zero, print_true
	
	
	the_end:
	li a7, 10
	ecall	
	
	
isBalanced:
	addi a3, a0, -1 
	mv a2, a0
	get_end_position:
		lb t0, (a2)
		beq t0, zero, end_get_position
		addi a2, a2, 1
		addi a3, a3, 1
		j get_end_position
		
	end_get_position:
		addi a2, a0, -1
		li a1, 1
		loop_is_balanced:
			addi a2, a2, 1
			addi a3, a3, -1
			blt a3, a2, end_loop_is_balanced
			lb t0, (a2)
			lb t1, (a3)
			
			li t2, '('
			li t3, ')'
			beq t0, t3, notBalanced
			beq t0, t2, check_parantheses
			
			li t2, '['
			li t3, ']'
			beq t0, t3, notBalanced
			beq t0, t2, check_brackets
			
			
			li t2, '{'
			li t3, '}'
			beq t0, t3, notBalanced
			beq t0, t2, check_angle_brackets
			
			j loop_is_balanced
			
			
			
		end_loop_is_balanced:
			jr ra
			
			
			
	
check_parantheses:
	la a0, debugg
	li a7, 4
	ecall
	
	li t2, '('
	li t3, ')'
	bne t0, t2, notBalanced 
	bne t1, t3, notBalanced
	j loop_is_balanced
	
check_brackets:
	la a0, debugg
	li a7, 4
	ecall
	
	li t2, '['
	li t3, ']'
	bne t0, t2, notBalanced 
	bne t1, t3, notBalanced
	j loop_is_balanced
	
check_angle_brackets:
	la a0, debugg
	li a7, 4
	ecall


	li t2, '{'
	li t3, '}'
	bne t0, t2, notBalanced 
	bne t1, t3, notBalanced
	j loop_is_balanced
	 
	
notBalanced:
	li a1, 0
	j end_loop_is_balanced
	
	
print_true:
	la a0, true
	li a7, 4
	ecall
	j the_end
	
print_false:
	la a0, false
	li a7, 4
	ecall
	j the_end
	

	
	
	
