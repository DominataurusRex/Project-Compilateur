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
    mov [CHAR_BUFF], rdi
    mov rax, 1
    mov rdi, 1
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    pop rbp
    ret

putint:                         ; Parametre rdi
    push rbp
    mov rbp, rsp
    mov esi, edi                ;arg dans printf
    mov rdi, print_int          ;plagiat de show_registers à partir d'ici lol
    mov rax, 0
    call printf
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
    xor rax, rax
    mov al, [CHAR_BUFF]
    pop rbp
    ret

getint:
    push rbp
    mov rbp, rsp
    xor rax, rax
    xor rdi, rdi
    mov rsi, INT_BUFF
    mov rdx, 16
    syscall

    xor rcx, rcx
    xor r10, r10
    mov r8, 1
    mov r11, 1
    mov r10b, byte [INT_BUFF]

    cmp r10, '-'
    jne .loop_getint
    inc r8
    mov r11, -1
    .loop_getint:
        cmp r8, rax
        jge .end_getint

        mov r10b, byte [INT_BUFF + r8 - 1]
        cmp r10, '0'
        jl .not_valid
        cmp r10, '9'
        jg .not_valid

        imul rcx, 10
        sub r10, '0'
        add rcx, r10

        inc r8
        jmp .loop_getint
    .end_getint:
        imul rcx, r11
        mov rax, rcx
        ret

    .not_valid:
        mov rax, 60
        mov rdi, 5
        pop rbp
        syscall

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
    push 34
    push 43
    call test_f
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
