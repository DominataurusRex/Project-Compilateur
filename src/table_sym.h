#ifndef _TABLE_SYM_
#define _TABLE_SYM_

#define TAILLE 16


typedef struct idVariable {
    char* id;
    char* type;
    int is_static;
    int is_used;
    char* adress;
    struct identifier* suiv;
} IdVariable;


typedef struct idFunction {
    char* id;
    char* type;
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
    struct table* global_var;        // Table variable global
    struct table* global_funct;      // Table fonction global
} TableCeption;


/**
 * Initialise une structure ̀`Identifier`.
 * @param ident L'id de l'identifiant
 * @param type Le type de l'identifiant
 * @param adress L'adresse de l'identifiant
 * @return L'adresse de la structure
 */
Identifier* initVariable(char* ident, char* type, char* adress);

Identifier* initFunction(char* ident, char* type);

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
 * @param is_static Si la variable est static (0/1)
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
 * Renvoie l'adresse de l'identifiant correspondant a `ident`
 * @param table Latable dans laquelle chercher
 * @param ident L'id de l'identifiant
 * @return L'adresse si il existe sinon `NULL`
 */
Identifier* getHashVar(Table* table, char* ident);



/**
 * Verifie la presence de l'id `ident` dans `table`.
 * @param table La table des symboles
 * @param ident L'id a rechercher
 * @return Renvoie la structure `identifier` si presente, NULL sinon
 */
Identifier* verifHash(Table* table, char* ident);


/**
 * Permet d'afficher dans la sortie standard le contenu de `table_ception`.
 * @param table_ception La structure `TableCeptin`
 */
void showCeption(TableCeption* table_ception);

#endif