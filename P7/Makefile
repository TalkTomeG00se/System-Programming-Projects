CC = gcc
CFLAGS = -Wall -std=c99

all: smash

smash: smash.o smashLib.a
	$(CC) $(CFLAGS) -g -lm -o smash smash.o smashLib.a

smash.o: smash.c
	$(CC) $(CFLAGS) -g -O -c smash.c smash.h

history.o: history.c history.h
	$(CC) $(CFLAGS) -g -O -c history.c

smashLib.a: history.o 
	ar rcs smashLib.a history.o 

clean:
	rm -f smash *.o *.a *.gch





