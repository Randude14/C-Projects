/* To represent a playing card, use
 * an 8 bit variable, like a 'char'
 *
 * The value of the card is stored in the 
 * bottom 4 bits
 *
 * The suite of the card is stored in the next 2 
 * bits
 */


#define VALUE_MASK 0x0F

#define ACE   0x01
#define TWO   0x02
#define THREE 0x03
#define FOUR  0x04
#define FIVE  0x05
#define SIX   0x06
#define SEVEN 0x07
#define EIGHT 0x08
#define NINE  0x09
#define TEN   0x0a
#define JACK  0x0b
#define QUEEN 0x0c
#define KING  0x0d

#define SUITE_MASK 0x40

#define CLUBS    0x00
#define HEARTS   0x10
#define DIAMONDS 0x20
#define SPADES   0x30

#define DEALT 0x80

/* 
 * the lowest value card representation is an ACE of CLUBS, 0x01.
 * the higest value card representation is a KING of SPADES, 0x3d.
 */

void print_card ( char card);
int card_value ( char card );
int is_ace ( char card );

int is_dealt ( char card );
