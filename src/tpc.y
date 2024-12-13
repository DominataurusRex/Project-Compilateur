%{
/* exp.y */
/* Syntaxe des expressions en TPC */
#include <stdio.h>
#include <string.h>
#include "tree.h"
int yylex();
void yyerror(char *);
%}

%union {
    Node *node;
    char byte;
    int num;
    char ident[64];
}
%type <node> Prog DeclVarsExt Declarateurs DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar
%type <node> Corps DeclVarsInt SuiteInstr Instr Exp TB FB M E T F Arguments ListExp
%token <byte> CHARACTER ADDSUB DIVSTAR
%token <num> NUM
%token <ident> IDENT TYPE ORDER EQ
%token OR AND WHILE IF ELSE RETURN VOID STATIC
%precedence NOELSE


%%
Prog:  DeclVarsExt DeclFoncts                       {$$ = makeNode(Prog);
                                                     addChild($$, $1);
                                                     addChild($$, $2);
                                                     printTree($$);
                                                     deleteTree($$);}
    ;

DeclVarsExt:
       DeclVarsExt TYPE Declarateurs ';'            {$$ = $1;
                                                     Node* type = makeNode(Type);
                                                     type->ident = strdup($2);
                                                     addChild($$, type);
                                                     addChild(type, $3);}
                                                     
    |                                               {$$ = makeNode(DeclVars);}
    ;

Declarateurs:
       Declarateurs ',' IDENT                       {$$ = $1;
                                                     Node* ident = makeNode(Ident);
                                                     ident->ident = strdup($3);
                                                     addSibling($$, ident);}
    |  IDENT                                        {$$ = makeNode(Ident);
                                                     $$->ident = strdup($1);}
    ;

DeclFoncts:
       DeclFoncts DeclFonct                         {$$ = $1;
                                                     /* addSibling($$, $2); */}
    |  DeclFonct                                    {$$ = makeNode(DeclFonct);}
    ;
DeclFonct:
       EnTeteFonct Corps                            // {addChild($$, $1);
                                                    //  addChild($$, $2);}
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'                {}
    |  VOID IDENT '(' Parametres ')'                {}
    ;
Parametres:
       VOID
    |  ListTypVar
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT
    |  TYPE IDENT
    ;
Corps: '{' DeclVarsInt SuiteInstr '}'               {}
    ;
DeclVarsInt:
       DeclVarsInt TYPE Declarateurs ';'
    |  DeclVarsInt STATIC TYPE Declarateurs ';'
    |
    ;
SuiteInstr:
       SuiteInstr Instr
    |
    ;
Instr:
       IDENT '=' Exp ';'
    |  IF '(' Exp ')' Instr     %prec NOELSE
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
  return value;
}
