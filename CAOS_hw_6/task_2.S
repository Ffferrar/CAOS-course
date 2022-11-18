.intel_syntax noprefix
.globl dot_product
.text


dot_product:
    push     rbp
    mov      rbp,  rsp
    mov      r8,   rdi
    mov      rax,  0
    mov      r9,   0
    cvtsi2ss xmm0, r9
    cvtsi2ss xmm3, r9
loop:
    add      rax,  8
    cmp      rax,  r8
    jg       loop2
    sub      rax,  8
    vmovups  ymm1, YMMWORD PTR[rsi + r9]
    vmovups  ymm2, YMMWORD PTR[rdx + r9]
    vmulps   ymm1, ymm1, ymm2
    vaddps   ymm0, ymm0, ymm1
    add      rax,  8
    add      r9,   32
    jmp      loop

loop2:
    sub      rax,  8
    sub      rsp,  32
    vmovups  YMMWORD PTR[rsp], ymm0
    mov      r10,  8
    mov      r11,  0
    mov      rcx,  0
cnt:
    cmp      r10,  r11
    jz       endcnt
    vmovss   xmm4, [rsp + rcx]
    vaddss   xmm3, xmm3, xmm4
    add      r11,  1
    add      rcx,  4
    jmp      cnt

endcnt:
    add      rsp,  32
loop2start:
    cmp      rax,  r8
    jz       end
    vmovss   xmm4, [rsi + r9]
    vmovss   xmm5, [rdx + r9]
    vmulss   xmm4, xmm4, xmm5
    vaddss   xmm3, xmm3, xmm4
    add      rax,  1
    add      r9,   4
    jmp      loop2start

end:
    vmovss   xmm0, xmm3, xmm3
    pop      rbp
    ret



