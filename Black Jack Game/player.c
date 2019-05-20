#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "player.h"


char ACTIONS[4][10] = {"split", "hit", "pass", "double"};

/*
 * Compares two strings, ignoring case
 * returns 1 if strings are equal, otherwise 0
 */
int strcmp_(char* string1, char* string2) {
  int len1 = strlen(string1);
  int len2 = strlen(string2);
  int index = (len1 < len2) ? len1 : len2; // find min length

  while(index >= 0) {
    char a = string1[index];
    char b = string2[index];
    if(a != b) {
      return 0;
    }
    index--;
  }
 
  return 1;
}


void player_move(int *hit, int* pass, int* _double, int* split) {
  assert (hit);
  assert (pass);
  assert (_double);
  assert (split);

  char delim[] = " .,";

  while(1) {
    printf("What would you like to do? ");
    char input[1024];
    scanf("%[^\n]%*c", input);

    char* token = strtok(input, delim);
    // check if player selected more than one option or none
    int numOptions = 0;

    while(token != NULL) {
      if(!strcmp(token, ACTIONS[0])) {
        *split = 1;
        numOptions++;
      } else if(!strcmp(token, ACTIONS[1])) {
        *hit = 1;
        numOptions++;
      } else if(!strcmp(token, ACTIONS[2])) {
        *pass = 1;
        numOptions++;
      } else if(!strcmp(token, ACTIONS[3])) {
        *_double = 1;
        numOptions++;
      }
      
      token = strtok(NULL, delim);
    }

    if(numOptions == 0 || numOptions > 1) {
      printf("You have selected too many options or none. Please try again.\n\n");
      *_double = 0;
      *pass = 0;
      *hit = 0;
      *split = 0;
    } else {
      break;
    }
  }


/*
 * this function will read an entire line (char*) from stdout and parse the
 * words to determine what the player intends to do.
 * use strtok() to slice the input line into tokens.
 * the player is allowed to enter in additional words, like "I would like to split", and this
 * function will then set the *split argument to true.
 *
 * another example is the player could enter "Hit Me" and this routine would set *hit argument
 * to true;
 *
 * only one of hit, pass, _double, or split is set.
 */
}



int player_bet()
{
/*
 * this function will prompt for and receive the players bet
 */
  int bet = 0;
  printf("Please enter the amount you would like to bet: ");
  scanf("%d", &bet);  
  return 0;
}
