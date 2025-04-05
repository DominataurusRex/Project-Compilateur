; Gestion de la memoire
section .data
    format_registers db "rbx:%ld r12:%ld r13:%ld r14:%ld", 10, 0

;-------------- Variable Global --------------;
section .bss
    global_var resb 8       ; Reserve 8x 1 octet
;-------------- Variable Global --------------;
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


test_funct:
    ;-------------- Variables Local --------------;
    push rbp                ; Sauvegarde ancien pointeur de base
    mov rbp, rsp            ; Modifie le pointeur de base par le pointeur de sommet de Pile
    ;-----------------------;

    ; -- Allocation  --
    sub rsp, 8                      ; 8 Octets (ex: char / int)

    ; -- Affectation --
    mov dword [rbp - 4], 'a'        ; Adresse relative : 4
    mov dword [rbp - 8], 34         ; Adresse relative : 8

    ; Recuperation   --
    mov ebx, [rbp - 4]
    mov r12d, [rbp - 8]

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
    mov dword [global_var], 76      ; Adresse relative : 0
    mov dword [global_var + 4], 138 ; Adresse relative : 4

    mov r13d, [global_var]
    mov r14d, [global_var + 4]
    ;---- Ex var global ----;

    call show_registers

    mov rax, 60
    xor rdi, rdi
    syscall
