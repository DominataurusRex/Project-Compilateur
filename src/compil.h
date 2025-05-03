#ifndef __COMPIL_H__
#define __COMPIL_H__

#include "table_sym.h"

#define INT_BUFF "INT_BUFF"     // Nom pour le buffer de put/getint
#define CHAR_BUFF "CHAR_BUFF"   // Nom pour le buffer de put/getchar
#define GLOBAL_VAR "GLOBAL_VAR" // Nom pour le stockage des variables globales


/**
 * Structure permettant de gerer le pre-calcul des expressions
 */
typedef struct precalc {
    int abort;      //info si on ne peut pas calculer la valeur. 
    int val;        //valeur du calcul
} Precalc;


/**
 * Evalue les fonctions et leurs instructions.
 * Ecrit l'assembleur tant qu'il n'y a pas d'erreur.
 * Supprime l'assembleur si c'est la cas
 */
void evalTpc();

#endif
