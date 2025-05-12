#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "table_sym.h"
#include "tree.h"


char* convertTypeVChar(type_v type) {
    switch (type)
    {
    case Int_v: return "int";
    case Char_v: return "char";
    case Void_v: return "void";
    default: return "none";
    }
}


type_v convertCharTypeV(char* type) {
    if (!strcmp(type, "int")) return Int_v;
    if (!strcmp(type, "char")) return Char_v;
    if (!strcmp(type, "void")) return Void_v;
    return None_v;
}


Identifier* initVariable(char* ident, char* type, char* adress) {
    Identifier* new = (Identifier*) malloc(sizeof(Identifier));
    if (!new) exit(4);
    new->type = VARIABLE;
    new->data.var.id = ident;
    new->data.var.type = convertCharTypeV(type);
    new->data.var.is_static = 0;
    new->data.var.is_used = 0;
    new->data.var.is_init = 0;
    if (strcmp(adress, "-")) {
        new->data.var.adress = strdup(adress);
        if (!new->data.var.adress) exit(4);
    } else {
        new->data.var.adress = NULL;
    }
    new->data.var.suiv = NULL;
    return new;
}


Identifier* initFunction(char* ident, char* type) {
    Identifier* new = (Identifier*) malloc(sizeof(Identifier));
    if (!new) exit(4);
    new->type = FUNCTION;
    new->data.func.id = ident;
    new->data.func.type = convertCharTypeV(type);
    new->data.func.is_used = 0;
    new->data.func.local_var = NULL;
    new->data.func.nb_param = 0;
    new->data.func.param = NULL;
    new->data.func.size_param = 0;
    new->data.func.size_alloc = 0;
    new->data.func.suiv = NULL;
    return new;
}


/**
 * Peremt de libere la memoire allouee pour `var`.
 * @param var L'identifiant
 */
void delIdentifier(Identifier* var) {
    if (var == NULL) return;
    switch (var->type) {
        case FUNCTION:
            if (var->data.func.local_var != NULL) deleteTable(var->data.func.local_var);
            free(var->data.func.param);
            var->data.func.param = NULL;
            delIdentifier(var->data.func.suiv);
            break;
        case VARIABLE:
            delIdentifier(var->data.var.suiv);
            free(var->data.var.adress);
            var->data.var.adress = NULL;
    }
    free(var);
    var = NULL;
}


/**
 * Initialise une structure `Table`.
 * @return L'adresse de la structure
 */
Table* initTableHash(IdType type) {
    Table* new = (Table*) malloc(sizeof(Table));
    if (!new) exit(4);
    new->type = type;
    for (int i = 0; i < TAILLE; i ++) {
        new->lst_tab[i] = NULL;
    }
    return new;
}


/**
 * Fonction pour calculer le hash de la chaine de caractere `ident`.
 * @param ident L'id a hash
 * @return La valeur du hash
 */
unsigned int functHash(char* ident) {
    int k = 613;
    int tmp = 0;
    for (int i = 0; ident[i] != '\0'; i++)
        tmp = k * tmp + ident[i];
    int result = (tmp % (int) pow(2, 30)) % TAILLE;
    if (result < 0) return -result;
    return result;
}


void showParam(Identifier* funct, int indent) {
    fprintf(stdout, "\033[35m");
    for (int j = 0; j < indent; j++) {
        fprintf(stdout, "--------");
    }
    fprintf(stdout, "==============================\n");
    for (int i = 0; i < funct->data.func.nb_param; i++) {
        for (int j = 0; j < indent; j++) fprintf(stdout, "\t");
        fprintf(
            stdout, "Param %-3d | Adress: %-15s | Type: %-4s | Id %s\n",
            i,
            funct->data.func.param[i].data.var.adress,
            convertTypeVChar(funct->data.func.param[i].data.var.type),
            funct->data.func.param[i].data.var.id
        );
    }
}


/**
 * Permet un affichage de la table des symboles des variables sur la sortie standard.
 * @param table La table a afficher
 * @param indent Le nombre d'indentation pour l'affichage
 */
void showTable(Table* table, int indent) {
    fprintf(stdout, "\033[3%dm", table->type == VARIABLE ? 2: 3);
    for (int j = 0; j < indent; j++) {
        fprintf(stdout, "--------");
    }
    fprintf(stdout, "==============================\n");
    Identifier* var;
    for (int i = 0; i < TAILLE; i++) {
        var = table->lst_tab[i];
        switch (table->type)
        {
        case VARIABLE:
            for (; var != NULL; var = var->data.var.suiv) {
                for (int j = 0; j < indent; j++) fprintf(stdout, "\t");
                fprintf(
                    stdout, "Bucket %-2d | Adress: %-15s | Type: %-4s | Static: %d | Id: %s\n",
                    i,
                    var->data.var.adress,
                    convertTypeVChar(var->data.var.type),
                    var->data.var.is_static,
                    var->data.var.id
                );
            }
            break;
        case FUNCTION:
            for (; var != NULL; var = var->data.func.suiv) {
                fprintf(stdout, "\033[33m");
                fprintf(
                    stdout, "Bucket %-2d | Type: %-4s | Nb_param: %-2d | Size_param: %-2d | Size_alloc: %-2d | Id: %s\n",
                    i,
                    convertTypeVChar(var->data.func.type),
                    var->data.func.nb_param,
                    var->data.func.size_param,
                    var->data.func.size_alloc,
                    var->data.func.id
                );
                showParam(var, indent + 1);
                showTable(var->data.func.local_var, indent + 1);
                fprintf(stdout, "\n");
            }
        }
    }
    fprintf(stdout, "\033[0m");
}


TableCeption* initTableCeption() {
    TableCeption* new = (TableCeption*) malloc(sizeof(TableCeption));
    if (!new) exit(4);
    new->global_var = initTableHash(VARIABLE);
    new->global_funct = initTableHash(FUNCTION);
    new->size_alloc_var = 0;
    return new;
}


void deleteTable(Table* table) {
    for (int i = 0; i < TAILLE; i++) {
        delIdentifier(table->lst_tab[i]);
    }
    free(table);
    table = NULL;
}


void deleteTableCeption(TableCeption* table_ception) {
    deleteTable(table_ception->global_funct);
    deleteTable(table_ception->global_var);
    free(table_ception);
    table_ception = NULL;
}


void addHashVar(Table* table_var, char* ident, char* type, char* adress, int is_static) {
    int hash = functHash(ident);
    Identifier* new = initVariable(ident, type, adress);
    new->data.var.is_static = is_static;
    new->data.var.suiv = table_var->lst_tab[hash];
    table_var->lst_tab[hash] = new;
}


Identifier* addHashFunct(Table* table_funct, char* ident, char* type) {
    int hash = functHash(ident);
    Identifier* new = initFunction(ident, type);
    new->data.func.suiv = table_funct->lst_tab[hash];
    table_funct->lst_tab[hash] = new;
    new->data.func.local_var = initTableHash(VARIABLE);
    return new;
}


Identifier* verifHashTable(Table* table, char* ident) {
    Identifier* var = table->lst_tab[functHash(ident)];
    switch (table->type) {
        case VARIABLE:
            for (; var != NULL; var = var->data.var.suiv) {
                if (!strcmp(ident, var->data.var.id)) {
                    return var;
                }
            }
            return NULL;
        case FUNCTION:
            for (; var != NULL; var = var->data.func.suiv) {
                if (!strcmp(ident, var->data.func.id)) {
                    return var;
                }
            }
    }
    return NULL;
}


Identifier* verifHashParam(Identifier* funct, char* ident) {
    for (int i = 0; i < funct->data.func.nb_param; i++) {
        if (!strcmp(funct->data.func.param[i].data.var.id, ident)) return &funct->data.func.param[i];
    }
    return NULL;
}


Identifier* verifHashFunct(Table* global_var, Identifier* funct, char* ident) {
    Identifier* var = verifHashTable(funct->data.func.local_var, ident);
    if (!var) var = verifHashParam(funct, ident);
    if (!var) var = verifHashTable(global_var, ident);
    return var;
}


void showCeption(TableCeption* table_ception) {
    showTable(table_ception->global_var, 0);
    fprintf(stdout, "\n");
    showTable(table_ception->global_funct, 0);
}
