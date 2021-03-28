CC = gcc

INCLUDE = -I.

CFLAGS = -g

LDFLAGS = -L. -L/usr/lib

LDLIBS = -lc -lm

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

all: main

main: pgm.o filter.o main.o main.c
	$(CC) -o $@ $@.o pgm.o filter.o $(LDFLAGS) $(LDLIBS)

main.o: main.c

clean:
	rm -f *.o
	rm -rf main
	rm Final.pgm
	rm grey.pgm
	rm dgrey.pgm
	rm ngrey.pgm
	

