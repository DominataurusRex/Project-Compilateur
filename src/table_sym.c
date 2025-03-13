#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "table_sym.h"
#include "tree.h"


Variable* initVariable(char* ident, char* type) {
    Variable* new = (Variable*) malloc(sizeof(Variable));
    if (new == NULL) exit(1);
    new->id = ident;
    new->type = type;
    new->is_static = 0;
    new->suiv = NULL;
    new->local_var = NULL;
    return new;
}


Table* initTableHash() {
    Table* new = (Table*) malloc(sizeof(Table));
    if (new == NULL) exit(1);
    for (int i = 0; i < TAILLE; i ++) {
        new->lst_tab[i] = NULL;
    }
    return new;
}


TableCeption* initTableCeption() {
    TableCeption* new = (TableCeption*) malloc(sizeof(TableCeption));
    if (new == NULL) exit(1);
    new->global_var = initTableHash();
    new->global_funct = initTableHash();
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


int verifHash(Table* table, char* ident) {
    Variable* var = table->lst_tab[functHash(ident)];
    for (; var != NULL; var = var->suiv) {
        if (!strcmp(ident, var->id)) {
            return 1;
        }
    }
    return 0;
}


void addHashVar(Table* table_var, char* ident, char* type) {
    int hash = functHash(ident);
    Variable* new = initVariable(ident, type);
    new->suiv = table_var->lst_tab[hash];
    table_var->lst_tab[hash] = new;
    
}


Table* addHashFunct(Table* table_funct, char* ident, char* type) {
    int hash = functHash(ident);
    Variable* new = initVariable(ident, type);
    new->suiv = table_funct->lst_tab[hash];
    table_funct->lst_tab[hash] = new;
    new->local_var = initTableHash();
    return new->local_var;
}


void deleteTable(Table* table) {
    for (int i = 0; i < TAILLE; i++) {
        deleteVar(table->lst_tab[i]);
    }
    free(table);
    table = NULL;
}


void deleteVar(Variable* var) {
    if (var == NULL) return;
    if (var->local_var != NULL) deleteTable(var->local_var);
    deleteVar(var->suiv);
    free(var);
    var = NULL;
}


void deleteTableCeption(TableCeption* table_ception) {
    deleteTable(table_ception->global_funct);
    deleteTable(table_ception->global_var);
    free(table_ception);
    table_ception = NULL;
}


void showTableVar(Table* table, int indent) {
    fprintf(stdout, "\033[32:1m");
    for (int j = 0; j < indent; j++) {
        fprintf(stdout, "--------");
    }
    fprintf(stdout, "==============================\n");
    Variable* var;
    for (int i = 0; i < TAILLE; i++) {
        var = table->lst_tab[i];
        for (; var != NULL; var = var->suiv) {
            for (int j = 0; j < indent; j++) {
                fprintf(stdout, "\t");
            }
            fprintf(stdout, "Bucket %-2d | Type: %-4s | Static: %d | Id: %s\n", i, var->type, var->is_static, var->id);
        }
    }
    fprintf(stdout, "\033[0m\n");
}


void showTableFunct(Table* table) {
    fprintf(stdout, "\033[33:1m");
    fprintf(stdout, "==============================\n");
    Variable* var;
    for (int i = 0; i < TAILLE; i++) {
        var = table->lst_tab[i];
        for (; var != NULL; var = var->suiv) {
            fprintf(stdout, "\033[33:1m");
            fprintf(stdout, "Bucket %-2d | Type: %-4s | Id: %s\n", i, var->type, var->id);
            showTableVar(var->local_var, 1);
            fprintf(stdout, "\033[0m");
        }
    }
}


void showCeption(TableCeption* table_ception) {
    showTableVar(table_ception->global_var, 0);
    showTableFunct(table_ception->global_funct);
}
