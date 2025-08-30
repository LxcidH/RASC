# Copyright (c) <2025>, <Lxcid>
# All rights reserved.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.


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
