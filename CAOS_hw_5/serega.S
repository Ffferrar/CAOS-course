.intel_syntax noprefix
.text
.globl sum

// extern void sum(size_t N, const int *A, const int *B, int *R);
// rdi rsi rdx rcx

sum:
sub rsp, 8

push rbp
mov rbp, rsp // rbp = rsc

mov rax, 0 // i == rax = 0

.loop:
cmp rdi, 0 // N == 0?
je .return // if (N == 0) return
dec rdi // else: —N
mov eax, [rsi + 4 * rax] // load to eax value from stack (A[i])
add eax, [rdx + 4 * rax] // add B[i] to eax
mov [rcx + 4 * rax], eax // copy answer to R[i]
inc rax // ++i
jmp .loop // repeat

.return:
pop rbp
add rsp, 8
ret
