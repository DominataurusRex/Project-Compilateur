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
%%

"//".*
"/*" BEGIN COMMENTAIRE;
<COMMENTAIRE>\n {lineno++;}
<COMMENTAIRE>"*/" BEGIN INITIAL;
<COMMENTAIRE>.

void {strcpy(yylval.ident, yytext); return VOID;}

int|char {strcpy(yylval.ident, yytext); return TYPE;}

while {return WHILE;}

if {return IF;}

else {return ELSE;}

static {return STATIC;}

return {return RETURN;}

[a-zA-Z_][a-zA-Z0-9_]* {strcpy(yylval.ident, yytext); return IDENT;}

'(\\[a-z]|[^\'])' {yylval.byte = yytext[0]; return CHARACTER;}

[0-9]+ {yylval.num = atoi(yytext); return NUM;}

[-+] {yylval.byte = yytext[0]; return ADDSUB;}

[/*%] {yylval.byte = yytext[0]; return DIVSTAR;}

"&&" {return AND;} 

"||" {return OR;}

"==" {strcpy(yylval.ident, yytext); return EQ;}
"!=" {strcpy(yylval.ident, yytext); return EQ;}

"<" {strcpy(yylval.ident, yytext); return ORDER;}
"<=" {strcpy(yylval.ident, yytext); return ORDER;}
">" {strcpy(yylval.ident, yytext); return ORDER;}
">=" {strcpy(yylval.ident, yytext); return ORDER;}

[ \t\r]+ ; 
<*>\n               {lineno++;}
<*>.                {return yytext[0];}
%%
