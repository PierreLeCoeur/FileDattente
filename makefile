fileDattente: main.o proba.o
	gcc main.o proba.o -o fileDattente

main.o: main.c
	gcc -c main.c

proba.o: proba.c proba.h 
	gcc -c proba.c

clean: 
	rm *.o  fileDattente
