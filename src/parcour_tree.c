#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parcour_tree.h"
#include "error.h"
#include "implement.h"

TableCeption* table_ception;            // Les tables des symboles
extern Node* root;                      // La racine de l'arbre syntaxique
extern int nb_error;                    // Le nombre d'erreur
extern const char *ban_funct[];         // Le nom des fonctions implementees
int main_flag;                          // Presence du main dans le fichier



/**
 * Rempli `table` avec les declarations de variable locale dans une fonction ou globale dans le programme
 * @param table La table des symboles a remplir
 * @param node La racine contenant la declaration des variables
 * @param lst_param La liste des parametres dans le cas d'une fonction, NULL si dans le programme
 * @param nb_param Le nombre de parametres dans le cas d'une fonction, -1 si dans le programme
 * @return La memoire a allouer pour stocker les variables
 */
static int fillTableVariable(Table* table, Node* node, Identifier* lst_param, int nb_param) {
    Node* start = node->firstChild;
    int is_new;
    int is_not_ban;
    int toto_mem = 0;
    char buff[20];
    for (; start != NULL; start = start->nextSibling) {
        // Cherche le noeud DeclVars
        if (start->label == DeclVars) {
            start = start->firstChild;
            // Parcour chaque Declvars
            for (; start != NULL; start = start->nextSibling) {
                Node* cursor = start->firstChild;
                is_new = 1;
                is_not_ban = 1;
                // Parcour chaque Ident dans start
                for (; cursor != NULL; cursor = cursor->nextSibling) {
                    // Verification duplication programme
                    if (verifHashTable(table, cursor->ident)) {
                        is_new = 0;
                    } else {
                        for (int i = 0; i < nb_param; i++) {
                            if (!strcmp(cursor->ident, lst_param[i].data.var.id)) {
                                is_new = 0;
                            }
                        }
                    }
                    if (!is_new) errorRedefinition(cursor);

                    // Verification redefinition fonction ban
                    if (nb_param == -1) is_not_ban = !verifBanDupli(cursor->ident);
                    if (!is_not_ban) errorRedefinitionBan(cursor);
                    if (is_new && is_not_ban) {
                        if (nb_param == -1) {
                            sprintf(buff, "[%s+%d]", GLOBAL_VAR, toto_mem);
                            addHashVar(table, cursor->ident, start->ident, buff, 0, cursor->line, cursor->column);
                            toto_mem += !strcmp(start->ident, "int")? 4: 1;
                        } else {
                            if (start->label == StaticType){ //je respecte le travail de Paul
                                sprintf(buff, "[%s+%d]", STATIC_VAR, table_ception->size_static_var);
                                Identifier* tmp = addHashVar(table, cursor->ident, start->ident, buff, 1, cursor->line, cursor->column);
                                tmp->data.var.is_init = 1;
                                table_ception->size_static_var += !strcmp(start->ident, "int")? 4: 1;
                            } else {
                                toto_mem += !strcmp(start->ident, "int")? 4: 1;
                                sprintf(buff, "[rbp-%d]", toto_mem);
                                addHashVar(table, cursor->ident, start->ident, buff, 0, cursor->line, cursor->column);
                            }
                        }
                    }
                }
            }
            return toto_mem;
        }
    }
    return 0;
}


/**
 * Permet de recuperer le bon registre pour stocker le `param_val`eme parametre
 * @param adress Le registre dans lequel le stocker, si `param_val` > 6, renvoie `-`
 * @param param_val Le numero du parametre
 * @param param_type Le type du parametre `int`/`char`
 */
static void getParamAdress(char adress[8], int param_val, char* param_type) {
    switch (param_val)
    {
        case 1: strncpy(adress, !strcmp(param_type, "int")? "edi": "dil", 7); break;   // rdi
        case 2: strncpy(adress, !strcmp(param_type, "int")? "esi": "sil", 7); break;   // rsi
        case 3: strncpy(adress, !strcmp(param_type, "int")? "edx": "dl", 7); break;    // rdx
        case 4: strncpy(adress, !strcmp(param_type, "int")? "ecx": "cl", 7); break;    // rcx
        case 5: strncpy(adress, !strcmp(param_type, "int")? "r8d": "r8b", 7); break;   // r8
        case 6: strncpy(adress, !strcmp(param_type, "int")? "r9d": "r9b", 7); break;   // r9
    
    default:
        sprintf(adress, "-");
    }
}


/**
 * Parcour les parametres de la fonction `funct`
 * @param funct L'identifier de la fonction
 * @param node La racine des parametres
 */
static void parcourParamFunct(Identifier* funct, Node* node) {
    if (node->firstChild->label == Void) {
        funct->data.func.nb_param = 0;
        return;
    }
    int nb_param = 0;
    int size_pile = 0;      // Taille de la pile si parametre dans la pile
    char adress[8];

    Node* cursor = node;
    for (; cursor; cursor = cursor->nextSibling) {
        // Compte le nombre de parametre
        nb_param++;
    }

    funct->data.func.param = (Identifier*) malloc(sizeof(Identifier) * nb_param);
    if (!funct->data.func.param) exit(4);
    cursor = node;
    for (int i = 0; i < nb_param; i++) {
        // Place les parametres dans la liste
        getParamAdress(adress, nb_param - i, cursor->firstChild->ident);
        Identifier* var_temp = initVariable(cursor->firstChild->nextSibling->ident, cursor->firstChild->ident, adress);
        funct->data.func.param[i] = *var_temp;
        funct->data.func.param[i].data.var.is_init = 1;
        free(var_temp);
        cursor = cursor->nextSibling;
    }
    for (int j = nb_param - 7; j >= 0; j--) {
        // Place l'adresse des parametres se trouvant dans la pile
        sprintf(adress, "[rbp+%d]", 16 + size_pile); // 16bytes d'en-tete
        funct->data.func.param[j].data.var.adress = (char*) malloc(sizeof(char) * strlen(adress));
        if (!funct->data.func.param[j].data.var.adress) exit(4);
        strcpy(funct->data.func.param[j].data.var.adress, adress);
        size_pile += funct->data.func.param[j].data.var.type == Char_v? 1: 4;
    }
    funct->data.func.size_param = size_pile;
    funct->data.func.nb_param = nb_param;
    return;
}


/**
 * Initialise un `identifier` FUNCTION avec le noeud EnTeteFonct
 * @param head La racine EnTeteFonct
 * @return L'adresse de `identifier` cree
 */
static Identifier* fillEnTeteFunct(Node* head) {
    Identifier* new = NULL;
    Node* name = head->firstChild->firstChild->nextSibling;
    if (verifHashTable(table_ception->global_var, name->ident)) {
        // Present dans global_var
        errorRedefinitionType(name);
    } else if (verifHashTable(table_ception->global_funct, name->ident)) {
        // Present dans global_funct
        errorRedefinition(name);
    } else {
        new = addHashFunct(
            table_ception->global_funct,
            name->ident,
            head->firstChild->firstChild->label == Void? "void": head->firstChild->firstChild->ident,
            name->line,
            name->column
        );
        if (verifBanDupli(name->ident)) errorRedefinitionBan(name);
        // Verification signature int main(...)
        if (!strcmp(name->ident, "main")) {
            if (head->firstChild->firstChild->nextSibling->nextSibling->firstChild->label != Void) warningMain();
            if (head->firstChild->firstChild->label != Void && !strcmp(head->firstChild->firstChild->ident, "int")) main_flag = 1;
            new->data.func.is_used = 1;
        }
        parcourParamFunct(new, name->nextSibling);
    }
    return new;
}


/**
 * Parcour toute les declarations de fonction dans le fichier d'entre
 */
static void parcourFunction() {
    Node* start = root->firstChild;
    for (; start != NULL; start = start->nextSibling) {
        if (start->label == DeclFonct) {
            Identifier* new = fillEnTeteFunct(start);
            if (new) new->data.func.size_alloc = fillTableVariable(new->data.func.local_var, start, new->data.func.param, new->data.func.nb_param);
        }
    }
}



void fillTableCeption() {
    main_flag = 0;
    table_ception = initTableCeption();
    table_ception->size_alloc_var = fillTableVariable(table_ception->global_var, root, NULL, -1);
    addBanFunct();          // Erreur 139: 14 18
    parcourFunction();
    if (!main_flag) errorNotMain();
}
