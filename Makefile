CC = gcc
CFLAGS = -Wall $(shell pkg-config --libs --cflags opencv)

PROG = sample

SRCS = sample.c
LIBS =

$(PROG): $(SRCS) $(LIBS)
	$(CC) $(CFLAGS) -o $(PROG) $<

clean:
	rm -rf *.o $(PROG)
