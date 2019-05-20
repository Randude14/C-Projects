#include "TicTacToe.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Resets the tic tac toe board to EMPTY
 */
void resetboard(char board[Length][Width]) {

  for(int i = 0;i < Length;i++) {
    for(int j = 0;j < Width;j++) {
      board[i][j] = EMPTY;
    }
  }
}

char checkForWin(char board[Length][Width]) {
  int i;
  
  // check for vertical wins
  for(i = 0;i < Length;i++) {
    if(board[i][0] != EMPTY && board[i][0] == board[i][1] 
           && board[i][1] == board[i][2]) {
      return board[i][0];
    }
  }

  // check for horizontal wins
  for(i = 0;i < Width;i++) {
    if(board[0][i] != EMPTY && board[0][i] == board[1][i] 
           && board[1][i] == board[2][i]) {
      return board[0][i];
    }
  }

  // check diagonal wins
  if(board[0][0] != EMPTY && board[0][0] == board[1][1] 
           && board[1][1] == board[2][2]) {
    return board[0][0];
  }

  if(board[0][2] != EMPTY && board[0][2] == board[1][1] 
           && board[1][1] == board[2][0]) {
    return board[0][2];
  }

  for(int i = 0;i < Length;i++) {
    for(int j = 0;j < Width;j++) {
      if(board[i][j] == EMPTY)
        return NO_WIN;
    }
  }

  // if board is full and there is no winner,
  // return that it is a stale mate
  return STALE_MATE;
}

void printboard(char board[Length][Width]) {

  // print separator and column numbers
  printf("__");
  for(int i = 0;i < Length;i++) {
    printf("____");
  }

  printf("\n  ");
  for(int i = 0;i < Length;i++) {
    printf("%4d", i+1);
  }

  printf("\n");

  // print out grid and row numbers
  for(int i = 0;i < Length;i++) {
    printf("\n%2d", i+1);
    for(int j = 0;j < Width;j++) {
      printf("%4c", board[i][j]);
    }
    printf("\n");
  }

  // print out separator
  printf("__");
  for(int i = 0;i < Length;i++) {
    printf("____");
  }
  printf("\n");
}

/*
 * Give the input from the console, return the coordinate that 
 * input points to, otherwise return NULL
 */
char* returnCoord(char* input, char board[Length][Width]) {
  if(strlen(input) < 2)
    return 0;

  // check if input contains numbers to point to
  if(input[0] < '0' || input[0] > '9' || input[1] < '0' || input[1] > '9') {
    return NULL;
  }

  // subtract 1 to point program coordinates
  int x = input[1] - '0' - 1;
  int y = input[0] - '0' - 1;

  // check coordinates are within bounds
  if(x >= 0 && x < Length && y >= 0 && y < Width) {
    return &( board[x][y] );
  } else {
    return NULL;
  }
}

