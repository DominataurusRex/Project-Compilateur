#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcour_tree.h"
#include "tree.h"

TableCeption* table_ception;
extern Node* root;
extern char* file_name;
extern int error_flag;


/**
 * Permet de remplir la table des variables `table`.
 * Si une variable est redefinie, fait passer le flag `error_flag` a 1.
 * @param table La table de symboles des variables
 * @param node Le noeud ayant pour fils des noeuds `DeclVars`
 */
void parcourFunctionVar(Table* table, Node* node) {
    Node* start = node->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclVars) {
            start = start->firstChild;
            Node* temp;
            for (; start != NULL; start = start->nextSibling) {
                temp = start->firstChild;
                for (; temp != NULL; temp = temp->nextSibling) {
                    if (verifHash(table, temp->ident) || verifHash(table_ception->global_var, temp->ident)) {
                        error_flag = 1;
                        fprintf(
                            stderr,
                            "%s:%d:%d \033[31;1merror:\033[0m redefinition of ‘%s’\n",
                            file_name,
                            temp->line,
                            temp->column,
                            temp->ident
                        );
                    }
                    addHashVar(table, temp->ident, start->ident, start->label == StaticType? 1: 0);
                }
            }
            return;
        }
    }
}


/**
 * Rajoute la fonction dans la table des fonctions et renvoie la table de ses parametres.
 * Si une fonction/variable est redefinie, fait passer le flag `error_flag` a 1.
 * @param node La racine de la fonction (DeclFonct)
 * @return La table des symboles de ses parametres
 */
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
        if (verifHash(table, tmp->firstChild->nextSibling->ident) || verifHash(table_ception->global_var, tmp->firstChild->nextSibling->ident)) {
            error_flag = 1;
            fprintf(
                stderr,
                "%s:%d:%d \033[31;1merror:\033[0m redefinition of ‘%s’\n",
                file_name,
                tmp->firstChild->nextSibling->line,
                tmp->firstChild->nextSibling->column,
                tmp->firstChild->nextSibling->ident
            );
        }
        addHashVar(table, tmp->firstChild->nextSibling->ident, tmp->firstChild->ident, 0);
        // printf("%s Ajout var %s\n", name, tmp->firstChild->nextSibling->ident);
    }
    return table;
}


/**
 * Parcour chaque fonction dans l'arbre.
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
