.L24:
    lea    r11, [r8+3]
    sub    rax, r10
    add    r9, 1
    lea    rsi, [r8+4]
    mov    rdx, r11
    imul   rdx, r11
    imul   rsi, rsi
    lea    rcx, [rax+r8]
    lea    rbx, [r8+6]
    lea    rax, [rdx+rsi]
    cqo
    idiv   r11
    lea    rsi, [rax+rbx]
    mov    rax, rbx
    cqo
    idiv   r11
    add    rsi, rax
    add    rcx, rsi
    lea    r11, [rcx+2]
    add    r8, rcx
    imul   r11, rcx
    sub    r8, rsi
    lea    rax, [r11+1]
    imul   rax, r11
    cqo
    idiv   r11
    mov    rdx, rax
    shr    rdx, 63
    add    rdx, rax
    sar    rdx
    sub    rax, rdx
    cmp    r9, rdi
    jne    .L24
