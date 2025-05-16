; Gestion de la memoire
section .data
    format_registers db "rbx:%ld r12:%ld r13:%ld r14:%ld", 10, 0
    print_int db "%d", 10, 0

;-------------- Variable Global --------------;
section .bss
    GLOBAL_VAR resb 8       ; Reserve 8x 1 octet
;-------------- Variable Global --------------;
    CHAR_BUFF resb 1
    INT_BUFF resb 16

section .text
    global _start

global show_registers
extern printf


show_registers:
    push rbp
    mov rbp, rsp
    
    mov r8,  r14
    mov rcx, r13
    mov rdx, r12
    mov rsi, rbx
    mov rdi, format_registers
    mov rax, 0
    call printf 
        
    pop rbp
    ret


putchar:                       ; Parametre rdi
    push rbp
    mov rbp, rsp
    mov [CHAR_BUFF], dil
    mov rax, 1
    mov rdi, 1
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    mov byte [CHAR_BUFF], 10
    syscall
    pop rbp
    ret

putint:                         ; Parametre rdi
    push rbp
    mov rbp, rsp
    cmp edi, 0
    jl .neg_putint
    jmp .pos_putint
    .neg_putint:
        imul edi, -1
        sub rsp, 4
        mov dword [rsp], edi
        mov byte [CHAR_BUFF], '-'
        mov rax, 1
        mov rdi, 1
        mov rsi, CHAR_BUFF
        mov rdx, 1
        syscall
        mov edi, [rsp]
        add rsp, 4
    .pos_putint:
    sub rsp, 1
    mov byte [rsp], 'v'
    sub rsp, 1
    mov byte [rsp], 10
    mov eax, edi
    mov r11d, 10
    .loop_convert:
    xor rdx, rdx
    idiv r11d
    add dl, '0'
    cmp eax, 0
    je .loop_putint
        sub rsp, 1
        mov byte [rsp], dl
        jmp .loop_convert
    .loop_putint:
    mov [CHAR_BUFF], dl
    mov rax, 1
    mov rdi, 1
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    mov dl, [rsp]
    add rsp, 1
    cmp rdx, 'v'
    jne .loop_putint
    mov rax, rdx
    mov rsp, rbp
    pop rbp
    ret


getchar:                        ; Retour rax
    push rbp
    mov rbp, rsp
    xor rax, rax
    xor rdi, rdi
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    xor r11, r11
    mov r11b, [CHAR_BUFF]
    dec rsp
    mov byte [rsp], r11b
    .loop_getchar:
        cmp r11, 10             ; ascii \n
        je .end_getchar
        xor rax, rax
        syscall
        xor r11, r11
        mov r11b, [CHAR_BUFF]
        jmp .loop_getchar
    .end_getchar:
    xor rax, rax
    mov al, [rsp]
    inc rsp
    pop rbp
    ret

getint:
    push rbp
    mov rbp, rsp
    xor rax, rax
    xor rdi, rdi
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    xor r11, r11
    mov r11b, [CHAR_BUFF]
    sub rsp, 4
    cmp r11, '-'
    je .neg_getint
    mov dword [rsp], 1
    jmp .pos_getint
    .neg_getint:
    mov dword [rsp], -1
    xor rax, rax
    syscall
    xor r11, r11
    mov r11b, [CHAR_BUFF]
    .pos_getint:
    sub rsp, 4
    mov dword [rsp], 0
    .loop_getint:
        cmp r11, 10
        je .end_getint
        cmp r11, '0'
        jl .loop_not_valid
        cmp r11, '9'
        jg .loop_not_valid
        sub r11, '0'
        mov r10d, [rsp]
        imul r10, 10
        add r10, r11
        mov dword [rsp], r10d
        xor rax, rax
        syscall
        xor r11, r11
        mov r11b, [CHAR_BUFF]
        jmp .loop_getint
    .loop_not_valid:
        cmp r11, 10             ; ascii \n
        je .not_valid
        xor rax, rax
        syscall
        xor r11, r11
        mov r11b, [CHAR_BUFF]
        jmp .loop_not_valid
    .not_valid:
        mov rax, 60
        mov rdi, 4
        syscall
    .end_getint:
    mov eax, [rsp]
    add rsp, 4
    mov r11d, [rsp]
    add rsp, 4
    imul eax, r11d
    pop rbp
    ret

test_funct:
    ;-------------- Variables Local --------------;
    push rbp                ; Sauvegarde ancien pointeur de base
    mov rbp, rsp            ; Modifie le pointeur de base par le pointeur de sommet de Pile
    ;-----------------------;

    ; -- Allocation  --
    sub rsp, 5                      ; 8 Octets (ex: char / int)

    ; -- Affectation --
    mov byte [rbp - 1], 'a'        ; Adresse relative : 4
    mov dword [rbp - 5], 34         ; Adresse relative : 8

    ; Recuperation   --
    xor rbx, rbx
    mov bl, [rbp - 1]
    mov r12d, [rbp - 5]

    ;-----------------------;
    mov rsp, rbp            ; Replace le sommet de pile a la base de la fonction
    pop rbp                 ; Recupere le pointeur de base
    ret                     ; Retour de la fonction
    ;-------------- Variables Local --------------;


test_f:
    push rbp
    mov rbp, rsp

    mov rdi, [rbp + 16]
    call putint
    mov rdi, [rbp + 24]
    call putint

    mov rsp, rbp
    pop rbp
    ret



_start:
    ;-------------- Alignement Pile --------------;
    mov r11, rsp            ; Pointeur de Pile
    sub rsp, 8              ; Alignement appel fonction (alloue de la place y placer rsp)
    and rsp, -16            ; aligne rsp vers le bas (conserve le multiple de 16)
    mov qword [rsp], r11    ; Place rsp dans la Pile
    ;-----------------------;
    call getint
    mov rdi, rax
    call putint
    ;-----------------------;
    pop rsp                 ; Recupere rsp dans la Pile
    ;-------------- Alignement Pile --------------;

    ;---- Ex var global ----;
    mov dword [GLOBAL_VAR], 76      ; Adresse relative : 0
    mov dword [GLOBAL_VAR + 4], 138 ; Adresse relative : 4

    mov r13d, [GLOBAL_VAR]
    mov r14d, [GLOBAL_VAR + 4]
    ;---- Ex var global ----;


    ; call show_registers

    mov rax, 60
    xor rdi, rdi
    syscall
