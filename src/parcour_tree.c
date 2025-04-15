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


void fillTableVariable(Table* table, Node* node) {
    Node* start = node->firstChild;
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
                        addHashVar(table, cursor->ident, start->ident, "¯\\_(ツ)_/¯", start->label == StaticType);
                    }
                }
            }
            return;
        }
    }
}


int parcourParamFunct(Identifier* funct, Node* cursor, int nb_param) {
    if (cursor == NULL || cursor->firstChild->label == Void) {
        funct->data.func.param = (Identifier*) malloc(sizeof(Identifier) * nb_param);
        if (!funct->data.func.param) exit(3); 
        return nb_param;
    }
    int toto_param = parcourParamFunct(funct, cursor->nextSibling, nb_param + 1);
    Identifier* var_temp = initVariable(cursor->firstChild->nextSibling->ident, cursor->firstChild->ident, "¯\\_(ツ)_/¯");
    funct->data.func.param[toto_param - nb_param - 1] = *var_temp;
    free(var_temp);
    return toto_param;
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
        new->data.func.nb_param = parcourParamFunct(new, name->nextSibling, 0);
    }
    return new;
}


void parcourFunction() {
    Node* start = root->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclFonct) {
            Identifier* new = fillEnTeteFunct(start);
            fillTableVariable(new->data.func.local_var, start);
        }
    }
}



void fillTableCeption() {
    table_ception = initTableCeption();
    fillTableVariable(table_ception->global_var, root);
    parcourFunction();
    
}
