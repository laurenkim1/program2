all: strassen

strassen: strassen.o
	gcc strassen.o -o strassen

strassen.o: strassen.c
	gcc -Wall -c strassen.c

clean:
	rm *o strassen
