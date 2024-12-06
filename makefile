CC = gcc
CFLAGS = -Wall -g -Iobj -Isrc
PARSER = tpc
LEXER = tpc_lex

bin/tpcas: obj/$(LEXER).o obj/$(PARSER).o obj/tree.o # ...
	$(CC) -o $@ $^

obj/tree.o: src/tree.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(PARSER).o: obj/$(PARSER).tab.c src/tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).o: obj/$(LEXER).c obj/$(PARSER).tab.h
	$(CC) -c -o $@ $< $(CFLAGS)
# ...

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).c: src/$(LEXER).lex obj/$(PARSER).tab.h
	flex -o $@ $<

obj/$(PARSER).tab.c obj/$(PARSER).tab.h &: src/$(PARSER).y
	bison -d -o obj/$(PARSER).tab.c $<

clean:
	rm obj/*

cleanall:
	make clean
	rm bin/tpcas