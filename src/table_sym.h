#ifndef _TABLE_SYM_
#define _TABLE_SYM_

#define TAILLE 16
#define GLOBAL_VAR "GLOBAL_VAR"


typedef enum {
    Int_v,          // Type int
    Char_v,         // Type char
    Void_v,         // Type void
    None_v          // Probleme de typage
} type_v;


typedef struct idVariable {
    char* id;
    type_v type;
    int is_static;
    int is_used;
    int is_init;
    char* adress;
    struct identifier* suiv;
} IdVariable;


typedef struct idFunction {
    char* id;
    type_v type;
    int is_used;
    struct table* local_var;
    int nb_param;
    struct identifier* param;
    int size_alloc;
    struct identifier* suiv;
} IdFunction;


typedef enum {
    VARIABLE,
    FUNCTION
} IdType;


typedef union data {
    IdVariable var;
    IdFunction func;
} Data;


typedef struct identifier {
    IdType type;
    Data data;
} Identifier;


/**
 * Représente un identifiant de fonction ou de variable.
 
typedef struct temp{
    char * id;                  // Nom de l'identifiant 
    char * type;                // Type de l'identifiant 
    int is_used;                // Si l'identifiant est utilise
    int is_static;              // -> Variable: si elle est static ou non
    char * adress;              // -> Variable: Adresse relative
    struct temp * suiv;   // L'identifiant suivante (utilisée dans le cas d'une collision)
    struct table* local_var;    // -> Fonction: Hash des variables locales
    struct temp ** param; // -> Fonction: Liste des parametres de la fonction
    int size_alloc;             // -> Fonction: La taille du bloc a allouer pour les locals
} Temp;
*/

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
    int size_alloc_var;             // Taille de la memoire a allouer pour les variable global
} TableCeption;


char* convertTypeV(type_v type);


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
 * @param info Si la variable est static (0/1)
 */
void addHashVar(Table* table_var, char* ident, char* type, char* adress, int is_static);


/**
 * Rajoute une fonction dans `table_funct`.
 * @param table_funct La table des symboles de fonction
 * @param ident L'id de la fonction
 * @param type Le type de la fonction
 */
Identifier* addHashFunct(Table* table_funct, char* ident, char* type);


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

#endif