CC=gcc

ast.o: ast.c
	$(CC) -c ast.c -o ast.o

out: main.c ast.o
	$(CC) main.c ast.o -o out
