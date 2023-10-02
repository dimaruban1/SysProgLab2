
output: main.o automata.o
	clang main.o automata.o -o output

main.o: main.c automata.h
	clang -c main.c

automata.o: automata.c automata.h
	clang -c automata.c

clean: 
	rm *.o output
