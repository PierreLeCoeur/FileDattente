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
	gcc main.o proba.o -o fileDattente -lm

main.o: main.c
	gcc -c -g main.c -lm

proba.o: proba.c proba.h 
	gcc -c -g proba.c -lm

clean: 
	rm *.o  fileDattente 

#on supprime le fichier sinon on ajouterait la liste de clients à la simulation précédente
supp_fichiers:
	rm	"Liste Clients.txt"
	rm  "Statistiques.txt"
