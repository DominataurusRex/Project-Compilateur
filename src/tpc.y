%{
/* exp.y */
/* Syntaxe des expressions en TPC */
#include <stdio.h>
int yylex();
void yyerror(char *);
%}

%union {
    char byte;
    int num;
    char ident[64];
    char comp[3];
    char type[4];
    char key[6];
}

%token <byte> CHARACTER ADDSUB DIVSTAR
%token <num> NUM
%token <ident> IDENT
%token <type> TYPE
%token <comp> ORDER EQ
%token OR
%token AND
%token WHILE
%token IF
%token ELSE
%token RETURN
%token VOID
%token STATIC


%%
Prog:  DeclVarsExt DeclFoncts
    ;
DeclVarsExt:
       DeclVarsExt TYPE Declarateurs ';'
    |  DeclVarsExt TYPE Declarateurs '=' Exp ';'
    |
    ;
Declarateurs:
       Declarateurs ',' IDENT
    |  IDENT '=' Exp
    |  IDENT
    ;
DeclFoncts:
       DeclFoncts DeclFonct
    |  DeclFonct
    ;
DeclFonct:
       EnTeteFonct Corps
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'
    |  VOID IDENT '(' Parametres ')'
    ;
Parametres:
       VOID
    |  ListTypVar
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT
    |  TYPE IDENT
    ;
Corps: '{' DeclVarsInt SuiteInstr '}'
    ;
DeclVarsInt:
       DeclVarsInt TYPE Declarateurs ';'
    |  DeclVarsInt TYPE Declarateurs '=' Exp ';'
    |  DeclVarsInt STATIC TYPE Declarateurs ';'
    |  DeclVarsInt STATIC TYPE Declarateurs '=' Exp ';'
    |
    ;
SuiteInstr:
       SuiteInstr Instr
    |
    ;
Instr:
       IDENT '=' Exp ';'
    |  IF '(' Exp ')' Instr
    |  IF '(' Exp ')' Instr ELSE Instr
    |  WHILE '(' Exp ')' Instr
    |  IDENT '(' Arguments  ')' ';'
    |  RETURN Exp ';'
    |  RETURN ';'
    |  '{' SuiteInstr '}'
    |  ';'
    ;
Exp :  Exp OR TB
    |  TB
    ;
TB  :  TB AND FB
    |  FB
    ;
FB  :  FB EQ M
    |  M
    ;
M   :  M ORDER E
    |  E
    ;
E   :  E ADDSUB T
    |  T
    ;    
T   :  T DIVSTAR F 
    |  F
    ;
F   :  ADDSUB F
    |  '!' F
    |  '(' Exp ')'
    |  NUM
    |  CHARACTER
    |  IDENT
    |  IDENT '(' Arguments  ')'
    ;
Arguments:
       ListExp
    |
    ;
ListExp:
       ListExp ',' Exp
    |  Exp
    ;
%%

void yyerror(char* msg) {
    fprintf(stderr, "Error - %s\n", msg);
}

int main(int argc, char **argv) {
  int value = yyparse();
  printf("%d\n", value);
  return value;
}
