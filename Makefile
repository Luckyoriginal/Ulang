CC=gcc

all:out

hashdict.o: hashdict.c
	$(CC) -c hashdict.c -o hashdict.o

arena.o: arena.c
	$(CC) -c arena.c -o arena.o

ast.o: ast.c
	$(CC) -c ast.c -o ast.o

parser.o: parser.c
	$(CC) -c parser.c -o parser.o

out: main.c ast.o parser.o arena.o hashdict.o
	$(CC) main.c ast.o parser.o arena.o hashdict.o -o out
