#include "TicTacToe.h"
#include <string.h>
#include <stdio.h>

/* Check to see if user wants to play tic tac toe agian
 *
 */
int playAgain(char* input) {
  if(!strcmp(input, "Y"))
    return 1;
  if(!strcmp(input, "y"))
    return 1;
  if(!strcmp(input, "yes"))
    return 1;
  if(!strcmp(input, "Yes"))
    return 1;

  return 0;
}

/* Main method. Runs the tic tac toe program
 */
int main(int argc, char* argv[]) {
  char board[Length][Width]; // create board
  char players[2] = {PLAYER_X, PLAYER_O};
  char input[20];
  char currentPlayer;
  char winner;
  int turn;
  int cont = 1; // whether to continue player the game

  do {
    printf("Resetting board.\n");
    resetboard(board);
    turn = 0;
    winner = NO_WIN;

    // continue
    while(winner == NO_WIN) {
      printf("\n\n\n");
      currentPlayer = players[turn%2];
      printboard(board);
      printf("It is player %c's turn. Enter 'q' if you want to quit the game.\n", currentPlayer); 
      printf("Please enter coordinate as a single number (11, 12, 13, etc): ");
      scanf("%s", input);

      // check if player wants to quit game
      if(!strcmp(input, "q")) {
        printf("\nExiting game...\n");
        return 0;
      }

      // attempt to find coordinates via input
      char* point = returnCoord(input, board);
 
      if(point == NULL) { // invalid input
        printf("\n\nYou have entered an invalid input! Please try again.\n");
        continue;
      } else if(*point != EMPTY) { // point already taken
        printf("\n\nThat spot has already been taken! Please try another one.\n");
        continue;
      } else { // set point
        *point = currentPlayer;
      }

      winner = checkForWin(board);
      turn++;
    }

    printf("\n\n\n");
    printboard(board);
 
    // find whether it was a stale mate or not
    if(winner == STALE_MATE) {
      printf("\nStale mate! There was no winner.\n");
    } else {
      printf("\nThe winner is %c! Way to go!\n", winner);
    }

    // see if players want to play another round
    printf("Would you like to player agian? ");
    scanf("%s", input);
    
    cont = playAgain(input);
  } while(cont);

  printf("\nThanks for playing!\n\n");
}
