#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
   
    string name = get_string();
    if (name != NULL) {
    printf("%c", toupper(name[0])); // always print the first letter in uppercase
    for (int i = 0, n = strlen(name); i < n; i++) {
            if( name[i] == ' ' && name[i+1] != 0) // if we have "space" and it's not the end of characters sequence, all your (characters +1) goes "toupper"
                printf("%c", toupper(name[i+1]));
        }
    }
    printf("\n");
}
  
  

