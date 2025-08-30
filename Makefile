CC		= gcc
CFLAGS	= -Wall -g -std=c99
LDLIBS  = -lncurses
RM		= rm -f

default: all

all: Main

Main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LDLIBS)

clean:
	$(RM) main

run: all
	./main
