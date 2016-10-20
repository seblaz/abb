# abb
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
OBJ = o/abb.o o/nodo_ab.o o/main.o o/pruebas_alumno.o o/pruebas_test.o o/testing.o
EXEC = abb
CC = gcc

all:abb

o/abb.o:abb.c abb.h
	$(CC) $(CFLAGS) -c -o o/abb.o abb.c

o/nodo_ab.o:nodo_ab.c nodo_ab.h
	$(CC) $(CFLAGS) -c -o o/nodo_ab.o nodo_ab.c

o/pruebas_alumno.o:pruebas_alumno.c
	$(CC) $(CFLAGS) -c -o o/pruebas_alumno.o pruebas_alumno.c

o/pruebas_test.o:pruebas_test.c
	$(CC) $(CFLAGS) -c -o o/pruebas_test.o pruebas_test.c

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
