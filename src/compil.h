#ifndef __COMPIL_H__
#define __COMPIL_H__

#include "table_sym.h"

#define INT_BUFF "INT_BUFF"     // Nom pour le buffer de put/getint
#define CHAR_BUFF "CHAR_BUFF"   // Nom pour le buffer de put/getchar


typedef struct precalc {
    int abort;
    int val;
} Precalc;


void evalTpc();

#endif
