all : main

main : biblioLC.o entreeSortieLC.o main.c
	gcc -Wall -c main.c -ggdb -o main.o
	gcc -Wall biblioLC.o entreeSortieLC.o main.o -ggdb -o main

biblioLC.o : biblioLC.c biblioLC.h
	gcc -Wall -c biblioLC.c -ggdb -o biblioLC.o

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h
	gcc -Wall -c entreeSortieLC.c -ggdb -o entreeSortieLC.o


clean:
	rm -rf *.o main