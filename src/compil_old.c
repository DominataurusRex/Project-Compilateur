#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compil.h"
#include "tree.h"

extern Node* root;
extern TableCeption* table_ception;
extern char* file_name;
extern int nb_error;
extern int start_flag;
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





int calcTypeExpr(Node* node, char** type) {
    if (node == NULL) {
        *type = "void";
        return 0;
    }
    char* expr_left, * expr_right;
    switch (node->label) {
        case Num: 
            *type = "int";
            return 0;
        case Char:
            *type = "char";
            return 0;
        case Ident:
            printf("Ident WIP\n");
            *type = "wip Ident";
            return 0;
        case Funct:
            printf("Funct WIP\n");
            *type = "wip Funct";
            return 0;
        case UnOperator:
            *type = "int";
            return 0;
        case BiOperator:
            printf("BiOperator WIP\n");
            *type = "wip BiOperator";
            return 0;
        case Order:
            printf("Order WIP\n");
            *type = "wip Order";
            return 0;
        default:
            printf("%d WIP\n", node->label);
    }
    if (calcTypeExpr(node->firstChild, &expr_left)) return 1;
    if (calcTypeExpr(node->firstChild->nextSibling, &expr_right)) return 1;
    if (!strcmp(expr_left, expr_right)) {
        *type = expr_left;
    } else {
        *type = "int";
    }
    return 0;
}


int calcTypeAffect(Node* node, Identifier* funct) {
    printf("-- %s %s --\n", node->ident, funct->id);
    Identifier* var = getHashVar(funct->local_var, node->ident);
    if (!var)
        var = getHashVar(table_ception->global_var, node->ident);

    if (!var) {
        error_flag = 1;
        fprintf(
            stderr,
            "\033[1m%s:%d:%d: \033[31;1merror:\033[0m \033[1m‘%s’\033[0m undeclared\n",
            file_name,
            node->line,
            node->column,
            node->ident
        );
        return 1;
    }
    char* affect_type;
    if (calcTypeExpr(node->firstChild, &affect_type)) return 1;
    if (!strcmp(var->type, affect_type)) {
        // int = int / char = char
        return 0;
    }
    if (!strcmp(var->type, "int")) {
        // int = char
        return 0;
    }
    // char = int
    fprintf(
        stderr,
        "\033[1m%s:%d:%d: \033[35;1mwarning:\033[0m implicit conversion for \033[1m‘%s’\033[0m assignment to type \033[1m‘int’\033[0m\n",
        file_name,
        node->line,
        node->column,
        node->ident
    );
    return 0;
}


int calcTypeReturn(Node* node, Identifier* funct) {
    char* return_type;
    if (calcTypeExpr(node->firstChild, &return_type)) return 1;
    if (!strcmp(funct->type, return_type)) {
        // int return int / char return char / void return void
        printf("%s good same type (calcTypeReturn)\n", funct->id);
        return 0;
    }
    if (!strcmp(funct->type, "void")) {
        // void return int/char
        fprintf(
            stderr,
            "\033[1m%s:%d:%d: \033[35;1mwarning:\033[0m ‘return’ with a value, in function returning void\n",
            file_name,
            node->line,
            node->column
        );
        return 0;
    }
    if (!strcmp(return_type, "void")) {
        // int/char return void
        fprintf(
            stderr,
            "\033[1m%s:%d:%d: \033[35;1mwarning:\033[0m ‘return’ with no value, in function returning non-void\n",
            file_name,
            node->line,
            node->column
        );
        //TODO
        error_flag = 1;
        return 1;
    }
    if (!strcmp(funct->type, "int")) {
        // int return char
        printf("%s good char->int\n", funct->id);
        return 0;
    }
    // char return int
    fprintf(
        stderr,
        "\033[1m%s:%d:%d: \033[35;1mwarning:\033[0m implicit conversion for \033[1m‘return’\033[0m function to type \033[1m‘int’\033[0m\n",
        file_name,
        node->line,
        node->column
    );
    return 0;
}


void calcTypeInstr(Node* node, Identifier* funct, char* name) {
    Node* instr = node;
    int if_return = 0;
    //int if_main = !strcmp(name, "main");
    //if (if_main) fprintf(f, "_start:\n");
    for (; instr != NULL; instr = instr->nextSibling) {
        // Parcour des lignes
        switch (instr->label) {
            case Affect:
                calcTypeAffect(instr, funct);
                break;
            case Return:
                if_return = 1;
                calcTypeReturn(instr, funct);
                break;
            //ajouter cases restants 
            default:
                break;
        }
    }
    //if (if_main) fprintf(f, "mov rax, 60\nmov rdi, 0\nsyscall\n");
    if (strcmp(funct->type, "void") != 0 && !if_return/* && !if_main*/) {
        // TODO (ajouter fin de la fonction au niveau des points d'interrogation)
        fprintf(
            stderr,
            "\033[1m%s:?:?: \033[35;1mwarning:\033[0m control reaches end of non-void function\n",
            file_name
        );
    }
}


void writeStart(){
    fprintf(f,
        "_start:\n"
        "call f_main\n"
        "mov rax, 60\n"
        "xor rdi, rdi\n"
        "syscall\n"
    );
}

void calcType() {
    f = fopen("bin/_anonymous.asm", "w+");
    if (start_flag) fprintf(f, "global _start\n");
    Node* temp = root->firstChild;
    for (; temp != NULL; temp = temp->nextSibling) {
        if (temp->label == DeclFonct) {
            // Parcour de fontion
            Node* expr = temp->firstChild->nextSibling->nextSibling->firstChild;
            char* name =  temp->firstChild->firstChild->nextSibling->ident;
            fprintf(f, "f_%s:\n", name);
            Identifier* funct = getHashVar(table_ception->global_funct, name);
            calcTypeInstr(expr, funct, name);
            fprintf(f, "ret\n");
        }
    }
    if (start_flag) writeStart();
    fclose(f);
}
