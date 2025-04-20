#ifndef __COMPIL_H__
#define __COMPIL_H__

#include "table_sym.h"

#define INT_BUFF "INT_BUFF"     // Nom pour le buffer de put/getint
#define CHAR_BUFF "CHAR_BUFF"   // Nom pour le buffer de put/getchar


typedef enum {
    Int_v,          // Type int
    Char_v,         // Type char
    None_v          // Probleme de typage
} type_v;


void evalTpc();

#endif
