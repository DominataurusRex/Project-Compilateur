EXEC=exp-tpc
PARSER=exp-tpc
LEXER=exp-tpc

# Compilation toto
$(EXEC): $(PARSER).o lex.yy.o
	gcc $(PARSER).o lex.yy.o -o $(EXEC) -lfl


lex.yy.o: lex.yy.c
	gcc -Wall -std=c17 -pedantic -c -ly lex.yy.c -o lex.yy.o -lfl


lex.yy.c: $(LEXER).lex
	flex $(LEXER).lex


# Compilation Bison
$(PARSER).o: $(PARSER).tab.c
	gcc -Wall -std=c17 -pedantic -c -ly $(PARSER).tab.c -o $(PARSER).o


$(PARSER).tab.c $(PARSER).tab.h: $(PARSER).y
	bison -d $(PARSER).y


clean:
	rm -f lex.yy.*
	rm -f $(PARSER).tab.*
	rm -f parser.o
