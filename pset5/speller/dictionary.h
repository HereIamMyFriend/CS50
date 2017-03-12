/**
 * Declares a dictionary's functionality.
 */
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>

#define CELL 15000 // the number of cells in the hash table
#define LENGTH 45 // lenght of the longest word



typedef struct node {
    char word[LENGTH+1]; //length of the word + 1 bit for zero symbol
    struct node* next; //hash table
} node;

node* hashTable[CELL];    // dictionary hashtable (linkedlist)
    /*
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
