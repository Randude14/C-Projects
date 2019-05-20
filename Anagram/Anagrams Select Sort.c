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
 * Precondition: accepts a string. Assumed word != NULL
 * Postcondition: uses selection sort. No return needed because call by referrence
 */
void sort(char* word) {
  int len = strlen(word);

  if(len > 0) {
    int min = 0; // keeps track of index of min value
    for(int i = 1;i < len;i++) {
      for(int j = i;j < len;j++) { // find min
        if(word[min] > word[j]) {
          min = j;
	}
      }

      // swap min value with current index (i-1)
      char temp = word[i-1];
      word[i-1] = word[min];
      word[min] = temp; 
      min = i;
    }
  }
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
 * Precondition: words are in the middle of sorting and this function is used to swap two struct Words
 * Postcondition: struct words have been swapped
 */
void swap(int s1, int s2) {
  assert(s1 >= 0 && s2 >= 0 && s1 < SIZE && s2 < SIZE); // check we are in bounds
  struct Word* word1 = words[s1];        // retrieve words at s1 and s2
  struct Word* word2 = words[s2];        
  char tempWord[MAX_LENGTH];             // create temp values
  char tempSorted[MAX_LENGTH];
  strcpy(tempWord, word1->word);         // set temp values for word1's values
  strcpy(tempSorted, word1->sorted_word);
  strcpy(word1->word, word2->word);      // set word1's values to word2's
  strcpy(word1->sorted_word, word2->sorted_word);  
  strcpy(word2->word, tempWord);         // set word2's values to temp's
  strcpy(word2->sorted_word, tempSorted);     
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
 * Precondition: The words have been read in and are assumed to be assigned correctly.
 * Postcondition: Words are sorted based on their sorted letters
 */
void sortWords() {
  int min = 0; // keeps track of min index
  for(int i = 1;i < SIZE;i++) {
    for(int j = i;j < SIZE;j++) { // find min
      struct Word* word1 = words[min];
      struct Word* word2 = words[j];
      if(strcmp(word1->sorted_word, word2->sorted_word) > 0) { // sort by their sorted values
        min = j;
      }
    }

  // swap min value with current index (i-1)
  swap(i-1, min);
  min = i;
  }
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
