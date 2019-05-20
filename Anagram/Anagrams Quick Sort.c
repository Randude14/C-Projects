#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1024 // max size of strings accepted
#define N 400000        // max # of strings read in. does NOT represent actual size


struct Word {
  char* sorted_word; // stores the sorted letters
  char* word;   // stores the word
};

// init global variables

// array of struct Words that will be sorted based on the sorted letters
struct Word* words[N];

// represents the number of strings read in
int SIZE = 0; 

/*
 * Precondition: accepts the input of the screen or file
 * Postcondition: returns whether -1 was read in
 */
int reachEnd(char input[]) {
  int len = strlen(input);
  if(len == 2) {
    return input[0] == '-' && input[1] == '1';
  }
  return 0;  
}

/*
 * Precondition: void pointers are passed to be cast down
 * Postcondition: the char values are retrieved and compared
 */
int compareLetters(const void* v1, const void* v2) {
  char c1 = *(char*) v1; // cast and derefference to get values
  char c2 = *(char*) v2;
  return c1 - c2;        // compare by finding their difference
}

/* 
 * Precondition: accepts a string. Assumed word != NULL
 * Postcondition: uses qsort. No return needed because call by referrence
 */
void sort(char* word) {
  qsort(word, strlen(word), sizeof(char), compareLetters);
}

/*
 * Precondition: takes in the input to create an entry
 * Postcondition: entry is created for the list that contains the sorted letters at the
 *                the beginning and the original order is at the end.
 */
void createEntry(char* input) {
  char sorted[MAX_LENGTH];  // allocate memory
  strcpy(sorted, input);              // copy data over
  sort(sorted);                       // sort letters

  struct Word* word = (struct Word*)malloc(sizeof(struct Word)); // allocate memory for new entry
  word->word = malloc(sizeof(char) * MAX_LENGTH); // allocate memory
  word->sorted_word = malloc(sizeof(char) * MAX_LENGTH); // allocate memory
  strcpy(word->word, input); // add sorted at beginning to put anagrams together
  strcat(word->sorted_word, sorted);    // add original word at end for storing
  words[SIZE] = word;
  SIZE++;
}

/*
 * Precondition: word is assumed to contain the its sorted letters at the beginning and the
 *               original word at the end. Word length is the original word's length times 2
 * Postcondition: the original word at the end is retrieved and returned. Value must be freed
 */
char* getOriginalWord(int index) {
  assert(index >= 0 && index < SIZE);           // check we are in bounds
  struct Word* word = words[index];             // retrieve word in index
  char* og = malloc(sizeof(char) * MAX_LENGTH); // allocate memory
  strcpy(og, word->word);                       // copy word over
  return og;
}

/*
 * Precondition: word is assumed to contain the its sorted letters at the beginning and the
 *               original word at the end. Word length is the original word's length times 2
 * Postcondition: the sorted letters are retrieved and returned. Value must be freed
 */
char* getSortedWord(int index) {
  assert(index >= 0 && index < SIZE);               // check we are in bounds
  struct Word* word = words[index];                 // retrieve value at index
  char* sorted = malloc(sizeof(char) * MAX_LENGTH); // allocate memory
  strcpy(sorted, word->sorted_word);                     // copy word over
  return sorted;
}

/*
 * Precondition: accepts two indexes and compares the values at those indexes
 * Postcondition: returns whether the two words are anagrams based on
 *                their length and if they have the same letters
 */
int areAnagrams(int index1, int index2) {
  char* sorted1 = getSortedWord(index1); // retrieve sorted word @ index1
  char* sorted2 = getSortedWord(index2); // retrieve sorted word @ index2
  
  int areAnagrams = strcmp(sorted1, sorted2) == 0; // strcmp returns 0 if strings are equal
  free(sorted1);
  free(sorted2);
  return areAnagrams;
}

/*
 * Precondition: void pointers are passed to be cast down
 * Postcondition: the struct Word values are retrieved and compared
 */
int compareStructs(const void* v1, const void* v2) {
  const struct Word* word1 = *(const struct Word**) v1; // cast and derefference to get values
  const struct Word* word2 = *(const struct Word**) v2;
  return strcmp(word1->sorted_word, word2->sorted_word);          // compare sorted values
}


/*
 * Precondition: The words have been read in and are assumed to be assigned correctly.
 * Postcondition: Uses qsort. Words are sorted based on their sorted values.
 */
void sortWords() {
  qsort(words, SIZE, sizeof(struct Word*), compareStructs);
}


/*
 * Precondition: The words have already been read in and sorted based on their sorted letters
 *               so we can easily compare them
 * Postcondition: The anagram words have been printed out in pairs and the total number
 *                anagrams is posted at the very end
 * NOTE: sortWords() must be called beforehand for method to work correctly
 */
void printoutAnagrams() { 
  int numAnagrams = 0;
  int start = -1;
  int stop = -1;
  for(int i = 0;i < SIZE-1;i++) {
    if(areAnagrams(i, i+1)) { // check if anagrams
      start = (start > -1) ? start : i; // don't change start if it is already set
    } else if(start > -1) { // set stop if start has been set. I.E. we have found anagrams
      stop = i;
    }
    if(start > -1 && (stop > -1 || i == SIZE-2)) {
      stop = (stop > -1) ? stop : i+1; // check if we are at the end or not
      for(int j = start;j <= stop;j++) {
        char* og = getOriginalWord(j); // grab original word
        printf("%s ", og); 
        free(og); // free og memory
      }
      printf("\n");
      int add = stop - start; // add the # of anagrams
      numAnagrams += add;
      start = -1; // reset
      stop = -1;  // reset
    }
  }

  printf("%d found\n", numAnagrams);
}

/*
 * Precondition: reads in either through the terminal or file
 * Postcondition: has finished reading in the input and printed out
 *                the number of anagrams within the terimnal or file
 */
int main(int argc, char* argv[]) {
  char input[MAX_LENGTH];
  scanf("%s", input);
  while(reachEnd(input) == 0 && SIZE <= N) {
      createEntry(input);       // create entry in list
      scanf("%s", input);       // read in next input
  }
  sortWords();                  // sort words
  printoutAnagrams();           // print out anagrams and # of them
  for(int i = 0;i < SIZE;i++) { // free all memory
    free(words[i]->word);
    free(words[i]->sorted_word);
    free(words[i]);
  }
  return 0; 
}