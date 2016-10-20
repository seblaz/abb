# abb
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
OBJ = o/abb.o o/nodo_ab.o o/main.o o/pruebas_arbol.o o/pruebas_nodo.o o/testing.o
EXEC = abb
CC = gcc

all:abb

o/abb.o:abb.c abb.h
	$(CC) $(CFLAGS) -c -o o/abb.o abb.c

o/nodo_ab.o:nodo_ab.c nodo_ab.h
	$(CC) $(CFLAGS) -c -o o/nodo_ab.o nodo_ab.c

o/pruebas_arbol.o:pruebas_arbol.c
	$(CC) $(CFLAGS) -c -o o/pruebas_arbol.o pruebas_arbol.c

o/pruebas_nodo.o:pruebas_nodo.c
	$(CC) $(CFLAGS) -c -o o/pruebas_nodo.o pruebas_nodo.c

o/testing.o:testing.c testing.h
	$(CC) $(CFLAGS) -c -o o/testing.o testing.c

o/main.o:main.c
	$(CC) $(CFLAGS) -c -o o/main.o main.c

$(EXEC):$(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

.PHONY: all clean count

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(EXEC)

run:
	./$(EXEC)
