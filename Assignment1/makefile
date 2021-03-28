CC = gcc

INCLUDE = -I.

CFLAGS = -g

LDFLAGS = -L. -L/usr/lib

LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

all: main

main: pgm.o ppm.o main.o main.c
	$(CC) -o $@ $@.o pgm.o ppm.o $(LDFLAGS) $(LDLIBS)

main.o: main.c

clean:
	rm -f *.o
	rm -rf main

