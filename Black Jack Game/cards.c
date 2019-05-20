#include <stdio.h>
#include <assert.h>

#include "cards.h"

char SUIT_NAMES[4][10] = {"Clubs", "Hearts", "Diamonds", "Spades"};
char CARD_NAMES[13][10] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

void print_card ( char card) {
/* this function prints out 
 * a card to stdout.  without a newline.
 * examples
 *       10 Diamonds
 *       Ace Spades
 *       4 Clubs
 */

 int suit = ((unsigned char)card) >> 4;
 int value = card_value(card);
 printf("%s %s\n", CARD_NAMES[value-1], SUIT_NAMES[suit]);
}

int card_value ( char card ) {
/*
 * this function returns a numerical value of a card.
 * the card is defined using the defined constants for
 * suite and value.
 *
 * if the card is an ace, it returns a 1.
 *
 */
   return ((unsigned char)card) & 0xF;
}

int is_ace ( char card ) {
/*
 * this function returns a 1 if the card is an ace.
 * in all other situations, it returns a 0.
 *
 */
   return card_value(card) == ACE;
}

int is_dealt (char card) {
/* 
 * this function returns a 1 if the card has been 
 * dealt.  otherwise, it returns a 0
 *
 */

   return ((unsigned char)card)>>7==DEALT>>7;
}
