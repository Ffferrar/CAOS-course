.text
	.global main         

main:
	sub sp, sp, 32       
	str x30, [sp, 12]     

	adr x0, format_str  
	
	add x1, sp, 4
	add x2, sp, 8

	bl scanf      
	
	ldr x3, [sp, 4]
	ldr x4, [sp, 8]      
                         
        add x3, x3, x4
        mov x1, x3
        adr x0, out
	bl printf
	
	ldr x30, [sp, 12]      
	add sp, sp, 32     
	
	mov x0, 0
	ret
	


	.section .rodata     
	
format_str:
	.string "%d %d"        
	
out:
	.string "%d\n"       
