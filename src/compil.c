#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compil.h"
#include "tree.h"

extern Node* root;
FILE* f;


void subNasm(Node* node) {
    instruction(node->firstChild);
    instruction(node->firstChild->nextSibling);
    fprintf(f, "pop rsi\n"); //2
    fprintf(f, "pop rdi\n"); //45
    fprintf(f, "sub rdi, rsi\n"); //45-2
    fprintf(f, "push rdi\n"); //43

}


void biOperator(Node* node) {
    printf("-- %c\n", node->byte);
    switch (node->byte)
    {
    case '-':
        subNasm(node);
        break;
    
    default:
        break;
    }
}


void instruction(Node* node) {
    printf("-- %c\n", node->label);
    switch (node->label)
    {
    case BiOperator:
        biOperator(node);
        break;
    case Num:
        fprintf(f, "push %d\n", node->num);
        break;
    default:
        break;
    }
}

void createNasm() {
    f = fopen("bin/_anonymous.asm", "w+");
    Node* start = root->firstChild->nextSibling;
    for(; start != NULL; start = start->nextSibling){
        if (!strcmp(start->firstChild->firstChild->nextSibling->ident, "main")){
            fprintf(f, "global _start\nsection .text\n_start:\n");
            instruction(start->firstChild->nextSibling->nextSibling->firstChild->firstChild);

            fprintf(f, "mov rax, 60\nmov rdi, 0\nsyscall\n");
        }
    }
    fclose(f);
}
