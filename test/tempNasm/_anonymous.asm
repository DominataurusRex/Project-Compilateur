; Gestion de la memoire
section .data
    format_registers db "rbx:%ld r12:%ld r13:%ld r14:%ld", 10, 0

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
    mov [CHAR_BUFF], rdi
    mov rax, 1
    mov rdi, 1
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    ret


putint:                         ; Parametre rdi
    mov r11, INT_BUFF + 16
    mov rax, rdi
    mov rbx, 10
    cmp rdi, 0

    jpe .convert_putint         ; Le rend positif
    neg rax

    .convert_putint:            ; Boucle de conversion
        xor rdx, rdx            ; Reset rdx
        div rbx                 ; rax = /10 // rdx = %10
        add rdx, '0'            ; conversion
        dec r11                 ; Decalage du pointeur du buffer
        mov [r11], dl           ; Deplacmement dans le buffer
        test rax, rax
        jnz .convert_putint

    cmp rdi, 0                  ; Rajoute le `-` si negatif
    jpe .end_putint
    mov r10, '-'
    dec r11
    mov [r11], r10b

    .end_putint:                ; Affiche
        mov rax, 1
        mov rdi, 1
        mov rsi, r11
        mov rdx, INT_BUFF + 16
        sub rdx, r11
        syscall
        ret


getchar:                        ; Retour rax
    mov rax, 0
    mov rdi, 0
    mov rsi, CHAR_BUFF
    mov rdx, 1
    syscall
    xor rax, rax
    mov al, [CHAR_BUFF]
    ret


test_funct:
    ;-------------- Variables Local --------------;
    push rbp                ; Sauvegarde ancien pointeur de base
    mov rbp, rsp            ; Modifie le pointeur de base par le pointeur de sommet de Pile
    ;-----------------------;

    ; -- Allocation  --
    sub rsp, 8                      ; 8 Octets (ex: char / int)

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



_start:
    mov rbx, rsp
    ;-------------- Alignement Pile --------------;
    mov r11, rsp            ; Pointeur de Pile
    sub rsp, 8              ; Alignement appel fonction
    and rsp, -16            ; aligne rsp vers le bas (clear les 4 bits de poids faible)
    mov qword [rsp], r11    ; Place rsp dans la Pile
    ;-----------------------;
    call test_funct
    ;-----------------------;
    pop rsp                 ; Recupere rsp dans la Pile
    ;-------------- Alignement Pile --------------;

    ;---- Ex var global ----;
    mov dword [GLOBAL_VAR], 76      ; Adresse relative : 0
    mov dword [GLOBAL_VAR + 4], 138 ; Adresse relative : 4

    mov r13d, [GLOBAL_VAR]
    mov r14d, [GLOBAL_VAR + 4]
    ;---- Ex var global ----;


    call show_registers

    mov rax, 60
    xor rdi, rdi
    syscall
