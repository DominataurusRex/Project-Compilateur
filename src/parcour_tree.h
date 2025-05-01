#ifndef __PARCOUR_TREE_H__
#define __PARCOUR_TREE_H__

#include "table_sym.h"


typedef enum {
    PUTINT,
    GETINT,
    PUTCHAR,
    GETCHAR,
    V_END
} BanFunct;


/**
 * Parcour l'arbre lexical pour remplir
 * la table des symboles
 */
void fillTableCeption();

#endif

