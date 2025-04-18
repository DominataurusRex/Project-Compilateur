#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcour_tree.h"
#include "tree.h"

TableCeption* table_ception;
extern Node* root;
extern char* file_name;
extern int nb_error;
int start_flag;


int fillTableVariable(Table* table, Node* node, int is_global) {
    Node* start = node->firstChild;
    int toto_mem = 0;
    char buff[16];
    for (; start != NULL; start = start->nextSibling) {
        // Cherche le noeud DeclVars
        if (start->label == DeclVars) {
            start = start->firstChild;
            // Parcour chaque Declvars
            for (; start != NULL; start = start->nextSibling) {
                Node* cursor = start->firstChild;
                // Parcour chaque Ident dans start
                for (; cursor != NULL; cursor = cursor->nextSibling) {
                    if (verifHash(table, cursor->ident) || verifHash(table_ception->global_var, cursor->ident)) {
                        nb_error++;
                        fprintf(
                            stderr,
                            "\033[1m%s:%d:%d\033[31;1m error:\033[0m redefinition of \033[1m‘%s’\033[0m\n",
                            file_name,
                            cursor->line,
                            cursor->column,
                            cursor->ident
                        );
                    } else {
                        if (!strcmp(cursor->ident, "main")) fprintf(
                            stderr,
                            "\033[1m%s:%d:%d\033[35;1m warning:\033[0;1m ‘%s’\033[0m is usually a function\n",
                            file_name,
                            cursor->line,
                            cursor->column,
                            cursor->ident
                        );
                        if (is_global) {
                            sprintf(buff, "[%s+%d]", GLOBAL_VAR, toto_mem);
                            addHashVar(table, cursor->ident, start->ident, buff, start->label == StaticType);
                            toto_mem += !strcmp(start->ident, "int")? 4: 1;
                        } else {
                            toto_mem += !strcmp(start->ident, "int")? 4: 1;
                            sprintf(buff, "[rbp-%d]", toto_mem);
                            addHashVar(table, cursor->ident, start->ident, buff, start->label == StaticType);
                        }
                       
                    }
                }
            }
            return toto_mem;
        }
    }
    return 0;
}


void getParamAdress(char adress[16], int param_val, char* param_type) {
    switch (param_val)
    {
        case 1: strcpy(adress, !strcmp(param_type, "int")? "edi": "dil"); break;
        case 2: strcpy(adress, !strcmp(param_type, "int")? "esi": "sil"); break;
        case 3: strcpy(adress, !strcmp(param_type, "int")? "edx": "dl"); break;
        case 4: strcpy(adress, !strcmp(param_type, "int")? "ecx": "cl"); break;
        case 5: strcpy(adress, !strcmp(param_type, "int")? "r8d": "r8b"); break;
        case 6: strcpy(adress, !strcmp(param_type, "int")? "r9d": "r9b"); break;
    
    default:
        sprintf(adress, "-");
    }
}


void parcourParamFunct(Identifier* funct, Node* node) {
    if (node->firstChild->label == Void) {
        funct->data.func.nb_param = 0;
        return;
    }
    int nb_param = 0;
    int size_pile = 0;      // Taille de la pile si parametre dans la pile
    char adress[16];

    Node* cursor = node;
    for (; cursor; cursor = cursor->nextSibling) {
        // Compte le nombre de parametre
        nb_param++;
    }

    funct->data.func.param = (Identifier*) malloc(sizeof(Identifier) * nb_param);
    cursor = node;
    for (int i = nb_param; i > 0; i--) {
        // Place les parametres dans la liste
        getParamAdress(adress, i, cursor->firstChild->ident);
        Identifier* var_temp = initVariable(cursor->firstChild->nextSibling->ident, cursor->firstChild->ident, adress);
        funct->data.func.param[i - 1] = *var_temp;
        free(var_temp);
        cursor = cursor->nextSibling;
    }

    for (int j = 6; j < nb_param; j++) {
        printf("((%s))\n", funct->data.func.param[j].data.var.id);
        sprintf(adress, "[rbp+%d]", size_pile);
        funct->data.func.param[j].data.var.adress = (char*) malloc(sizeof(char) * strlen(adress));
        strcpy(funct->data.func.param[j].data.var.adress, adress);
        size_pile += !strcmp(funct->data.func.param[j].data.var.type, "int")? 4: 1;
    }
    funct->data.func.nb_param = nb_param;
    return;
}


/**
 * Initialise un `identifier` FUNCTION avec le noeud EnTeteFonct
 * @param head La racine EnTeteFonct
 * @return L'adresse de `identifier` cree
 */
Identifier* fillEnTeteFunct(Node* head) {
    Identifier* new = NULL;
    Node* name = head->firstChild->firstChild->nextSibling;
    if (verifHash(table_ception->global_var, name->ident)) {
        // Present dans global_var
        nb_error++;
        fprintf(
            stderr,
            "\033[1m%s:%d:%d\033[31;1m error:\033[0;1m ‘%s’\033[0m redeclared as different kind of symbol\n",
            file_name,
            name->line,
            name->column,
            name->ident
        );
    } else if (verifHash(table_ception->global_funct, name->ident)) {
        // Present dans global_funct
        nb_error++;
        fprintf(
            stderr,
            "\033[1m%s:%d:%d\033[31;1m error:\033[0m redefinition of \033[1m‘%s’\033[0m\n",
            file_name,
            name->line,
            name->column,
            name->ident
        );
    } else {
        new = addHashFunct(table_ception->global_funct, name->ident, head->firstChild->firstChild->label == Void? "void": head->firstChild->firstChild->ident);
        parcourParamFunct(new, name->nextSibling);
    }
    return new;
}


void parcourFunction() {
    Node* start = root->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclFonct) {
            Identifier* new = fillEnTeteFunct(start);
            new->data.func.size_alloc = fillTableVariable(new->data.func.local_var, start, 0);
        }
    }
}



void fillTableCeption() {
    table_ception = initTableCeption();
    table_ception->size_alloc_var = fillTableVariable(table_ception->global_var, root, 1);
    parcourFunction();
    
}
