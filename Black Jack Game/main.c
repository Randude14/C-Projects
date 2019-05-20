#include <stdio.h>
#include <stdlib.h>

#include "cards.h"
#include "bjack.h"
#include "player.h"


#define NUM_DECKS (2)
#define CARDS_IN_DECK (52)

/*
 * Assignment 5 is to implement some of the low level functions
 * that will be needed for a game of blackjack.
 *
 * To learn more * about blackjack, either head to Las Vegas for
 * a long weekend, or ask wikipedia, the source of all knowledge.
 *
 * The headers and test code for each routine you need to write
 * are included in this assignment.
 *
 * Feel free to add additional tests to main.c
 *
 * At your discretion, you can add more functions.  If you think that
 * the parameters for any functions defined in this assignment need
 * to be changed, please contact the instructor.  The next assignment
 * will build on this one, so changes in the data structures or function
 * prototypes  may cause the next assignment to become more complex.
 *
 * well written and tested routines will make the follow on assignment
 * much more pleasant.
 *
 * the makefile should be functional as is.  if you need to change it,
 * feel free to do so.
 *
 * Turn in this tarball, renamed as described in assignment 4,
 * after you have implemented and tested the 'stub' functions.
 *
 */

int main(int argc,char* argv[])
{
   // this main program will test some of the functions

   char deck[CARDS_IN_DECK*NUM_DECKS];

   init( deck, CARDS_IN_DECK );               // creates a deck of cards
   init( deck+CARDS_IN_DECK, CARDS_IN_DECK ); // creates another deck of cards

   shuffle( deck, CARDS_IN_DECK*NUM_DECKS );  // shuffles the deck of cards

   if ( !verify( deck, NUM_DECKS, CARDS_IN_DECK*NUM_DECKS) )
   {
      printf("the deck is not correct\n");
   }
   else
   {
      printf("the deck is OK\n");
   }

  // simple method testing

   char hand1[3]={0};
   hand1[0] = ACE | DIAMONDS;
   hand1[1] = THREE | SPADES;
   hand1[2] = ACE | SPADES;
   int* value;
   int* n_values;
   value = (int*) malloc (sizeof(int)*10); // should be big enough
   n_values = (int*) malloc (sizeof(int));
   calculate_hand_value (hand1,3,value,n_values);
   if(*n_values < 1) {
     printf("Player has busted!\n");
   }
   for(int i = 0;i < *n_values;i++) {
     printf("%d %d\n",i,value[i]);
   }
   
/*
   // put in code here to test player_move
   int split = 0;
   int _double = 0;
   int pass = 0;
   int hit = 0;
   player_move(&hit, &pass, &_double, &split);

   // only one of these should be set to 1
   printf("Hit: %d, Pass: %d, Double: %d, Split: %d\n", hit, pass, _double, split);
*/


  // put in code here to test deal()
  char card = -1;
  do {
    int left = deal(deck, &card);
    if(card >= 0) {
      printf("You drew a ");
      print_card(card);
      printf("There are cards %d left.\n\n", left);
    } else {
      printf("No cards to draw.\n");
    }
  } while(card >= 0);
 
  return 0;
}
