
CC = gcc
CFLAGS = -std=c2x -Wall -Wextra -Werror
TARGET = prova1_20244503_20245106
OBJS = arvoreB.o fila.o main.o

# compilae gera o executavel
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

arvoreB.o: arvoreB.c arvoreB.h fila.h
	$(CC) $(CFLAGS) -c arvoreB.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

main.o: main.c arvoreB.h
	$(CC) $(CFLAGS) -c main.c

# limpa os temporarios e o executavel
clean:
	rm -f $(OBJS) $(TARGET)

#para rodar com o valgrind
run: all
	./$(TARGET)

valgrind: all
	valgrind --leak-check=full ./$(TARGET)