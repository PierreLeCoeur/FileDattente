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

fileDattente:	main.o fonctions.o 
	gcc main.o fonctions.o -o fileDattente -lm -Wall 

main.o: main.c
	gcc -c -g main.c -lm -Wall 

fonctions.o: fonctions.c fonctions.h 
	gcc -c -g fonctions.c -lm -Wall 

clean: 
	rm *.o  fileDattente 

#on supprime le fichier sinon on ajouterait la liste de clients à la simulation précédente
supp_fichiers:
	rm	"Liste Clients.txt"
	rm  "Statistiques.txt"
