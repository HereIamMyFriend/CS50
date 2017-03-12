#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


void cipherbyCaesar(char* , int );

int main(int argc, string argv[]) {
    int key = 0;
    if ((argc != 2) || atoi(argv[1]) < 0 ) { // user would enter a command-line argument, if > 1(exception for program name) arguments or nothing = error
        printf ("Usage: ./caesar k (where k is a non-negative integer key for Caesar cipher)\n");
        return 1;
    }
    else {
         key = atoi(argv[1]);                                         // converts string to integer
    }
        printf ("plaintext: ");
        string expression = get_string();                             // get string from user
        printf("ciphertext: ");
        cipherbyCaesar(expression, key);    
    return 0;
}


void cipherbyCaesar (char* symb, int k) {
    for (int i = 0, length = strlen(symb); i < length; i++) {  
                                                                    // 26 is the number of letters in english alphabet
        if (isalpha(symb[i]) && isupper(symb[i]))                   //cycle for encryption uppercase letters
            printf("%c", (symb[i] - 'A' + k) % 26 + 'A');
            
        if (isalpha(symb[i]) && islower(symb[i]))                   //cycle for encryption lowecase letters
            printf("%c", (symb[i] - 'a' + k) % 26 + 'a');
            
        if (!isalpha(symb[i]))                                      // cycle for missing non-alphabetical characters
            printf("%c", symb[i]);
  
    }
        printf("\n");
    
}