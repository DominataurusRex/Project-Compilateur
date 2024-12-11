%{
#include <ctype.h>
#include <stdlib.h>
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

void 

int|char

while/[ \n\t]*\(

if {printf("coucou");}

else 

static 

return 

[a-zA-Z_][a-zA-Z0-9_]*/[ \n\t]*\(  {printf("%s\n", yytext);}

\'[a-zA-Z0-9]\'

[0-9]+ 
[-+] 
[/*%]

"&&"

"||" 
==
"!=" 
"<" 
"<="
">"

">=" 

[!(),;={}]

[a-zA-Z_][a-zA-Z0-9_]*

[ \t\r]+
\n
<*>\n
<*>. {printf("%c", yytext[0]);}
%%

int main(int argc, char **argv) {
  yylex();
  return 0;
}
