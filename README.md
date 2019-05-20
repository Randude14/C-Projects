# C-Projects

Anagrams: this project dealt with reading in text files with an enourmous amount of words (150,000+) and finding the anagrams within those words. The purpose of this program was to learn to create, manipulate, and free pointers while also using string functions. The other objective was to compare and understand program run times using a slow basic sorting algarithm like select sort vs C's built in quick sort function. Was also introduced to the idea of makefiles

Black Jack game: Used as the foundation of a black jack game. This folder contains several .c and .h files that has several helper functions that can be used to simluate a game of black jack.

Tic Tac Toe: simulates a text-based tic tac toe game. Uses a 3x3 character array and can detect who has won and whether a stale mate has ocurred.

Binary Coded Decimal Printer: This program takes in a max value of 0xFFFFFFFF (4294967295) from the terminal and uses bitwise operations to obtain the Binary Coded Decimal (BCD). It then prints the BCD in an old calculator display whose numbers are 5x5 wide using a single array.

Reserved word counter: this program reads in .c and .h files and counts the words reserved by C. Afterwards, it prints out the total of each word read per file and tallies them all up to print the total of all files. As an extra, it also excludes comments and comment blocks within those files using a do while loop and several string manipulation functions.

Subwords Binary Tree: the objective of this program was to learn the basics of a binary tree and the advantages it has within certain situations. The program first reads in all the words of a .txt file and creates a binary tree with them using C's strcmp() function. It then goes down the tree starting from the root searching the subwords that each word is contained within and prints them all out.

Taylor Series Sin Calculator: builds an array whose values go from 0 degrees to 359 degrees with esimated sin values. These values are estimated with a taylor series of 4 terms. After building this array, it reads in degree values through the terminal or file to be interpolated and printed to the screen.

