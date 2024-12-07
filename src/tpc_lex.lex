%{
#include <ctype.h>
#include <stdlib.h>
#include "tree.h"
#include "tpc.tab.h"
void yyerror(char* msg);
int lineno;
%}

%option nounput
%option noinput
%option noyywrap
%option yylineno
%x COMMENTAIRE
%x TEXT
%%

"//".*
"/*" BEGIN COMMENTAIRE;
<COMMENTAIRE>"*/" BEGIN INITIAL;

"'" BEGIN TEXT;
<TEXT>"'" BEGIN INITIAL;
<TEXT>[^"\""'"]|"\n"|"\t"|"\'"|"\\" 

void {strcpy(yylval.type, yytext); return VOID;}

int|char {strcpy(yylval.type, yytext); return TYPE;}

if {strcpy( yylval.key, yytext); return IF;}

else {strcpy( yylval.key, yytext); return ELSE;}

while {strcpy( yylval.key, yytext); return WHILE;}

static {strcpy( yylval.key, yytext); return STATIC;}

return {return RETURN;}

[a-zA-Z_][a-zA-Z0-9_]*/[ \n\t]*\( {strcpy(yylval.ident, yytext); return IDENT;}

[-+] {yylval.byte = yytext[0]; return ADDSUB;}

[/*%] {yylval.byte = yytext[0]; return DIVSTAR;}

[0-9]+ {return NUM;}

[a-zA-Z_][a-zA-Z0-9_]* {strcpy(yylval.ident, yytext); return IDENT;}

"&&" {strcpy(yylval.comp, yytext); return AND;} 

"||" {strcpy(yylval.comp, yytext); return OR;}

== {strcpy(yylval.comp, yytext); return EQ;}

"!=" {strcpy(yylval.comp, yytext); return EQ;}

"<" {strcpy(yylval.comp, yytext); return ORDER;}

"<=" {strcpy(yylval.comp, yytext); return ORDER;}

">" {strcpy(yylval.comp, yytext); return ORDER;}

">=" {strcpy(yylval.comp, yytext); return ORDER;}

[!(),;={}] {return yytext[0];}

<*>\n
<*>.
%%
