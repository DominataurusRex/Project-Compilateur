#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compil.h"
#include "tree.h"

extern Node* root;
extern TableCeption* table_ception;
extern char* file_name;
extern int error_flag;
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






void calcTypeExpr(Node* node) {
    printf("-- %d --\n", node->label);
}


void calcTypeAffect(Node* node, Identifier* funct) {
    printf("-- %s %s --\n", node->ident, funct->id);
    Identifier* var = getHashVar(funct->local_var, node->ident);
    if (!var) {
        error_flag = 1;
        fprintf(stderr, "%s:%d:%d: \033[31;1merror:\033[0m ‘%s’ undeclared\n", file_name, node->line, node->column, node->ident);
        return;
    }
}


void calcTypeReturn(Node* node, Identifier* funct) {

}


void calcType() {
    Node* temp = root->firstChild;
    for (; temp != NULL; temp = temp->nextSibling) {
        if (temp->label == DeclFonct) {
            Node* expr = temp->firstChild->nextSibling->nextSibling->firstChild;
            char* name =  temp->firstChild->firstChild->nextSibling->ident;
            if (!table_ception->global_funct) fprintf(stdout, "C\n");
            Identifier* funct = getHashVar(table_ception->global_funct, name);
            for (; expr != NULL; expr = expr->nextSibling) {
                switch (expr->label) {
                    case Affect:
                        calcTypeAffect(expr, funct);
                        break;
                    case Return:
                        calcTypeReturn(expr, funct);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
