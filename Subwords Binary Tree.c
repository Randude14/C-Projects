#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct wordList { 
  char* word;                 // node word
  char** list;                // list of words this node is a part of
  int N;                      // size of list 
  struct wordList* lessword;  // word less than  
  struct wordList* greatword; // word greater than 
} wordList_t; 
 
/* Precondition: takes in a node of a binary tree and the word to insert
 * Postcondition: recursively goes through the binary tree until it finds an empty branch
 *                NOTE: sorts based on strcmp
 */
void insert(wordList_t** node, char* word) {
  assert(word);

  if(*node == NULL) {
    *node = (wordList_t*)malloc(sizeof(wordList_t));
    int len = strlen(word);                        // get length of word
    (*node)->word = (char*)malloc(len+1);          // grab memory               
    strcpy( (*node)->word, word );                 // copy word over
    (*node)->lessword = (*node)->greatword = NULL; // set lessword to NULL
    (*node)->list = NULL;                          // set greatword to NULL
    (*node)->N = 0;                                // set N to 0
  } else {
    int compare = strcmp(word, (*node)->word); // compare words
    if(compare > 0) {                          // if greater then
      insert( &(*node)->greatword, word );     // check greatword
    } else if(compare < 0) {                   // if less then (this is here in case of duplicates)
      insert( &(*node)->lessword, word );      // check lessword
    }
  }
}

/* Precondition: takes in a node to be freed of it's memory
 * Postcondition: recursively goes through the binary tree freeing 
 *                memory and setting nodes to NULL
 */
void clean_up(wordList_t* node) {
  if(node) {                       // if node exists
    clean_up( node->lessword );    // clean up lessword
    clean_up( node->greatword );   // clean up greatword
    free(node->word);              // free word memory
    free(node->list);              // free list memory
    node->word = NULL;             // set nodes variables to NULL or 0
    node->list = NULL;
    node->lessword = node->greatword = NULL;
    node->N = 0;
    free(node);                    // free node memory
    node = NULL;
  }
}

/* Precondition: takes in a node and word to be searched for
 * Postcondition: recursively goes through the binary tree until it either
 *                reaches the end or finds the word
 */
wordList_t* search(wordList_t* node, char* word) {
  assert(word);
  if(node == NULL) { 
    return NULL;                           // return NULL if we have reached the end
  }
  int compare = strcmp(word, node->word);  // compare words

  if(compare == 0) {
    return node;                           // return node if words are equal
  } else if(compare > 0) {
    return search(node->greatword, word);  // go right if word is larger
  } else {
    return search(node->lessword, word);   // go left if word is smaller
  }
}

/* Precondition: accepts a word to be copied to, the original word, the start index,
 *               and the length of the substring (copies from start to start+len)
 * Postcondition: returns whether the result is possible and if so the sub portion 
 *                of that word is copied
 */
int substring(char* copyTo, char* word, int start, int len) {
  assert(copyTo);                         // check our inputs
  assert(word);
  assert(len > 0);
  assert(start >= 0);
  if(start+len > strlen(word)) {          // check that we don't go out of bounds
    return 0;
  }
  int index = 0;                          // keeps track of copyTo's index
  for(int i = start;i < start+len;i++) {  // go from start to start+len
    copyTo[index] = word[i];              // copy character over
    index++;                              // increment index
  }
  copyTo[index] = '\0';                   // cap off string
  return 1;                               // return success
}

/* Precondition: accepts a node and word to be added to that nodes list
 * Postcondition: word is added to that nodes list
 */
void addWord(wordList_t* node, char* word) {
  assert(node);                                      // check node isn't NULL
  assert(word);                                      // check word isn't NULL
  (node->N)++;                                       // increment N

  if(node->N > 1) {                                  // if not the first word
    node->list = (char**)realloc(node->list, sizeof(char*) * node->N); // reallocate memory
  } else {                                           // first word added
    node->list = (char**)malloc(sizeof(char*));      // allocate memory
  }
  node->list[ node->N -1 ] = word;                   // set last index to word
}

/* Precondition: takes in a node to be searched
 * Postcondition: recursively travels through the binary tree and for each
 *                node splits its word into subwords to find
 */
void searchForSubwords(wordList_t* root, wordList_t* node) {
  if(!root || !node) {                            // stop if root or node doesn't exist
    return;
  }
  char* word = node->word;                        // grab word from node
  int wordLen = strlen(word);                     // grab word length
  char subword[wordLen];                          // create temp subword
  int i;                                          // keeps track of index

  for(int len = 3;len < wordLen;len++) {          // create subword lengths starting from 3
    i = 0;                                        // init index
    while(substring(subword,word,i,len)) {        // create substring if possible
      wordList_t* result = search(root, subword); // search for subword
      if(result) {                                // if result found
        addWord(result, word);                    // add node word to result
      }
      i++;                                        // go to next index
    }
  }
  searchForSubwords(root, node->greatword);       // search greatword
  searchForSubwords(root, node->lessword);        // search lessword
}

/* Precondition: accepts two variables of unknown types
 * Postcondition: strings are casted from pointers and compared
 */
int compareStrings(const void* v1, const void* v2) {
  const char* s1 = *(const char**) v1; // cast and dereference to get values
  const char* s2 = *(const char**) v2;
  return strcmp(s1, s2);  // use strcmp() to find difference
}

/* Precondition: takes in a node to be printed
 * Postcondition: recursively travels through the binary tree and prints out all the
 *                nodes, traversing IN-ORDER whose N > 0 - I.E. words that node is a part of
 */
void print(wordList_t *node) {
  if (node) {  
    print(node->lessword);
    if(node->N) {  
      printf("%s [%d]\n",node->word,node->N); 
      qsort(node->list, node->N, sizeof(char*), compareStrings); // sort before printing
      for (int i = 0;i < node->N;i++) 
        printf("   %s\n",node->list[i]); 
    } 
    print(node->greatword); 
  } 
} 

/* Precondition: accepts the arguments
 * Postcondition: loads the file, fills in the binary tree and finds all subwords for each node
 *                prints out those values, and finally clears all system memory
 */
int main(int argc, char** argv) {
  char* filename = "words.txt";       // set filename
  wordList_t* root = NULL;            // represents root of binary tree
  FILE *read = fopen(filename, "r");  // attempt to open file

  if(read) {                          // file was loaded
    char input[1024];          
    while(!feof(read)) {              // check if we reached the end
      fscanf(read, "%s", input);      // read in next token
      insert(&root, input);           // insert word into tree
    }
    fclose(read);                     // close file
  } else { 
    printf("%s failed to load or does not exist.\n", filename);
  }

  searchForSubwords(root, root);   // search for subwords starting at root
  print(root);                     // print binary tree
  clean_up(root);                  // delete binary tree
  root = NULL;                     // set root to NULL
  return 0;
}
