CC = gcc

INCLUDE = -I.

CFLAGS = -g

LDFLAGS = -L. -L/usr/lib

LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

all: main

main: pgm.o filter.o main.o main.c
	$(CC) -o $@ $@.o filter.o pgm.o $(LDFLAGS) $(LDLIBS)

main.o: main.c

clean:
	rm -f *.o
	rm -rf main
	rm dxgrey.pgm
	rm dygrey.pgm
	rm ndxgrey.pgm
	rm ndygrey.pgm

