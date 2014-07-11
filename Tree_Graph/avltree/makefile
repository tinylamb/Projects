main: main.o tree.o 
	clang main.o tree.o -o main
main.o: main.c tree.h
	clang -c main.c
tree.o: tree.c tree.h
	clang -c tree.c

