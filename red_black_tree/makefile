# makefile BST

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c99
MAIN = myrb

# lista de arquivos-objetos
OBJ = main.o rb.o

# executavel
myrb: main.o rb.o
	$(CC) -o $(MAIN) $(OBJ)

# TAD
rb.o: rb.c rb.h
	$(CC) -c $(CFLAGS) rb.c

# compila tp1
main.o: main.c rb.h
	$(CC) -c $(CFLAGS) main.c

# executar
run: $(MAIN)
	./$(MAIN)

# limpar arquivos temporarios
clean:
	rm -f *~ $(OBJ) $(MAIN) .out