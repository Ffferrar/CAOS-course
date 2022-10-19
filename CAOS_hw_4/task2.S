.text
	.global main         

main:

	mov w0, 1
	mov x20, x30
	bge check_condition
	
loop_start:
	
	bl getchar_unlocked
	
	mov w1, 47
	cmp w1, w0
	bge check_condition
	
	mov w2, 58
	cmp w0, w2
	bge check_condition
	
	bl putchar_unlocked
	b loop_start
	
check_condition:
	cmp w0, #-1 
	beq loop_end
	b loop_start

loop_end:
	mov x30, x20
	mov w0, 0
	ret     
