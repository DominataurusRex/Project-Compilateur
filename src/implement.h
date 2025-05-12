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



void addBanFunct();


int verifBanDupli(char* name);


void verifBanNeed(char* name);


void writeBanFunct();


#endif
