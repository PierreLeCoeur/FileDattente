CC = gcc
CFLAGS = -c -g -Wall
EXEC = fileDattente
SRC = $(wildcard *.c )
OBJ = $(SRC:.c=.o)

all: fileDattente

#$(EXEC): $(OBJ)
#	$(CC)  $< -o $@

#%.o : %.c %.h
#	$(CC) $(CFLAGS) $< 

fileDattente:	main.o proba.o 
	gcc main.o proba.o -o fileDattente 

main.o: main.c
	gcc -c -g main.c

proba.o: proba.c proba.h 
	gcc -c -g proba.c

clean: 
	rm *.o  fileDattente "Liste Clients"

