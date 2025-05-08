section .bss
CHAR_BUFF resb 1
INT_BUFF resb 16
section .text
global _start
f_mult:
push rbp
mov rbp, rsp
mov r11d, esi
sub rsp, 4
mov dword [rsp], r11d
mov r11d, edi
sub rsp, 4
mov dword [rsp], r11d
mov r10d, [rsp]
add rsp, 4
mov r11d, [rsp]
add rsp, 4
imul r10d, r11d
sub rsp, 4
mov dword [rsp], r10d
mov eax, [rsp]
add rsp, 4
mov rsp, rbp
pop rbp
ret
mov rsp, rbp
pop rbp
ret
f_test:
push rbp
mov rbp, rsp
mov r11b, [rbp+16]
sub rsp, 1
mov byte [rsp], r11b
sub rsp, 1
mov byte [rsp], dil
sub rsp, 4
mov dword [rsp], esi
mov r11, rsp
sub rsp, 8
and rsp, -16
add rsp, 0
mov qword [rsp], r11
mov r11d, r9d
sub rsp, 4
mov dword [rsp], r11d
sub rsp, 1
mov byte [rsp], dil
sub rsp, 4
mov dword [rsp], esi
mov r11, rsp
sub rsp, 8
and rsp, -16
add rsp, 0
mov qword [rsp], r11
mov r11b, dil
sub rsp, 1
mov byte [rsp], r11b
mov r11b, r8b
sub rsp, 1
mov byte [rsp], r11b
xor rax, rax
xor rbx, rbx
mov r11, rdx
xor rdx, rdx
mov al, [rsp]
add rsp, 1
mov bl, [rsp]
add rsp, 1
idiv rbx
sub rsp, 4
mov dword [rsp], edx
mov rdx, r11
mov r11d, [rsp]
add rsp, 4
neg r11
sub rsp, 4
mov dword [rsp], r11d
mov r11d, esi
sub rsp, 4
mov dword [rsp], r11d
mov r11d, ecx
sub rsp, 4
mov dword [rsp], r11d
mov r11, rdx
xor rdx, rdx
mov eax, [rsp]
add rsp, 4
mov ebx, [rsp]
add rsp, 4
idiv rbx
sub rsp, 4
mov dword [rsp], eax
mov rdx, r11
mov edi, [rsp]
add rsp, 4
mov esi, [rsp]
add rsp, 4
call f_mult
add rsp, 0
pop rsp
mov esi, [rsp]
add rsp, 4
mov dil, [rsp]
add rsp, 1
sub rsp, 4
mov dword [rsp], eax
sub rsp, 1
mov byte [rsp], dil
sub rsp, 4
mov dword [rsp], esi
mov r11, rsp
sub rsp, 8
and rsp, -16
add rsp, 0
mov qword [rsp], r11
mov r11b, dl
sub rsp, 1
mov byte [rsp], r11b
mov r11b, [rsp]
add rsp, 1
sub rsp, 4
mov dword [rsp], r11d
mov r11d, esi
sub rsp, 4
mov dword [rsp], r11d
mov r11b, dil
sub rsp, 1
mov byte [rsp], r11b
xor r10, r10
mov r10b, [rsp]
add rsp, 1
mov r11d, [rsp]
add rsp, 4
add r10d, r11d
sub rsp, 4
mov dword [rsp], r10d
mov edi, [rsp]
add rsp, 4
mov esi, [rsp]
add rsp, 4
call f_mult
add rsp, 0
pop rsp
mov esi, [rsp]
add rsp, 4
mov dil, [rsp]
add rsp, 1
sub rsp, 4
mov dword [rsp], eax
mov r10d, [rsp]
add rsp, 4
mov r11d, [rsp]
add rsp, 4
sub r10d, r11d
sub rsp, 4
mov dword [rsp], r10d
mov edi, [rsp]
add rsp, 4
mov esi, [rsp]
add rsp, 4
call f_mult
add rsp, 0
pop rsp
mov esi, [rsp]
add rsp, 4
mov dil, [rsp]
add rsp, 1
sub rsp, 4
mov dword [rsp], eax
xor r11, r11
mov r10d, [rsp]
add rsp, 4
mov r11b, [rsp]
add rsp, 1
add r10d, r11d
sub rsp, 4
mov dword [rsp], r10d
mov eax, [rsp]
add rsp, 4
mov rsp, rbp
pop rbp
ret
mov rsp, rbp
pop rbp
ret
f_temp:
push rbp
mov rbp, rsp
mov r11d, edi
sub rsp, 4
mov dword [rsp], r11d
mov eax, [rsp]
add rsp, 4
mov rsp, rbp
pop rbp
ret
mov rsp, rbp
pop rbp
ret
f_main:
push rbp
mov rbp, rsp
sub rsp, 4
sub rsp, 4
mov dword [rsp], 0
mov r11d, [rsp]
add rsp, 4
mov dword [rbp-4], r11d
mov r11d, [rbp-4]
sub rsp, 4
mov dword [rsp], r11d
.61:
sub rsp, 4
mov dword [rsp], 8
mov eax, [rsp]
add rsp, 4
mov rsp, rbp
pop rbp
ret
jmp .63: ;ICICICICICI
.62:
sub rsp, 4
mov dword [rsp], 2
mov eax, [rsp]
add rsp, 4
mov rsp, rbp
pop rbp
ret
sub rsp, 4
mov dword [rsp], 6
mov r11d, [rsp]
add rsp, 4
neg r11
sub rsp, 4
mov dword [rsp], r11d
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