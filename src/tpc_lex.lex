%{
#include <ctype.h>
#include <stdlib.h>
#include "tree.h"
#include "tpc.tab.h"
void yyerror(char* msg);
int lineno = 1;
%}

%option nounput
%option noinput
%option noyywrap

%x COMMENTAIRE
%x TEXT
%%

"//".*
"/*" BEGIN COMMENTAIRE;
<COMMENTAIRE>\n {lineno++;}
<COMMENTAIRE>"*/" BEGIN INITIAL;
<COMMENTAIRE>.

void {strcpy(yylval.type, yytext); return VOID;}

int|char {strcpy(yylval.type, yytext); return TYPE;}

while {strcpy( yylval.key, yytext); return WHILE;}

if {strcpy( yylval.key, yytext); return IF;}

else {strcpy( yylval.key, yytext); return ELSE;}

static {strcpy( yylval.key, yytext); return STATIC;}

return {return RETURN;}

[a-zA-Z_][a-zA-Z0-9_]* {strcpy(yylval.ident, yytext); return IDENT;}

'(\\[a-z]|[^\'])' {return CHARACTER;}

[0-9]+ {return NUM;}

[-+] {yylval.byte = yytext[0]; return ADDSUB;}

[/*%] {yylval.byte = yytext[0]; return DIVSTAR;}

"&&" {strcpy(yylval.comp, yytext); return AND;} 

"||" {strcpy(yylval.comp, yytext); return OR;}

== {strcpy(yylval.comp, yytext); return EQ;}

"!=" {strcpy(yylval.comp, yytext); return EQ;}

"<" {strcpy(yylval.comp, yytext); return ORDER;}

"<=" {strcpy(yylval.comp, yytext); return ORDER;}

">" {strcpy(yylval.comp, yytext); return ORDER;}

">=" {strcpy(yylval.comp, yytext); return ORDER;}

[!(),;={}] {return yytext[0];}

[a-zA-Z_][a-zA-Z0-9_]* {strcpy(yylval.ident, yytext); return IDENT;}

[ \t\r]+
<*>\n               {lineno++;}
<*>.                {return 1;}
%%
