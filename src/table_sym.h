#ifndef _TABLE_SYM_
#define _TABLE_SYM_

#define TAILLE 16

typedef struct variable{
    char * id; //nom de la variable 
    char * type; //type de la variable 
    struct variable * suiv; //variable suivante (utilisée dans le cas d'une collision)
} Variable;


typedef struct table {
    struct variable lst_tab[TAILLE];
} Table;


Table* initTableHash();

void deleteTableHash(Table* table);

int presenceHash(Table* table, char * ident);

int addHash(Table* table, char* ident, char* type);

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