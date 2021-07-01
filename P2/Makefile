CC = gcc
CFLAGS = -Wall 

match: match.o
	gcc match.o -o match

all: 
	gcc -Wall match.c -o match

match.o: match.c
	gcc -c match.c -o match.o

clean:
	rm -f *.o match



