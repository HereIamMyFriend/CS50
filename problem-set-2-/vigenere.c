#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void cipherbyVigenere(char* , char*  );

int main(int argc, string argv[]) {
    string keyword;
    if (argc != 2) {                                                                 // according to the task user have to enter commad-line argument
        printf (" Missed comand-line argument \n");
        return 1;
    }
    keyword = argv[1];
    for (int i = 0, keylen = strlen(argv[1]); i < keylen; i ++ ){                    // It's should be an alphabetical comand-line argument == keyword
            if (!isalpha(keyword[i])) {
                printf("Incorrect input");
                return 1;
            }
    }
        printf ("plaintext: ");
        string expression = get_string();                                             // get string from user
        printf("ciphertext: ");
        cipherbyVigenere(expression, keyword);                                        // cipher function
    return 0;
}

void cipherbyVigenere (char* symb, char* key) {
    int expressionlength = strlen(symb);
 //   int keylength = strlen(key);
        for (int i = 0, j = 0 ; i < expressionlength; i++) {                           //going over the entire sequence of string
            if (j < expressionlength)                                                  // j is a counter fo key length.
                j = j%strlen(key);                                                     // cycle for keylength. it should be a sequence of key that equals to expressionlength  (!(keylength > expressionlength))
            if (!isalpha(symb[i]))                                                     // if current symbol is non-alphabetical, program miss it without changes
                printf("%c", symb[i]);
            else if (isupper(symb[i]))  {                                              // if current symbol is uppercase, it have to be changed by corresponding keyword
                printf("%c", (((symb[i] - 'A') + (toupper(key[j]) - 'A')) % 26) + 'A');// 26 is for amount of letters in english language, symb[i] - 'A' used to get the distance btw current symbol and 'a'
                j++;                                                                   //(toupper(key[j]) - 'A')  toupper function used to handle with situatoion when symb[i]=K and key[j] = k
            }                                                                          // %26 is the same as char c = (c >= 'A' && c>= 'Z')
            else if (islower(symb[i]))  {
                printf("%c", (((symb[i] - 'a') + (tolower(key[j]) - 'a')) % 26) + 'a');
                j++;
            }
        }
        printf("\n");
}
