CC = gcc
CFLAGS = -Wall -g -Iobj -Isrc
PARSER = tpc
LEXER = tpc_lex

bin/tpcas: obj/$(LEXER).o obj/$(PARSER).o obj/tree.o obj/table_sym.o obj/main.o 
	mkdir bin -p
	$(CC) -o $@ $^ -lfl

obj/main.o: src/main.c
	gcc -c -o obj/main.o src/main.c $(CFLAGS)

obj/$(PARSER).o: obj/$(PARSER).tab.c src/tree.h src/table_sym.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).o: obj/$(LEXER).c obj/$(PARSER).tab.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/%.o: src/%.c src/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

obj/$(LEXER).c: src/$(LEXER).lex obj/$(PARSER).tab.h
	flex -o $@ $<

obj/$(PARSER).tab.c obj/$(PARSER).tab.h &: src/$(PARSER).y
	mkdir obj -p
	bison -d -o obj/$(PARSER).tab.c $<

clean:
	rm obj -rf

cleanall:
	make clean
	rm bin -rf


testG:
	@for file in test/good/*; do \
		echo "Traitement $$file"; \
		./bin/tpcas < "$$file"; \
	done


testB:
	@for file in test/syn-err/*; do \
		echo "Traitement $$file"; \
		./bin/tpcas < "$$file"; \
	done
