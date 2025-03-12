#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "table_sym.h"
#include "tree.h"

Table* initTableHash(char* type) {
    Table* new = (Table*) malloc(sizeof(Table));
    if (new == NULL) exit(1);
    new->type = type;
    for (int i = 0; i < TAILLE; i ++) {
        new->lst_tab[i] = NULL;
    }
    return new;
}

unsigned int functHash(char* ident) {
    int k = 613;
    int tmp = 0;
    for (int i = 0; ident[i] != '\0'; i++) 
        tmp = k * tmp + ident[i];
    return (tmp % (int) pow(2, 30)) % TAILLE;
}

void deleteTableHash(Table* table) {
    printf("WIP\n");
}


int verifHash(Table* table, char* ident, char* type) {
    Variable* var = table->lst_tab[functHash(ident)];
    for (; var != NULL; var = var->suiv) {
        if (!strcmp(ident, var->id)) {
            return 1;
        }
    }
    return 0;
}


void addHash(Table* table, char* ident, char* type) {
    int hash = functHash(ident);
    Variable* new = (Variable*) malloc(sizeof(Variable));
    if (new == NULL) exit(1);
    new->id = ident;
    new->type = type;
    printf("%d\n", hash);
    new->suiv = table->lst_tab[hash];
    table->lst_tab[hash] = new;
}


void showHash(Table* table) {
    fprintf(stdout, "========== %s ==========\n", table->type);
    Variable* var;
    for (int i = 0; i < TAILLE; i++) {
        var = table->lst_tab[i];
        for (; var != NULL; var = var->suiv) {
            fprintf(stdout, "Bucket %-2d | Type: %-4s | Id: %s\n", i, var->type, var->id);
        }
    }
}
