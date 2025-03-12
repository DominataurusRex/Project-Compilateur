#ifndef _TABLE_SYM_
#define _TABLE_SYM_

#define TAILLE 16


/**
 * Représente une variable
 */
typedef struct variable{
    char * id; //nom de la variable 
    char * type; //type de la variable 
    struct variable * suiv; //variable suivante (utilisée dans le cas d'une collision)
} Variable;


/**
 * Représente une table de hash pour des variables
 */
typedef struct table {
    char* type;
    struct variable* lst_tab[TAILLE];
} Table;



Table* initTableHash(char* type);

void deleteTableHash(Table* table);

void addHash(Table* table, char* ident, char* type);

int verifHash(Table* table, char* ident, char* type);

void showHash(Table* table);

/*
typedef struct {
    Variable var;
    int param; //vaut 1 si la varaible est un paramètre de fonction
    void * adr; //adresse de la variable
} Hash_var;

typedef struct {
    char * id; //nom de la fonction
    char * type; //type de retour de la fonction
    Variable * param; //liste de Variable représentant les paramètres de la fonction
    void * adr; //adresse de la fonction
} Hash_fct;

*/
#endif