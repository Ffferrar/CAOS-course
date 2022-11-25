#include <sys/syscall.h>
    .intel_syntax noprefix
    .text
    .global _start
    
count:
    mov rdi, 0
    mov rsi, rsp
    add rsi, 8
    mov rdx, 1
    
    jmp calling

_start:
    sub rsp, 8

    mov rax, SYS_read
    jmp count
    
calling:
    syscall

    cmp rax, 0
    jle loop_end

    jmp moving
    
moving:
    mov rax, SYS_write
    mov rdi, 1
    mov rsi, rsp
    add rsi, 8
    mov rdx, 1
    jmp call_sys_call
    
loop_end:
    add rsp, 8

    mov rax, SYS_exit
    mov rdi, 0
    syscall
    
call_sys_call:

    syscall
    jmp _start
