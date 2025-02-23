all : main

main : biblioLC.o entreeSortieLC.o main.c
	gcc -Wall -c main.c -ggdb -o main.o
	gcc -Wall biblioLC.o entreeSortieLC.o main.o -ggdb -o main

#Compilation pour BiblioLC
biblioLC.o : biblioLC.c biblioLC.h
	gcc -Wall -c biblioLC.c -ggdb -o biblioLC.o

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h
	gcc -Wall -c entreeSortieLC.c -ggdb -o entreeSortieLC.o

#Compilation pour BiblioH
biblioH.o : biblioH.c biblioH.h
	gcc -Wall -c biblioH.c -ggdb -o biblioH.o

entreeSortieH.o : entreeSortieH.c entreeSortieH.h
	gcc -Wall -c entreeSortieH.c -ggdb -o entreeSortieH.o

clean:
	rm -rf *.o main main_compare