#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "implement.h"

extern TableCeption* table_ception;
extern FILE* f_nasm;
static int funct_need = 0;
const char *ban_funct[] = {
    "putint",
    "getint",
    "putchar",
    "getchar"
};


int verifBanDupli(char* name) {
    for (int i = 0; i < V_END; i++) {
        if (!strcmp(ban_funct[i], name)) {
            return 1;
        }
    }
    return 0;
}


void verifBanNeed(char* name) {
    for (int i = 0; i < V_END; i++) {
        if (!strcmp(ban_funct[i], name)) {
            funct_need = funct_need | (1 << i);
            return;
        }
    }
}


void addBanFunct() {
    Identifier* new, * var_temp;
    new = addHashFunct(table_ception->global_funct, "putint", "void");
    new->data.func.param = (Identifier*) malloc(sizeof(Identifier));
    if (!new->data.func.param) exit(4);
    var_temp = initVariable("value", "int", "edi");
    new->data.func.param[0] = *var_temp;
    new->data.func.nb_param = 1;
    free(var_temp);
    
    new = addHashFunct(table_ception->global_funct, "putchar", "void");
    new->data.func.param = (Identifier*) malloc(sizeof(Identifier));
    if (!new->data.func.param) exit(4);
    var_temp = initVariable("value", "char", "dil");
    new->data.func.param[0] = *var_temp;
    new->data.func.nb_param = 1;
    free(var_temp);
    
    new = addHashFunct(table_ception->global_funct, "getint", "int");
    new->data.func.param = (Identifier*) malloc(sizeof(Identifier) * 0);
    if (!new->data.func.param) exit(4);
    new->data.func.nb_param = 0;
    
    new = addHashFunct(table_ception->global_funct, "getchar", "char");
    new->data.func.param = (Identifier*) malloc(sizeof(Identifier) * 0);
    if (!new->data.func.param) exit(4);
    new->data.func.nb_param = 0;
}


static void writePutint() {
    fprintf(
        f_nasm, "f_putint:\n"
                "push rbp\nmov rbp, rsp\npush rdi\npush rsi\npush rdx\n"
                "cmp edi, 0\njl .neg_putint\njmp .pos_putint\n"
                ".neg_putint:\n"
                "imul edi, -1\n"
                "sub rsp, 4\nmov dword [rsp], edi\n"
                "mov byte [%s], '-'\n"
                "mov rax, 1\nmov rdi, 1\nmov rsi, %s\nmov rdx, 1\nsyscall\n"
                "mov edi, [rsp]\nadd rsp, 4\n"
                ".pos_putint:\n"
                "sub rsp, 1\nmov byte [rsp], 'v'\nsub rsp, 1\nmov byte [rsp], 10\n"
                "mov eax, edi\nmov r11d, 10\n"
                ".loop_convert:\n"
                "xor rdx, rdx\nidiv r11d\nadd dl, '0'\n"
                "cmp eax, 0\nje .loop_putint\n"
                "sub rsp, 1\nmov byte [rsp], dl\njmp .loop_convert\n"
                ".loop_putint:\n"
                "mov [%s], dl\nmov rax, 1\nmov rdi, 1\nmov rsi, %s\nmov rdx, 1\nsyscall\n"
                "mov dl, [rsp]\nadd rsp, 1\n"
                "cmp rdx, 'v'\njne .loop_putint\n"
                "mov rax, rdx\n"
                "pop rdx\npop rsi\npop rdi\npop rbp\n"
                "ret\n",
                CHAR_BUFF, CHAR_BUFF, CHAR_BUFF, CHAR_BUFF
    );
}


static void writeGetint() {
    fprintf(
        f_nasm, "f_getint:\n"
                "push rbp\nmov rbp, rsp\n"
                "push rdi\npush rsi\npush rdx\n"
                "xor rax, rax\nxor rdi, rdi\nmov rsi, %s\nmov rdx, 1\nsyscall\n"
                "xor r11, r11\nmov r11b, [%s]\nsub rsp, 4\n"
                "cmp r11, '-'\nje .neg_getint\nmov dword [rsp], 1\njmp .pos_getint\n"
                ".neg_getint:\n"
                "mov dword [rsp], -1\nxor rax, rax\nsyscall\n"
                "xor r11, r11\nmov r11b, [%s]\n"
                ".pos_getint:\n"
                "sub rsp, 4\nmov dword [rsp], 0\n"
                ".loop_getint:\n"
                "cmp r11, 10\nje .end_getint\n"
                "cmp r11, '0'\njl .loop_not_valid\n"
                "cmp r11, '9'\njg .loop_not_valid\n"
                "sub r11, '0'\nmov r10d, [rsp]\n"
                "imul r10, 10\nadd r10, r11\nmov dword [rsp], r10d\n"
                "xor rax, rax\nsyscall\n"
                "xor r11, r11\nmov r11b, [%s]\njmp .loop_getint\n"
                ".loop_not_valid:\n"
                "cmp r11, 10\nje .not_valid\n"
                "xor rax, rax\nsyscall\n"
                "xor r11, r11\nmov r11b, [%s]\njmp .loop_not_valid\n"
                ".not_valid:\n"
                "mov rax, 60\nmov rdi, 5\nsyscall\n"
                ".end_getint:\n"
                "mov eax, [rsp]\nadd rsp, 4\nmov r11d, [rsp]\nadd rsp, 4\nimul eax, r11d\n"
                "pop rdx\npop rsi\npop rdi\npop rbp\n"
                "ret\n",
                CHAR_BUFF, CHAR_BUFF, CHAR_BUFF, CHAR_BUFF, CHAR_BUFF
    );
}


static void writePutchar() {
    fprintf(
        f_nasm, "f_putchar:\n"
                "push rbp\n"
                "mov rbp, rsp\n"
                "push rsi\npush rdx\n"
                "mov [%s], rdi\n"
                "mov rax, 1\nmov rdi, 1\n"
                "mov rsi, %s\nmov rdx, 1\n"
                "syscall\n"
                "mov byte [%s], 10\nsyscall\n"
                "pop rdx\npop rsi\n"
                "pop rbp\n"
                "ret\n",
                CHAR_BUFF, CHAR_BUFF, CHAR_BUFF
    );
}


static void writeGetchar() {
    fprintf(
        f_nasm, "f_getchar:\n"
                "push rbp\nmov rbp, rsp\npush rdi\npush rsi\npush rdx\n"
                "xor rax, rax\nxor rdi, rdi\nmov rsi, %s\nmov rdx, 1\nsyscall\n"
                "xor r11, r11\nmov r11b, [%s]\ndec rsp\nmov byte [rsp], r11b\n"
                ".loop_getchar:\n"
                "cmp r11, 10\nje .end_getchar\nxor rax, rax\nsyscall\n"
                "xor r11, r11\nmov r11b, [%s]\njmp .loop_getchar\n"
                ".end_getchar:\n"
                "xor rax, rax\nmov al, [rsp]\ninc rsp\n"
                "pop rdx\npop rsi\npop rdi\npop rbp\n"
                "ret\n",
                CHAR_BUFF, CHAR_BUFF, CHAR_BUFF
    );
}


void writeBanFunct() {
    printf("-- BF %d\n", funct_need);
    if (funct_need & 1) writePutint();
    if (funct_need & (1 << 1)) writeGetint();
    if (funct_need & (1 << 2)) writePutchar();
    if (funct_need & (1 << 3)) writeGetchar();
}
