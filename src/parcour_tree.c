#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcour_tree.h"
#include "tree.h"

TableCeption* table_ception;
extern Node* root;


void parcourFunctionVar(Table* table, Node* node) {
    Node* start = node->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclVars) {
            start = start->firstChild;
            Node* temp;
            for (; start != NULL; start = start->nextSibling) {
                temp = start->firstChild;
                for (; temp != NULL; temp = temp->nextSibling) {
                    if (!verifHash(table, temp->ident) && !verifHash(table_ception->global_var, temp->ident)) {
                        addHashVar(table, temp->ident, start->ident, start->label == StaticType? 1: 0);
                        // printf("Ajout var %s\n", temp->ident);
                    } else {
                        printf("Error dupli var %s\n", temp->ident);
                        exit(1);
                    }
                }
            }
            return;
        }
    }
}


Table* getEnTeteFunct(Node* node) {
    Node* en_tete = node->firstChild->firstChild;       // Position 1er fils EnTeteFonct
    char* name = en_tete->nextSibling->ident;
    if (verifHash(table_ception->global_funct, name)) {
        printf("Error dupli funct %s\n", name);
        exit(1);
    }
    Table* table = addHashFunct(table_ception->global_funct, name, en_tete->label == Void? "void": en_tete->ident);
    Node* tmp = en_tete->nextSibling->nextSibling;
    // printf("Ajout funct %s\n", name);
    for (; tmp != NULL; tmp = tmp->nextSibling) {
        if (tmp->firstChild->label == Void) break;
        if (!verifHash(table, tmp->firstChild->nextSibling->ident)) {
            addHashVar(table, tmp->firstChild->nextSibling->ident, tmp->firstChild->ident, 0);
            // printf("%s Ajout var %s\n", name, tmp->firstChild->nextSibling->ident);
        } else {
            printf("%s Error dupli var %s\n", name, tmp->firstChild->nextSibling->ident);
            exit(1);
        }
    }
    return table;
}


/**
 * Parcour chaque fonction dans l'arbre
 */
void parcourFunction() {
    Node* start = root->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclFonct) {
            Table* table = getEnTeteFunct(start);
            parcourFunctionVar(table, start);
        }
    }
}


void fillTableCeption() {
    table_ception = initTableCeption();
    parcourFunctionVar(table_ception->global_var, root);
    parcourFunction();
}
