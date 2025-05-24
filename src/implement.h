#ifndef __IMPLEMENT_H__
#define __IMPLEMENT_H__

#include "table_sym.h"

#define INT_BUFF "INT_BUFF"     // Nom pour le buffer de put/getint
#define CHAR_BUFF "CHAR_BUFF"   // Nom pour le buffer de put/getchar

typedef enum {
    PUTINT,         // 1
    GETINT,         // 2
    PUTCHAR,        // 4
    GETCHAR,        // 8
    V_END
} BanFunct;


/**
 * Rajoute les fonctions implementees d'origine
 */
void addBanFunct();


/**
 * Verifie si le nom fait parti des fonctions implementees
 */
int verifBanDupli(char* name);


/**
 * Rajoute la fonction deja implementees dans les fonctions a ecrire
 */
void verifBanNeed(char* name);


/**
 * Ecrit les fonctions implementees necessaire au programme
 */
void writeBanFunct();


#endif
