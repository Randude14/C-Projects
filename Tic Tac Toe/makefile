CFLAGS = -Wall -g -O0 -std=c99

all:TicTacToe

TicTacToe: TicTacToe.o TTTGame.o 
	gcc ${CFLAGS} -o TicTacToe TicTacToe.o TTTGame.o

TicTacToe.o: TicTacToe.h TicTacToe.c

TTTGame.o: TicTacToe.h TicTacToe.c TTTGame.c

clean:
	rm TicTacToe TicTacToe.o TTTGame.o
