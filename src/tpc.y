%{
/* exp.y */
/* Syntaxe des expressions en TPC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
int yylex();
void yyerror(char *);
Node* root = NULL;
extern char *yytext;
extern char* file_name;
extern int nb_error;
Node* tree;
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
%locations
%precedence IF
%precedence ELSE

%%

Prog:  DeclVarsExt DeclFoncts                       {
                                                    $$ = makeNode(Prog);
                                                    addChild($$, $1);
                                                    addChild($$, $2);
                                                    root = $$;
}
    ;

DeclVarsExt:
       DeclVarsExt TYPE Declarateurs ';'            {
                                                    $$ = $1;
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup($2);
                                                    addChild($$, type);
                                                    addChild(type, $3);
}
                                                     
    |                                               {$$ = makeNode(DeclVars);}
    ;

Declarateurs:
       Declarateurs ',' IDENT                       {
                                                    $$ = $1;
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup($3);
                                                    ident->line = @3.first_line;
                                                    ident->column = @3.first_column;
                                                    addSibling($$, ident);
}
    |  IDENT                                        {
                                                    $$ = makeNode(Ident);
                                                    $$->ident = strdup($1);
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
}
    ;

DeclFoncts:
       DeclFoncts DeclFonct                         {
                                                    $$ = $1;
                                                    addSibling($$, $2);
}
    |  DeclFonct                                    {$$ = $1;}
    ;
DeclFonct:
       EnTeteFonct Corps                            {
                                                    $$ = makeNode(DeclFonct);
                                                    addChild($$, $1);
                                                    addChild($$, $2);
}
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'                {
                                                    $$ = makeNode(EnTeteFonct);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup($1);
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup($2);
                                                    ident->line = @2.first_line;
                                                    ident->column = @2.first_column;
                                                    addChild($$, type);
                                                    addChild($$, ident);
                                                    addChild($$, $4);
}
    |  VOID IDENT '(' Parametres ')'                {
                                                    $$ = makeNode(EnTeteFonct);
                                                    Node* type = makeNode(Void);
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup($2);
                                                    ident->line = @2.first_line;
                                                    ident->column = @2.first_column;
                                                    addChild($$, type);
                                                    addChild($$, ident);
                                                    addChild($$, $4);
}
    ;
Parametres:
       VOID                                         {
                                                    $$ = makeNode(Var);
                                                    Node* vide = makeNode(Void);
                                                    addChild($$, vide);
}        
    |  ListTypVar                                   {$$ = $1;}
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT                    {
                                                    $$ = makeNode(Var);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup($3);
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup($4);
                                                    ident->line = @4.first_line;
                                                    ident->column = @4.first_column;
                                                    addChild($$, type);
                                                    addChild($$, ident);
                                                    addSibling($$, $1);
}
    |  TYPE IDENT                                   {
                                                    $$ = makeNode(Var);
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup($1);
                                                    Node* ident = makeNode(Ident);
                                                    ident->ident = strdup($2);
                                                    ident->line = @2.first_line;
                                                    ident->column = @2.first_column;
                                                    addChild($$, type);
                                                    addChild($$, ident);
}
    ;
Corps: '{' DeclVarsInt SuiteInstr '}'               {
                                                    $$ = $2;
                                                    Node* instr = makeNode(Instr);
                                                    addSibling($$, instr);
                                                    addChild(instr, $3);
}
    ;
DeclVarsInt:
       DeclVarsInt TYPE Declarateurs ';'            {
                                                    $$ = $1;
                                                    Node* type = makeNode(Type);
                                                    type->ident = strdup($2);
                                                    addChild($$, type);
                                                    addChild(type, $3);
}
    |  DeclVarsInt STATIC TYPE Declarateurs ';'     {
                                                    $$ = $1;
                                                    Node* type = makeNode(StaticType);
                                                    type->ident = strdup($3);
                                                    addChild($$, type);
                                                    addChild(type, $4);
}
    |                                               {$$ = makeNode(DeclVars);}
    ;
SuiteInstr:
       SuiteInstr Instr                             {
                                                    if ($1 != NULL) {
                                                        $$ = $1;
                                                        addSibling($$, $2);
                                                    } else {
                                                        $$ = $2;
                                                    }
}
    |                                               {$$ = NULL;}
    ;
Instr:
       IDENT '=' Exp ';'                            {
                                                    $$ = makeNode(Affect);
                                                    $$->ident = strdup($1);
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
                                                    addChild($$, $3);
}
    |  IF '(' Exp ')' Instr     %prec IF            {
                                                    $$ = makeNode(If);
                                                    Node* cond = makeNode(Cond);
                                                    addChild(cond, $3);
                                                    addChild($$, cond);
                                                    if ($5 != NULL) {
                                                        Node* doo = makeNode(Do);
                                                        addChild(doo, $5);
                                                        addChild($$, doo);
                                                    }
}
    |  IF '(' Exp ')' Instr ELSE Instr  %prec ELSE  {
                                                    $$ = makeNode(If);
                                                    Node* cond = makeNode(Cond);
                                                    addChild(cond, $3);
                                                    addChild($$, cond);
                                                    if ($5 != NULL) {
                                                        Node* doo = makeNode(Do);
                                                        addChild(doo, $5);
                                                        addChild($$, doo);
                                                    }
                                                    if ($7 != NULL) {
                                                        Node* elsee = makeNode(Else);
                                                        addChild(elsee, $7);
                                                        addChild($$, elsee);
                                                    }
}
    |  WHILE '(' Exp ')' Instr                      {
                                                    $$ = makeNode(While);
                                                    Node* cond = makeNode(Cond);
                                                    addChild(cond, $3);
                                                    addChild($$, cond);
                                                    if ($5 != NULL) {
                                                        Node* doo = makeNode(Do);
                                                        addChild(doo, $5);
                                                        addChild($$, doo);
                                                    }
}
    |  IDENT '(' Arguments  ')' ';'                 {
                                                    $$ = makeNode(Funct);
                                                    $$->ident = strdup($1);
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
                                                    addChild($$, $3);
}
    |  RETURN Exp ';'                               {
                                                    $$ = makeNode(Return);
                                                    $$->line =@1.first_line;
                                                    $$->column = @1.first_column;
                                                    addChild($$, $2);
}
    |  RETURN ';'                                   {
                                                    $$ = makeNode(Return);
                                                    $$->line =@1.first_line;
                                                    $$->column = @1.first_column;
}
    |  '{' SuiteInstr '}'                           {$$ = $2;}
    |  ';'                                          {$$ = NULL;}
    ;
Exp :  Exp OR TB                                    {
                                                    $$ = makeNode(Or);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
}
    |  TB                                           {$$ = $1;}
    ;
TB  :  TB AND FB                                    {
                                                    $$ = makeNode(And);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
}
    |  FB                                           {$$ = $1;}
    ;
FB  :  FB EQ M                                      {
                                                    $$ = makeNode(Equal);
                                                    $$->ident = strdup($2);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
}
    |  M                                            {$$ = $1;}
    ;
M   :  M ORDER E                                    {
                                                    $$ = makeNode(Order);
                                                    $$->ident = strdup($2);
                                                    addChild($$, $1);
                                                    addChild($$, $3);
}
    |  E                                            {$$ = $1;}
    ;
E   :  E ADDSUB T                                   {
                                                    $$ = makeNode(BiOperator);
                                                    $$->byte = $2;
                                                    addChild($$, $1);
                                                    addChild($$, $3);
}
    |  T                                            {$$ = $1;}
    ;    
T   :  T DIVSTAR F                                  {
                                                    $$ = makeNode(BiOperator);
                                                    $$->byte = $2;
                                                    addChild($$, $1);
                                                    addChild($$, $3);
}
    |  F                                            {$$ = $1;}
    ;
F   :  ADDSUB F                                     {
                                                    $$ = makeNode(UnOperator);
                                                    $$->byte = $1;
                                                    addChild($$, $2);
}
    |  '!' F                                        {
                                                    $$ = makeNode(Negate);
                                                    addChild($$, $2);
}
    |  '(' Exp ')'                                  {$$ = $2;}
    |  NUM                                          {
                                                    $$ = makeNode(Num);
                                                    $$->num = $1;
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
}
    |  CHARACTER                                    {
                                                    $$ = makeNode(Char);
                                                    $$->byte = $1;
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
}
    |  IDENT                                        {
                                                    $$ = makeNode(Ident);
                                                    $$->ident = strdup($1);
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
}
    |  IDENT '(' Arguments  ')'                     {
                                                    $$ = makeNode(Funct);
                                                    $$->ident = strdup($1);
                                                    $$->line = @1.first_line;
                                                    $$->column = @1.first_column;
                                                    addChild($$, $3);
}
    ;
Arguments:
       ListExp                                      {$$ = $1;}
    |                                               {$$ = makeNode(Void);}
    ;
ListExp:
       ListExp ',' Exp                              {
                                                    $$ = $1;
                                                    addSibling($$, $3);
}
    |  Exp                                          {$$ = $1;}
    ;
%%

void yyerror(char* msg) {
    nb_error++;
    fprintf(
        stderr,
        "\033[1m%s:%d:%d: \033[31;1merror:\033[0m %s \033[1m‘%s’\033[0m\n",
        file_name,
        yylloc.first_line,
        yylloc.first_column,
        msg,
        yytext
    );
}
