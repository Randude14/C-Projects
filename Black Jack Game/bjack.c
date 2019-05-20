#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bjack.h"
#include "cards.h"

int CARDS[13] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

void init( char *deck,int CARDS_IN_DECK ) {
   assert (CARDS_IN_DECK==52);
   assert (deck);

   // init deck
   for(int i = 0;i < 13;i++) {
     deck[i] =    CARDS[i] | CLUBS;
     deck[i+13] = CARDS[i] | HEARTS;
     deck[i+26] = CARDS[i] | DIAMONDS;
     deck[i+39] = CARDS[i] | SPADES;
   }

/*
 * this function will initialize a deck of cards
 * there will be one kind of each card in the deck
 * the parameter CARDS_IN_DECK will always be 52,
 * if it is not this is a fatal error.  CARDS_IN_DECK
 * is included to provide possible future modifications.
 *
 */
}

void shuffle( char *deck, int CARDS ) {
  assert (deck);

  int numDecks = CARDS / 52;
  for(int num = 0;num < numDecks;num++) {
    for(int i = 0;i < 52;i++) {
      int currentIndex = num * 52 + i;      // grab current index based on deck
      int ran = rand() % 52 + (num * 52); // grabs a large number and finds the remainder of 52
      char temp = deck[ran];
      deck[ran] = deck[currentIndex];
      deck[currentIndex] = temp;
    }
  }
   

/*
 * this function will shuffle a deck (or several) of cards.
 * one way to do this:
 *              process each card in a for i loop
 *                  use random() to generate a number between 0 and CARDS
 *                  swap the card from deck[i] to deck[random number between 0 and CARDS]
 *              
 */
}

int verify( char *deck, int NUM_DECKS, int CARDS ) {
   assert (deck);
   assert (NUM_DECKS>0);
   assert (CARDS>=52);
   int CHECK_CARDS[4][13] = {0}; // keeps track of cards in current deck

   for(int i = 0;i < CARDS;i++) {
     int suit = deck[i] >> 4;
     int value = card_value(deck[i])-1;
     if(CHECK_CARDS[suit][value] < NUM_DECKS) { // number of unique cards = NUM_DECKS
       CHECK_CARDS[suit][value]++;              // increment
     } else {
       return 0; // if we already have this card in the current deck, return 0
     }
   }
   


/* 
 * this function will verify that the deck has the correct
 * type of cards.  this is to ensure that the shuffle routine 
 * was correct, and did not duplicate or remove any cards.
 *
 * suggestion:  use an array to count how many of each card type
 * is in the deck.
 *
 * return value is a 1 if the deck is good, otherwise it returns a
 * 0
 *
 */

   return 1;
}

int deal (char* deck,char *card) {
   assert (deck);
   assert (card);
/*
 * this function returns two values:
 *    the return value is the number of cards left in the deck.
 *    *card is the card to be dealt.
 *
 *    (note) use a bit in the card to signify a card has been dealt,
 *    see cards.h
 */

  int notDealt = 0; // keep track of number of cards not dealt
  for(int i = 0;i < 52;i++) {
    if(!is_dealt(deck[i])) {
      notDealt++;
    }
  }

  if(notDealt > 0) {
    int i = 0;
    while(is_dealt(deck[i++])) { }
    i--;
    *card = deck[i];
    deck[i] |= DEALT;
    notDealt--;
  } else {
    *card = -1;
  }

  return notDealt;
}


void calculate_hand_value (char* cards, int N, int* value, int* N_VALUES) {
   assert(N>0);
   assert (cards);
   assert (value);
   assert (N_VALUES);


/*
 * this function calculates the different values for a hand of cards.
 * for example:
 *
 *           N = 1
 *           cards[0] = 3 of clubs
 *
 *           value[0]=3
 *           N_VALUES=1
 *
 *
 *  another example
 *
 *          N = 2
 *          cards[0]=10 diamonds
 *          cards[1]=ace of spades
 *
 *          value[0] = 11
 *          value[1] = 21
 *          N_VALUES = 2
 *
 *
 * there are some functions in cards.h that will help you here.
 */

  int aceDealt = 0; // keep track of whether an ace has already come through
  
  // find total value of cards
  for(int i = 0;i < N;i++) {
    int cardValue = card_value(cards[i]);
    // set cardValue to 10: jack, queen, or king equal 10
    cardValue = (cardValue > 10) ? 10 : cardValue;
    value[0] = value[0] + cardValue;
    if(cardValue == ACE) {
      aceDealt = 1;
    }
  }

  // check if an has been dealt and if there is enough room to add 10
  // NOTE: this accounts for the first ace that can be valued at 1 or 11 (11-1 = 10)
  if(aceDealt && value[0] + 10 <= 21) {
    value[1] = value[0] + 10;
    *N_VALUES = 2;

  // if not ace has been dealt, check if less than 21
  } else if(value[0] <= 21) {
    *N_VALUES = 1;

  // otherwise this player has busted 21 and set values to 0
  } else {
    value[0] = 0;
    *N_VALUES = 0;
  }
   
/*
    // test values
    *value=21;
    value++;
    *value=10;
    *N_VALUES=2;*/
}

