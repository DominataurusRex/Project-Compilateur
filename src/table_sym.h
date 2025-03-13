#ifndef _TABLE_SYM_
#define _TABLE_SYM_

#define TAILLE 16


/**
 * Représente une variable
 */
typedef struct variable{
    char * id;                  // Nom de la variable 
    char * type;                // Type de la variable 
    int is_static;              // Si variable static
    struct variable * suiv;     // Variable suivante (utilisée dans le cas d'une collision)
    struct table* local_var;    // Hash des variables locales
} Variable;


/**
 * Représente une table de hash pour des variables
 */
typedef struct table {
    struct variable* lst_tab[TAILLE];   // Hash des variable
} Table;


/**
 * Représente les tables de hash du programme
 */
typedef struct tableCeption {
    struct table* global_var;        // Table variable global
    struct table* global_funct;      // Table fonction global
} TableCeption;


TableCeption* initTableCeption();

void addHashVar(Table* table_var, char* ident, char* type);

Table* addHashFunct(Table* table_funct, char* ident, char* type);

int verifHash(Table* table, char* ident);

void deleteVar(Variable* var);

void deleteTableCeption(TableCeption* table_ception);

void showCeption(TableCeption* table_ception);




void showTable(Table* table);


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