#include<string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_BUFFER (1024) // max buffer read from file line
#define N (44)            // size of C_reserved_words

// unsorted array of the reserved words of C
const char* C_reserved_words[] = {"auto", "break", "case", "char", 
"const", "continue", "default", "do", "double", "else", "enum", 
"extern", "float", "for", "goto", "if", "inline", "int", "long", 
"register", "restrict", "return", "short", "signed", "sizeof", 
"static", "struct", "switch", "typedef", "union", "unsigned", 
"void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", 
"_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", 
"_Static_assert", "_Thread_local"};


// structure for counting key words
typedef struct fileCounter {
  int* keywords;  // keeps track of counting, each index 
                  // coressponds to index in C_reserved_words
  char* filename; // file name
} fileCounter_t;


/* Precondition: accepts a string repsenting filename to check
 * Postcondition: returns whether the file is a .c or .h file
 */
int isCFile(char* filename) {
  if(!filename)
    return 0;
  int len = strlen(filename);
  if(len < 2)
    return 0;
  return filename[len-2] == '.' && 
         (filename[len-1] == 'h' || filename[len-1] == 'c');
}


/* Precondition: accepts a string to search for
 * Postcondition: uses binary search to look for strings and 
 *                returns index if found, otherwise -1
 */
int findKeywordIndex(char* searchFor) {
  assert(searchFor);
  int first = 0;               
  int last = N-1;  
  int middle = (first+last)/2;

  while(first <= last) {
    int compare = strcmp(searchFor, C_reserved_words[middle]);
    
    if(compare == 0) {       // searchFor found, return middle
      return middle;
    } else if(compare < 0) { // searchFor less than, set last below middle
      last = middle-1;
    } else {                 // searchFor more than, set first above middle
      first = middle+1;
    }
    
    middle = (first+last)/2; // set middle between first and last
  }

  return -1;                 // return -1 if we found nothing
}


/* Precondition: accepts two strings to compare
 * Postcondition: returns integer from strcmp()
 */
int compareStrings(const void* c1, const void* c2) {
  const char* w1 = *(const char**) c1;
  const char* w2 = *(const char**) c2;
  return strcmp(w1, w2);
}


/* Precondition: accepts a line and a string to look for within the line
 * Postcondition: if checkFor is found, return index of first character
 */
int indexOf(char* line, char* checkFor) {
  assert(line);
  assert(checkFor);
  int len1 = strlen(line);
  int len2 = strlen(checkFor);
  int i, j, k, equals;

  for(i = 0;i <= len1-len2;i++) {
    k = 0;
    equals = 1;
    for(j = i;j < i+len2;j++) {
      if(checkFor[k++] != line[j]) {
        equals = 0;
        break;
      }
    }

    if(equals)
      return i;
  }

  return -1;
}


/* Precondition: accepts the line read in, a starting point, and an end point (start < end). 
 *               endString controls whether to end the line after the replaced chunk
 * Postcondition: truncates the line by removing all characters within the interval [start, end]
 *                and replaces it with a single space
 * 
 */
void deleteChunkWithSpace(char* line, int start, int end) {
  // check inputs
  int len = strlen(line);
  assert(start >= 0);
  assert(start < end);
  assert(start < len && end < len);
  int offset = end - start;
  line[start] = ' ';          // delete first space

  for(int i = start+1;i <= len-offset;i++) {
    line[i] = line[i+offset]; // move characters over
  }
}


/* Precondition: accepts the file line read, the delimiter, the keywords for the
 *               file counter, and the boolean that indicates if in code block
 * Postcondition: removes all comments and determines if the current line should
 *                be read, if so remove special characters and tally keywords
 *
 */
void processLine(char* line, char* delim, int* keywords, int* inCodeBlock) {
  assert(line); // check inputs
  assert(keywords);
  assert(inCodeBlock);
  int stop = -1;
  int start = 0; // assume we start at 0

  // check for end of code block if we are in one
  if(*inCodeBlock) {
    stop = indexOf(line, "*/")+1;
  }

  // loop until we have determined that we are out of a code
  // block or the code block continues on a different line
  do {

    // chop off if end of code block found
    if(*inCodeBlock && stop > 0) {
      deleteChunkWithSpace(line, start, stop);
      *inCodeBlock = 0; // set to 0 for out of code block
      stop = -1;        // reset stop
    }
 
    start = indexOf(line, "/*"); // check for another code block
    if(!(*inCodeBlock) && start >= 0) {
      *inCodeBlock = 1;             // set to 1 for in code block
      stop = indexOf(line, "*/")+1; // check for end of code block
    }

  } while(stop > 0);

  // if we are in a code block, no need to go any further
  if(*inCodeBlock) {
    return;
  }

  start = indexOf(line, "//"); // check for "//" comments
  if(start >= 0) {
    deleteChunkWithSpace(line, start, strlen(line)-1);
  }

  // process line after comment deletion
  char* token = strtok(line, delim);
  while(token) {
    int index = findKeywordIndex(token); // look for index
    if(index >= 0) {
      (keywords[index])++;               // inc index if found
    }
    token = strtok(NULL, delim);
  }
}


/* Precondition: accepts a filename and delimiters to count C's reserved keywords
 * Postcondition: counts the number of reserved words and returns the informtation
 *                in the form of the fileCounter structure
 */
fileCounter_t* processFile(char* filename, char* delim) {
  assert(filename);
  char readin[MAX_BUFFER]; // buffer to read in

  if(!isCFile(filename)) { // check if file is a .c or .h file first
    return NULL;
  }
  FILE* input = fopen(filename, "r");   // open file

  if(input) {
    fileCounter_t* counter = malloc(sizeof(fileCounter_t));
    counter->filename = malloc(strlen(filename)+1); // create memory for filename
    strcpy(counter->filename, filename);            // copy filename over
    counter->keywords = malloc(sizeof(int) * N);    // create memory for keywords

    for(int i = 0;i < N;i++)
      counter->keywords[i] = 0;                     // set all keyword index to 0

    int inCodeBlock = 0;                            // used to check for code blocks

    while(fgets(readin, MAX_BUFFER, input)) {       // read through file line by line
      processLine(readin, delim, counter->keywords, &inCodeBlock);
    }
    
    fclose(input);                      // close file
    return counter;                     // return fileCounter
  } else {
    printf("Could not open file: %s\n", filename);
    return NULL;                        // file failed to open, return NULL
  }
}


/* Precondition: main function of program, process argument lines passed through
 * Postcondition: process and count the total number of reserved C words to print
 *                out while also counting and printing the global count
 */
int main(int argc, char* argv[]) {
  qsort(C_reserved_words, N, sizeof(char*), compareStrings); // sort c_reserved_words
  char* delim = " (){}[]<>*,;";                               // create delimiters
 
  fileCounter_t** fileCounters = NULL;                       // array of file counters
  int SIZE = 0;                                              // keep track of size of array
 
  for(int i = 1;i < argc;i++) {
    fileCounter_t* counter = processFile(argv[i], delim);    // grab file counter

    if(counter) {                                            // if exists either create array
      SIZE++;                                                // memory or reallocate
      if(fileCounters) {
        fileCounters = realloc(fileCounters, sizeof(fileCounter_t*) * SIZE);
      } else {
        fileCounters = malloc(sizeof(fileCounter_t*));
      }
      fileCounters[SIZE-1] = counter;                        // set to end of array
    }
  }

  int globalCount[N] = {0};                                  // keep track of global counting
  
  for(int i = 0;i < SIZE;i++) {
    fileCounter_t* counter = fileCounters[i];                // grab file counter
    printf("File name is %s\n", counter->filename);          // print out file name

    for(int j = 0;j < N;j++) {
      if(counter->keywords[j] > 0) {                         // if value > 0
        printf("%s %d\n", C_reserved_words[j], counter->keywords[j]); // print out
        globalCount[j] = globalCount[j] + counter->keywords[j]; // inc global count at j
      }
    }

    // free fileCounter memory
    free(counter->filename);
    free(counter->keywords);
    counter->filename = NULL;
    counter->keywords = NULL;
    free(counter);
    fileCounters[i] = NULL;
  }

  // free array memory
  free(fileCounters);
  fileCounters = NULL;

  // PRINT GLOBAL COUNT
  printf("Global counts\n");
  for(int i = 0;i < N;i++) {
    if(globalCount[i] > 0) {
      printf("%s %d\n", C_reserved_words[i], globalCount[i]);
    }
  }
}
