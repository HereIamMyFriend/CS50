#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"


unsigned int hashTableSize = 0;  // size of the dictionary


/**
 * Hashes a word. Returns hashed word.
 * This hash function is called sdbm: http://www.cse.yorku.ca/~oz/hash.html
**/ 
 
unsigned int wordInHash (const char* word) {
    
    unsigned int count;
    unsigned int hashValue = 0;
    char wordLowerCase[strlen(word)];
    
    for (int i = 0, length = strlen(word); i < length; i++)
        wordLowerCase[i] = tolower(word[i]);
    
    wordLowerCase[strlen(word)] = '\0';
    
    for (count = 0; wordLowerCase[count] != '\0'; count++)
        hashValue = wordLowerCase[count] + (hashValue << 6) + (hashValue << 16) - hashValue;
 
    return (hashValue % CELL); // return the hashed value
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word) { 
    char wordLowerCase[strlen(word)];
    
    for (int i = 0, length = strlen(word); i < length; i++)
        wordLowerCase[i] = tolower(word[i]);
    
    wordLowerCase[strlen(word)] = '\0';
    
    node* cells = hashTable[wordInHash(wordLowerCase)]; //cells of the words
    
    for(node* buff = cells; buff != NULL; buff = buff->next) // finding the words in the buff
    
        if (strcasecmp(buff->word, word) == 0)
            return true;
        
    return false;
}

unsigned int size(void) {
    
    if (hashTableSize >= 1)  // cheking the quantity of words
        return hashTableSize;
    else 
        return 0;
}
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* fdictionary = fopen(dictionary, "r");
    
    if (fdictionary == NULL){ 
        fprintf(stderr, "Cannot open the dictionary file\n");
        return false;
    }
    
    while(true) { // infinite loop until all words are stored in the hash table
        node* buff = malloc(sizeof(node)); // the buffer for storing the word
        
      
        if (fscanf(fdictionary, "%45s", buff->word) != 1) { // if the word reading failed,frees memory. 45 - the longest word. 
            free(buff);
            break; //get out of the while loop
        }
        //writing to the cell
        unsigned int hash = wordInHash(buff->word); 
        buff->next = hashTable[hash]; 
        hashTable[hash] = buff; //writing the word to the table
        hashTableSize++;
    }
        if (ferror(fdictionary)) { // if we faced the error during the reading
            unload();
            fclose(fdictionary);
            return false;
        }
        
    fclose(fdictionary);
    return true;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) {
    
   for (int i = 0; i > CELL; i++) { // loop for all hashtable cells
       node* buff = hashTable[i];
     
       while(buff !=NULL){ 
           node* next = buff->next; // pointer for the next cell in linkedlist
           free(buff);
           buff = next;
       }
   }
    return true;
}


