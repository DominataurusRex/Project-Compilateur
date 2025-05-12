CC = gcc
CFLAGS = -Wall -g -Iobj -Isrc
PARSER = tpc
LEXER = tpc_lex

bin/tpcc: obj/$(LEXER).o obj/$(PARSER).o obj/tree.o obj/table_sym.o obj/main.o obj/parcour_tree.o obj/compil.o obj/error.o obj/implement.o
	mkdir bin -p
	$(CC) -o $@ $^ -lfl

obj/main.o: src/main.c
	$(CC) -c -o obj/main.o src/main.c $(CFLAGS)

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


nasm: bin/_anonymous.asm
	mkdir obj -p
	nasm -f elf64 bin/_anonymous.asm -o obj/_anonymous.o
	gcc -o bin/_anonymous obj/_anonymous.o -no-pie -nostartfiles


clean:
	rm obj -rf

cleanall:
	make clean
	rm bin -rf


testGood:
	@for file in test/good/*; do \
		echo "Traitement $$file"; \
		./bin/tpcc < "$$file"; \
	done


testSem:
	@for file in test/sem-err/*; do \
		echo "Traitement $$file"; \
		./bin/tpcc < "$$file"; \
	done


testSyn:
	@for file in test/syn-err/*; do \
		echo "Traitement $$file"; \
		./bin/tpcc < "$$file"; \
	done


testWarn:
	@for file in test/warn/*; do \
		echo "Traitement $$file"; \
		./bin/tpcc < "$$file"; \
	done
