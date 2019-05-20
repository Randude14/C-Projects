CFLAGS = -Wall -g -O0 -std=c99
CC=gcc

all:hw5

hw5: main.o cards.o dealer.o player.o bjack.o
	${CC} ${CFLAGS} -o hw5 main.o cards.o dealer.o player.o bjack.o

cards.o:cards.c cards.h

dealer.o:dealer.c dealer.h cards.h

player.o:player.c cards.h

bjack.o:bjack.c player.h dealer.h cards.h

clean: 
	rm -rf hw5 main.o cards.o dealer.o player.o main.o bjack.o
