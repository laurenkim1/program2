all: strassen

strassen: strassen.o
	gcc strassen.o -o strassen -O3

strassen.o: strassen.c
	gcc -Wall -c strassen.c -O3

clean:
	rm *o strassen
