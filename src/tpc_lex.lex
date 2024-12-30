%{
#include <ctype.h>
#include <stdlib.h>
#include "tree.h"
#include "tpc.tab.h"
void yyerror(char* msg);
extern YYLTYPE yylloc;
%}

%option nounput
%option noinput
%option noyywrap

%x COMMENTAIRE
%%

"//".*
"/*"                    BEGIN COMMENTAIRE;
<COMMENTAIRE>\n         {yylloc.first_line++; yylloc.first_column = 1;}
<COMMENTAIRE>"*/"       BEGIN INITIAL;
<COMMENTAIRE>.

void                    {yylloc.first_column += 4; strcpy(yylval.ident, yytext); return VOID;}

int|char                {yylloc.first_column += yyleng; strcpy(yylval.ident, yytext); return TYPE;}

while                   {yylloc.first_column += 5; return WHILE;}

if                      {yylloc.first_column += 2; return IF;}

else                    {yylloc.first_column += 4; return ELSE;}

static                  {yylloc.first_column += 6; return STATIC;}

return                  {yylloc.first_column += 6; return RETURN;}

[a-zA-Z_][a-zA-Z0-9_]*  {yylloc.first_column += yyleng; strcpy(yylval.ident, yytext); return IDENT;}

'(\\[a-z]|[^\'])'       {yylloc.first_column++; yylval.byte = yytext[1]; return CHARACTER;}

[0-9]+                  {yylloc.first_column += yyleng; yylval.num = atoi(yytext); return NUM;}

[-+]                    {yylloc.first_column++; yylval.byte = yytext[0]; return ADDSUB;}

[/*%]                   {yylloc.first_column++; yylval.byte = yytext[0]; return DIVSTAR;}

"&&"                    {yylloc.first_column += 2; return AND;} 

"||"                    {yylloc.first_column += 2; return OR;}

"=="                    {yylloc.first_column += 2; strcpy(yylval.ident, yytext); return EQ;}

"!="                    {yylloc.first_column += 2; strcpy(yylval.ident, yytext); return EQ;}

"<"                     {yylloc.first_column++; strcpy(yylval.ident, yytext); return ORDER;}

"<="                    {yylloc.first_column += 2; strcpy(yylval.ident, yytext); return ORDER;}

">"                     {yylloc.first_column++; strcpy(yylval.ident, yytext); return ORDER;}

">="                    {yylloc.first_column += 2; strcpy(yylval.ident, yytext); return ORDER;}

[ \t\r]+ ; 
<*>\n                   {yylloc.first_line++; yylloc.first_column = 1;}
<*>.                    {yylloc.first_column++; return yytext[0];}
%%
