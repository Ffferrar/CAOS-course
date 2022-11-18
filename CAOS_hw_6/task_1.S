    .intel_syntax noprefix

    .text
    .global avx_sin

avx_sin:
	mov rdi, 1
	vcvtsi2sd xmm2, xmm2, rdi //кладем в 3 даблr8
	vdivsd xmm1, xmm0, xmm2 // делим х на mm2 и кладем в xmm1
	
	mov rsi, 1 //счетчик
	
	vdivsd xmm3, xmm0, xmm2 //член ряда
	
	mov rdi, 0
	vcvtsi2sd xmm2, xmm2, rdi // кладем в 3 ноль 	

loop:

	vmulsd xmm3, xmm3, xmm1 //умножаем на х
	inc rsi
	vcvtsi2sd xmm4, xmm4, rsi 
	vdivsd xmm3, xmm3, xmm4


	vmulsd xmm3, xmm3, xmm1
	inc rsi
	vcvtsi2sd xmm4, xmm4, rsi
	vdivsd xmm3, xmm3, xmm4
	
	jmp Sign
	
    ret
    
Sign:
	mov rdi, -1
	vcvtsi2sd xmm4, xmm4, rdi
	vdivsd xmm3, xmm3, xmm4
	
	jmp Add
	
Add:
	vaddsd xmm0, xmm0, xmm3
	vcomisd xmm2, xmm3  
	jnz loop
	ret
