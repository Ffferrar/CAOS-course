 .intel_syntax noprefix

    .text                                  
    .global sum

sum:
    mov rax, 0
    movsx rdi, edi

    lea r8, [0+rdi*4]

.loop_begin:
    
    mov edi, DWORD PTR [rdx+rax] //summ a
    add edi, DWORD PTR[rsi+rax] //summ b
    
    mov DWORD PTR [rcx+rax], edi //put in R summary
    
    add rax, 4 //loop 
    cmp r8, rax //loop
    jne    .loop_begin     

    ret

