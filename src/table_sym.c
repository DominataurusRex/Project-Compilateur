#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "table_sym.h"

Table* initTableHash() {
    Table* new = (Table*) malloc(sizeof(Table));
    if (new == NULL) exit(1);
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


int addHash(Table* table, char* ident, char* type) {
    int val = functHash(ident);
    Variable* temp = &table->lst_tab[val];
    for (; temp->id != NULL; temp = temp->suiv) {
        if (strcmp(ident, temp->id) == 0) {
            printf("Present  %2d %s\n", val, ident);
            return 1;
        }
    }
    printf("Ajout    %2d %s\n", val, ident);
    temp->id = ident;
    temp->type = type;
    temp->suiv = (Variable*) malloc(sizeof(Variable));
    return 0;
}


void showHash(Table* table) {
    for (int i = 0; i < TAILLE; i++) {
        if (table->lst_tab[i].id != NULL) {
            fprintf(stdout, "========== %2d ==========\n", i);
            Variable* temp = &table->lst_tab[i];
            for (; temp->id != NULL; temp = temp->suiv) {
                fprintf(stdout, "Id: %-16s Type: %-6s\n", temp->id, temp->type);
            }
            fprintf(stdout, "\n");
        }
    }
}
