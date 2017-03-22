all: strassen

stressen: strassen.o
	gcc -o strassen.o -O3

strassen.o: strassen.c
	gcc -Wall -c strassen.c -O3

clean:
	rm *o strassen
