#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "table_sym.h"
#include "tree.h"

TableCeption* initTableCeption() {
    TableCeption* new = (TableCeption*) malloc(sizeof(TableCeption));
    if (new == NULL) exit(1);
    new->global_var = NULL;
    new->global_funct = NULL;
    for (int i = 0; i < TAILLE; i++) {
        new->lst_tab[i] = NULL;
    }
    return new;
}


Table* initTableHash(char* name) {
    Table* new = (Table*) malloc(sizeof(Table));
    if (new == NULL) exit(1);
    new->name = name;
    for (int i = 0; i < TAILLE; i ++) {
        new->lst_tab[i] = NULL;
    }
    new->suiv = NULL;
    return new;
}

unsigned int functHash(char* ident) {
    int k = 613;
    int tmp = 0;
    for (int i = 0; ident[i] != '\0'; i++)
        tmp = k * tmp + ident[i];
    int result = (tmp % (int) pow(2, 30)) % TAILLE;
    if (result < 0) return -result;
    return result;
}

void deleteTableHash(Table* table) {
    printf("WIP\n");
}


int verifHash(Table* table, char* ident) {
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
    new->is_static = 0;
    new->suiv = table->lst_tab[hash];
    table->lst_tab[hash] = new;
}


void addCeption(TableCeption* table_ception, Table* table) {
    int hash = functHash(table->name);
    table->suiv = table_ception->lst_tab[hash];
    table_ception->lst_tab[hash] = table;
}


void showTable(Table* table) {
    fprintf(stdout, "========== %s ==========\n", table->name);
    Variable* var;
    for (int i = 0; i < TAILLE; i++) {
        var = table->lst_tab[i];
        for (; var != NULL; var = var->suiv) {
            fprintf(stdout, "Bucket %-2d | Type: %-4s | Id: %s\n", i, var->type, var->id);
        }
    }
}


void showCeption(TableCeption* table_ception) {
    showTable(table_ception->global_var);
    fprintf(stdout, "\n");
    showTable(table_ception->global_funct);
    fprintf(stdout, "\n=============== LocalVar ===============\n");
    for (int i = 0; i < TAILLE; i++) {
        Table* tmp = table_ception->lst_tab[i];
        for(; tmp != NULL; tmp = tmp->suiv) {
            fprintf(stdout, "\nBucket %d\n", i);
            showTable(tmp);
        }
    }
}
