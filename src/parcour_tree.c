#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcour_tree.h"
#include "tree.h"

TableCeption* table_ception;
extern Node* root;
extern char* file_name;
extern int error_flag;
int start_flag;


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
                            "\033[1m%s:%d:%d \033[31;1merror:\033[0m redefinition of ‘%s’\n",
                            file_name,
                            temp->line,
                            temp->column,
                            temp->ident
                        );
                    }
                    addHashVar(table, temp->ident, start->ident, "Variable", start->label == StaticType? 1: 0);
                }
            }
            return;
        }
    }
}


int fillTabParam(Identifier*** tab_param, Node* node, int current_size) {
    fprintf(stderr, "1 Hey\n");
    if (current_size == 0 && node->firstChild->label == Void) return 0;
    fprintf(stderr, "2 Hey\n");
    if (!node) {
    fprintf(stderr, "3 Hey %d\n", current_size);
        *tab_param = (Identifier**) malloc(sizeof(Identifier*) * current_size);
        if (!tab_param) exit(3);
        return current_size;
    }
    int size = fillTabParam(tab_param, node->nextSibling, current_size + 1);
    fprintf(stderr, "4 Hey %d\n", current_size);
    char* adress;
    switch (current_size)
    {
    case 0:
        adress = "rdi";
        break;
    case 1:
        adress = "rsi";
        break;
    case 2:
        adress = "rdx";
        break;
    case 3:
        adress = "rcx";
        break;
    case 4:
        adress = "r8";
        break;
    case 5:
        adress = "r9";
    default:
        sprintf(adress, "[rbp - %d]", (size - current_size) * 8);
    }
    *(tab_param)[current_size] = initVariable(node->firstChild->nextSibling->ident, node->firstChild->ident, adress);
    return size;
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
    if (!strcmp(name, "main")) start_flag = 1;
    Table* table = addHashFunct(table_ception->global_funct, name, en_tete->label == Void? "void": en_tete->ident);
    Node* tmp = en_tete->nextSibling->nextSibling;
    // printf("Ajout funct %s\n", name);
    /*
    Identifier** tab_param;
    int size = fillTabParam(&tab_param, tmp, 0);
    for (int i = 0; i < size; i ++) {
        fprintf(stdout, "--> %s\n", tab_param[i]->id);
    }
    */
    for (; tmp != NULL; tmp = tmp->nextSibling) {
        if (tmp->firstChild->label == Void) break;
        if (verifHash(table, tmp->firstChild->nextSibling->ident) || verifHash(table_ception->global_var, tmp->firstChild->nextSibling->ident)) {
            error_flag = 1;
            fprintf(
                stderr,
                "\033[1m%s:%d:%d \033[31;1merror:\033[0m redefinition of ‘%s’\n",
                file_name,
                tmp->firstChild->nextSibling->line,
                tmp->firstChild->nextSibling->column,
                tmp->firstChild->nextSibling->ident
            );
        }
        addHashVar(table, tmp->firstChild->nextSibling->ident, tmp->firstChild->ident, "Param", 0);
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
