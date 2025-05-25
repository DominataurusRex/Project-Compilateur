#ifndef _TABLE_SYM_
#define _TABLE_SYM_

#define TAILLE 16
#define GLOBAL_VAR "GLOBAL_VAR"
#define STATIC_VAR "STATIC_VAR"

typedef enum {
    Int_v,                          // Type int
    Char_v,                         // Type char
    Void_v,                         // Type void
    Bool_v,                         // Type bool
    None_v                          // Probleme de typage
} type_v;


typedef struct idVariable {
    char* id;                       // L'identifiant de la variable
    type_v type;                    // Le type de la variable
    int is_static;                  // Si la variable est static
    int is_used;                    // Si la variable est utilisee
    int is_init;                    // Si la variable est initialisee
    int line;                       // Ligne de la declaration
    int column;                     // Colonne de la declaration
    char* adress;                   // L'adresse relative de la variable
    struct identifier* suiv;        // L'identifier suivant
} IdVariable;                       // Identifier de variable


typedef struct idFunction {
    char* id;                       // L'identifiant de la fonction
    type_v type;                    // Le type de retour de la fonction
    int is_used;                    // Si la fonction est utilisee
    int line;                       // Ligne de la declaration
    int column;                     // Colonne de la declaration
    struct table* local_var;        // La table de ses variables locales
    int nb_param;                   // Le nombre de parametre
    struct identifier* param;       // La liste chainee de ses paramtres
    int size_param;                 // Taille de la memoire dans la pile des parametres 7 et +
    int size_alloc;                 // Taille d'allocation pour les variables locales
    struct identifier* suiv;        // L'identifier suivant
} IdFunction;                       // Identifier de fonction


typedef enum {
    VARIABLE,
    FUNCTION
} IdType;


typedef union data {
    IdVariable var;                 // Identifier de variable
    IdFunction func;                // Identifier de fonction
} Data;


typedef struct identifier {
    IdType type;                    // Type de l'identifier
    Data data;                      // Donnee de l'identifier
} Identifier;


/**
 * Représente une table de hash pour les identifiants.
 */
typedef struct table {
    IdType type;
    Identifier* lst_tab[TAILLE];   // Hash des identifiants
} Table;


/**
 * Représente les tables de hash du programme.
 */
typedef struct tableCeption {
    struct table* global_var;       // Table variable global
    struct table* global_funct;     // Table fonction global
    int size_alloc_var;             // Taille de la memoire a allouer pour les variables globales
    int size_static_var;            // Taille pour les statiques
} TableCeption;


/**
 * Initialise une structure ̀`Identifier`.
 * @param ident L'id de l'identifiant
 * @param type Le type de l'identifiant
 * @param adress L'adresse de l'identifiant
 * @return L'adresse de la structure
 */
Identifier* initVariable(char* ident, char* type, char* adress);


/**
 * Initialise la structure.
 * @return L'adresse de la structure
 */
TableCeption* initTableCeption();


/**
 * Permet de liberer la memoire allouee pour `table`.
 * @param table La table des symboles
 */
void deleteTable(Table* table);


/**
 * Permet de liberer la memoire allouee pour `table_ception`.
 * @param table_ception La structure `TableCeption`
 */
void deleteTableCeption(TableCeption* table_ception);


/**
 * Rajoute une variable dans `table_var`.
 * @param table_var La table des symboles  de variable
 * @param ident L'id de la variable
 * @param type Le type de la variable
 * @param adress L'adresse de la variable
 * @param is_static Si la variable est static
 * @param line La ligne de la declaration
 * @param column La colnne de la declaration
 * @return L'adresse de la nouvelle variable
 */
Identifier* addHashVar(Table* table_var, char* ident, char* type, char* adress, int is_static, int line, int column);


/**
 * Rajoute une fonction dans `table_funct`.
 * @param table_funct La table des symboles de fonction
 * @param ident L'id de la fonction
 * @param type Le type de la fonction
 * @param line La ligne de la declaration
 * @param column La colonne de la declaration
 * @return L'adresse de la nouvelle fonction
 */
Identifier* addHashFunct(Table* table_funct, char* ident, char* type, int line, int column);


/**
 * Renvoie l'adresse de l'identifier correspondant a `ident` dans la table
 * @param table La table dans laquelle chercher
 * @param ident L'id de l'identifier
 * @return L'adresse si il existe sinon `NULL`
 */
Identifier* verifHashTable(Table* table, char* ident);


/**
 * Renvoie l'adresse de l'identifier correspondant a `ident` dans les parametres de la fonction
 * @param funct La fonction dans laquelle chercher
 * @param ident L'id de l'identifier
 * @return L'adresse si il existe sinon `NULL`
 */
Identifier* verifHashParam(Identifier* funct, char* ident);


/**
 * Renvoie l'adresse de l'identifier correspondant a `ident` dans les variables globales et dans la fonction
 * @param global_var La table des variables globales
 * @param funct La fonction dans laquelle chercher
 * @param ident L'id de l'identifier
 * @return L'adresse si il existe sinon `NULL`
 */
Identifier* verifHashFunct(Table* global_var, Identifier* funct, char* ident);


/**
 * Permet d'afficher dans la sortie standard le contenu de `table_ception`.
 * @param table_ception La structure `TableCeptin`
 */
void showCeption(TableCeption* table_ception);


void genWarningNotUse(TableCeption* table_ception);

#endif