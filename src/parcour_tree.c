#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcour_tree.h"


void parcourFunctionVar(Table* table, Node* node) {
    Node* start = node->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclVars) {
            start = start->firstChild;
            Node* temp;
            for (; start != NULL; start = start->nextSibling) {
                temp = start->firstChild;
                for (; temp != NULL; temp = temp->nextSibling) {
                    if (!verifHash(table, temp->ident)) {
                        addHash(table, temp->ident, start->ident);
                        printf("Ajout var %s\n", temp->ident);
                    } else {
                        printf("Error dupli var %s\n", temp->ident);
                        exit(1);
                    }
                }
            }
            return;
        }
    }

    /*
    Node* temp = node->firstChild->firstChild;
    */
}


Table* getEnTeteFunct(Table* global_funct, Node* node) {
    Node* en_tete = node->firstChild->firstChild;
    char* name = en_tete->nextSibling->ident;
    if (verifHash(global_funct, name)) {
        printf("Error dupli funct %s\n", name);
        exit(1);
    }
    addHash(global_funct, name, en_tete->ident);
    Table* table = initTableHash(name);
    Node* tmp = en_tete->nextSibling->nextSibling;
    printf("Ajout funct %s\n", name);
    for (; tmp != NULL; tmp = tmp->nextSibling) {
        if (tmp->firstChild->label == Void) break;
        if (!verifHash(table, tmp->firstChild->nextSibling->ident)) {
            addHash(table, tmp->firstChild->nextSibling->ident, tmp->firstChild->ident);
            printf("%s Ajout var %s\n", table->name, tmp->firstChild->nextSibling->ident);
        } else {
            printf("%s Error dupli var %s\n", table->name, tmp->firstChild->nextSibling->ident);
            exit(1);
        }
    }
    return table;
}


void parcourFunction(TableCeption* table_ception, Node* node) {
    Node* start = node->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclFonct) {
            Table* table = getEnTeteFunct(table_ception->global_funct, start);
            parcourFunctionVar(table, start);
            addCeption(table_ception, table);
        }
    }
}





void fillTableCeption(TableCeption* table_ception, Node* root) {
    table_ception->global_var = initTableHash("\%GlobalVar\%");
    parcourFunctionVar(table_ception->global_var, root);
    table_ception->global_funct = initTableHash("\%GlobalFunct\%");
    parcourFunction(table_ception, root);
}
