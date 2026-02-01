CC=gcc

all:out

ast.o: ast.c
	$(CC) -c ast.c -o ast.o

parser.o: parser.c
	$(CC) -c parser.c -o parser.o

out: main.c ast.o parser.o
	$(CC) main.c ast.o parser.o -o out
