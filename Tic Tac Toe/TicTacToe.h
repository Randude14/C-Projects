/* This class is mainly responsible for board manipulation and
 * helping with runnig a separate tic tac toe program
 */

// deminsions of the tic tac toe board
#define Length 3
#define Width 3

#define PLAYER_X 'X' // player X
#define PLAYER_O 'O' // player O
#define EMPTY '-'    // empty space
#define STALE_MATE '^' // used to signify board is full
#define NO_WIN '!'   // used in checkForWin

/* Resets the tic tac toe board to EMPTY
 */
void resetboard(char board[Length][Width]);

/* Checks if a player has won the game
 * returns either NO_WIN if winner is still indeterminant, 
 * STALE_MATE if board is full and there is no winner
 * otherwise returns PLAYER_X or PLAYER_O
 */
char checkForWin(char board[Length][Width]);

/* Prints the tic tac toe board to the console
 */
void printboard(char board[Length][Width]);

/*
 * Give the input from the console, return the coordinate that 
 * input points to, otherwise return NULL
 */
char* returnCoord(char* input, char board[Length][Width]);
