#include <stdio.h> 
#include <assert.h>

#define MASK 0xF // The main mask used to & integers and retrieve the front hexadecimal values.
#define N 8 // length of bcd, represents a 32 bit word
#define LENGTH 48 // (5 characters spaces + 1 blank space) * (8 numbers)
#define WIDTH 5 // 5 characters tall

/*
 * Precondition: takes an unsigned integer the represents the input
 * Postcondition: determines the 8 digit packed BCD and passes it to
 *                the function displayBCD(int bcd[]) to display output
 */
void processInput(unsigned int input);

/*
 * Precondition: takes an 8 gigit packed BCD to be displayed
 * Postcondition: the 8 digit packed BCD is converted to a 5 x 5
 *                character display that represents a calculator
 */
void displayBCD(int bcd[]);

/*
 * Precondition: takes in an array that represents the display, the characters
 *               to fill in onto the screen, the x that points to how far on the
 *               line we are starting, y represents the line number, and stop is
 *               the length of the array
 * Postcondition: the display has been filled with the characters in the correct spot
 */
void fill(char display[], char fillWith[], int x, int y, int stop);

/*
 * Precondition: either takes in and reads a file or input from terminal
 * Postconfition: finishes reading from said file or the user operating
 *                the terminal has entered a -1 to terminate the program
 */
int main(int argc, char *argv[]) { 
  unsigned int input = 0;
  scanf("%d", &input);
  while((int)input != -1) {
    processInput(input);
    scanf("%d", &input);
  }
  return 0;
}

void processInput(unsigned int input) {
  int bcd[N] = {0};
  // Retrieve the hex digits and store in an array
  // Start at end value because we start masking at front
  for(int i = N-1;i >= 0;i--) {
    int hex = input & MASK;
    if(hex < 10) { // bcd value cannot be > 9
      bcd[i] = hex;
    }
    input = input >> 4; // Truncate our input
  }
  displayBCD(bcd);
}

void fill(char display[], char fillWith[], int x, int y, int stop) {
  for(int i = 0;i < stop;i++) {
    int line = y * LENGTH;
    assert(line+x+i < LENGTH * WIDTH);
    display[line+x+i] = fillWith[i];
  }
}

void displayBCD(int bcd[]) {
  // Represents the display of the screen. 
  char display[LENGTH * WIDTH];

  // Move from left to right
  for(int i = 0;i < N;i++) {
    int offset = i * 6;
    assert(bcd[i] >= 0 && bcd[i] <= 9);
    if(bcd[i] == 0) {
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 1, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 2, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 1) {
      fill(display, (char[]){' ', ' ', ' ', ' ', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 1, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 2) {
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){' ', ' ', ' ', '/', ' ', ' '}, offset, 1, 6);
      fill(display, (char[]){' ', ' ', '/', ' ', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', '/', ' ', ' ', ' ', ' '}, offset, 3, 6);
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 3) {
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 1, 6);
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 4) {
      fill(display, (char[]){' ', ' ', ' ', ' ', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', ' ', ' '}, offset, 1, 6);
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', ' ', '^', ' ', ' ', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', ' ', '^', ' ', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 5) {
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', ' ', ' '}, offset, 1, 6);
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 6) {
      fill(display, (char[]){' ', ' ', ' ', ' ', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', ' ', ' '}, offset, 1, 6);
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 7) {
      fill(display, (char[]){'-', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){' ', ' ', ' ', '/', ' ', ' '}, offset, 1, 6);
      fill(display, (char[]){' ', ' ', '/', ' ', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', '/', ' ', ' ', ' ', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', ' ', ' '}, offset, 4, 6);
    } else if(bcd[i] == 8) {
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 1, 6);
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 4, 6);
    } else { // after assert check assume 9
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 0, 6);
      fill(display, (char[]){'|', ' ', ' ', ' ', '|', ' '}, offset, 1, 6);
      fill(display, (char[]){' ', '-', '-', '-', ' ', ' '}, offset, 2, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', '|', ' '}, offset, 3, 6);
      fill(display, (char[]){' ', ' ', ' ', ' ', ' ', ' '}, offset, 4, 6);
    }
  }

  // goes through 48 characters and then moves on to the next line
  for(int i = 0;i < WIDTH;i++) {
    for(int j = 0;j < LENGTH;j++) {
      assert(i*LENGTH+j < LENGTH*WIDTH);
      printf("%c", display[i*LENGTH+j]);
    }
    printf("\n");
  }
}
