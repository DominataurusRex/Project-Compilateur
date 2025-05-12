section .bss
CHAR_BUFF resb 1
section .text
global _start
f_main:
push rbp
mov rbp, rsp
sub rsp, 4
sub rsp, 4
mov dword [rsp], 6
mov r11d, [rsp]
add rsp, 4
mov dword [rbp-4], r11d
sub rsp, 4
mov dword [rsp], 0
mov r11d, [rsp]
add rsp, 4
cmp r11, 0
jne .label_4
jmp .label_5
.label_4:
sub rsp, 4
mov dword [rsp], 0
mov r11d, [rsp]
add rsp, 4
cmp r11, 0
jne .label_7
jmp .label_8
.label_7:
sub rsp, 4
mov dword [rsp], 8
mov r11d, [rsp]
add rsp, 4
mov dword [rbp-4], r11d
jmp .label_9 ;ICICICICICI
.label_8:
sub rsp, 4
mov dword [rsp], 9
mov r11d, [rsp]
add rsp, 4
mov dword [rbp-4], r11d
.label_9:
jmp .label_6 ;ICICICICICI
.label_5:
sub rsp, 4
mov dword [rsp], 0
mov r11d, [rsp]
add rsp, 4
cmp r11, 0
jne .label_16
jmp .label_17
.label_16:
sub rsp, 4
mov dword [rsp], 1
mov r11d, [rsp]
add rsp, 4
mov dword [rbp-4], r11d
jmp .label_18 ;ICICICICICI
.label_17:
sub rsp, 4
mov dword [rsp], 10
mov r11d, [rsp]
add rsp, 4
mov dword [rbp-4], r11d
.label_18:
.label_6:
mov r11, rsp
sub rsp, 8
and rsp, -16
add rsp, 0
mov qword [rsp], r11
mov r11d, [rbp-4]
sub rsp, 4
mov dword [rsp], r11d
mov edi, [rsp]
add rsp, 4
call f_putint
add rsp, 0
pop rsp
sub rsp, 4
mov dword [rsp], 0
mov eax, [rsp]
add rsp, 4
mov rsp, rbp
pop rbp
ret
mov rsp, rbp
pop rbp
ret
_start:
call f_main
mov rdi, rax
mov rax, 60
syscall
f_putint:
push rbp
mov rbp, rsp
push rdi
push rsi
push rdx
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
pop rdx
pop rsi
pop rdi
pop rbp
ret
