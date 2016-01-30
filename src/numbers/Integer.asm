.L22:

; m -= o_f_f;

    mov    esi, OFFSET FLAT:o_f_f
    mov    rdi, rsp
    call   DS::Numbers::Integer::operator-=

; intType m3(init+intType(3)), m4(init+intType(4)), m6(init+intType(6));

    lea    rdi, [rsp+96]
    mov    esi, 3
    call   DS::Numbers::Integer::Integer(int)
    lea    rdi, [rsp+48]
    mov    esi, OFFSET FLAT:init
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+96]
    lea    rdi, [rsp+48]
    call   DS::Numbers::Integer::operator+=
    lea    rdi, [rsp+96]
    call   DS::Numbers::Integer::~Integer

    mov    esi, 4
    lea    rdi, [rsp+144]
    call   DS::Numbers::Integer::Integer(int)
    lea    rdi, [rsp+96]
    mov    esi, OFFSET FLAT:init
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+144]
    lea    rdi, [rsp+96]
    call   DS::Numbers::Integer::operator+=
    lea    rdi, [rsp+144]
    call   DS::Numbers::Integer::~Integer

    mov    esi, 6
    lea    rdi, [rsp+192]
    call   DS::Numbers::Integer::Integer(int)
    lea    rbx, [rsp+1392]
    mov    esi, OFFSET FLAT:init
    mov    rdi, rbx
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+192]
    mov    rdi, rbx
    call   DS::Numbers::Integer::operator+=
    lea    rdi, [rsp+192]
    call   DS::Numbers::Integer::~Integer

; m += init;

    mov    esi, OFFSET FLAT:init
    mov    rdi, rsp
    call   DS::Numbers::Integer::operator+=

; m = (m3*m3 + m4*m4) / m3 + m6 + m6/m3 + m;

    lea    rdi, [rsp+480]
    mov    rsi, rbx
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+480]
    call   DS::Numbers::Integer::operator/=
    lea    rsi, [rsp+96]
    lea    rdi, [rsp+288]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+96]
    lea    rdi, [rsp+288]
    call   DS::Numbers::Integer::operator*=
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+240]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+240]
    call   DS::Numbers::Integer::operator*=
    lea    rsi, [rsp+240]
    lea    rdi, [rsp+336]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+288]
    lea    rdi, [rsp+336]
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+336]
    lea    rdi, [rsp+384]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+384]
    call   DS::Numbers::Integer::operator/=
    lea    rsi, [rsp+384]
    lea    rdi, [rsp+432]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+432]
    mov    rsi, rbx
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+432]
    lea    rdi, [rsp+528]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+480]
    lea    rdi, [rsp+528]
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+528]
    lea    rdi, [rsp+576]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+576]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator+=
    ; Integer move/copy(?) assignment operator
    lea    rsi, [rsp+576]
    mov    rdi, rsp
    call   _ZN2DS7Numbers9BaseArrayaSERKS1_
    movzx   eax, BYTE PTR [rsp+608]
    lea    rdi, [rsp+576]
    mov    BYTE PTR [rsp+32], al
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+528]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+432]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+384]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+336]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+240]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+288]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+480]
    call   DS::Numbers::Integer::~Integer

; init += m;

    mov    rsi, rsp
    mov    edi, OFFSET FLAT:init
    call   DS::Numbers::Integer::operator+=

; m = m*m + m + m;

    lea    rdi, [rsp+624]
    mov    rsi, rsp
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+624]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator*=
    lea    rsi, [rsp+624]
    lea    rdi, [rsp+672]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+672]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+672]
    lea    rdi, [rsp+720]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+720]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator+=
    ; Integer move/copy(?) assignment operator
    lea    rsi, [rsp+720]
    mov    rdi, rsp
    call   _ZN2DS7Numbers9BaseArrayaSERKS1_
    movzx   eax, BYTE PTR [rsp+752]
    lea    rdi, [rsp+720]
    mov    BYTE PTR [rsp+32], al
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+672]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+624]
    call   DS::Numbers::Integer::~Integer

; m = (m*m + m) / m;

    lea    rdi, [rsp+768]
    mov    rsi, rsp
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+768]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator*=
    lea    rsi, [rsp+768]
    lea    rdi, [rsp+816]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+816]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+816]
    lea    rdi, [rsp+864]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+864]
    mov    rsi, rsp
    call   DS::Numbers::Integer::operator/=
    ; default move assignment operator
    lea    rsi, [rsp+864]
    mov    rdi, rsp
    call   _ZN2DS7Numbers9BaseArrayaSERKS1_
    movzx  eax, BYTE PTR [rsp+896]
    lea    rdi, [rsp+864]
    mov    BYTE PTR [rsp+32], al
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+816]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+768]
    call   DS::Numbers::Integer::~Integer

; m = m-m/2;

    mov    esi, 2
    lea    rdi, [rsp+912]
    call   DS::Numbers::Integer::Integer(int)
    lea    rdi, [rsp+960]
    mov    rsi, rsp
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+912]
    lea    rdi, [rsp+960]
    call   DS::Numbers::Integer::operator/=
    lea    rdi, [rsp+1008]
    mov    rsi, rsp
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+960]
    lea    rdi, [rsp+1008]
    call   DS::Numbers::Integer::operator-=
    ; default move assignment operator
    lea    rsi, [rsp+1008]
    mov    rdi, rsp
    call   _ZN2DS7Numbers9BaseArrayaSERKS1_
    movzx  eax, BYTE PTR [rsp+1040]
    lea    rdi, [rsp+1008]
    mov    BYTE PTR [rsp+32], al
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+960]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+912]
    call   DS::Numbers::Integer::~Integer

; init -= (m3*m3 + m4*m4) / m3 + m6 + m6/m3;

    lea    rdi, [rsp+1296]
    mov    rsi, rbx
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+1296]
    call   DS::Numbers::Integer::operator/=
    lea    rsi, [rsp+96]
    lea    rdi, [rsp+1104]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+96]
    lea    rdi, [rsp+1104]
    call   DS::Numbers::Integer::operator*=
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+1056]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+1056]
    call   DS::Numbers::Integer::operator*=
    lea    rsi, [rsp+1056]
    lea    rdi, [rsp+1152]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+1104]
    lea    rdi, [rsp+1152]
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+1152]
    lea    rdi, [rsp+1200]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+48]
    lea    rdi, [rsp+1200]
    call   DS::Numbers::Integer::operator/=
    lea    rsi, [rsp+1200]
    lea    rdi, [rsp+1248]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rdi, [rsp+1248]
    mov    rsi, rbx
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+1248]
    lea    rdi, [rsp+1344]
    call   DS::Numbers::Integer::Integer(Integer&)
    lea    rsi, [rsp+1296]
    lea    rdi, [rsp+1344]
    call   DS::Numbers::Integer::operator+=
    lea    rsi, [rsp+1344]
    mov    edi, OFFSET FLAT:init
    call   DS::Numbers::Integer::operator-=
    lea    rdi, [rsp+1344]
    add    rbp, 1
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+1248]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+1200]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+1152]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+1056]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+1104]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+1296]
    call   DS::Numbers::Integer::~Integer
    mov    rdi, rbx
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+96]
    call   DS::Numbers::Integer::~Integer
    lea    rdi, [rsp+48]
    call   DS::Numbers::Integer::~Integer

    cmp    rbp, r12
    jne    .L22
