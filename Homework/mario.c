#include <stdio.h>
#include <cs50.h>


int main()
{
    int height, lines, space;
    
    do {
    printf("Enter the height: ");           // loop for entering integer data from 0 to 23
     height = GetInt();
    }
    while (height < 0 || height > 23);
    
   for (lines = 0; lines < height; lines++){         //loop for drawing lines
        for (space = height - lines - 1; space > 0; space--){ //   loop to format  "#" to the right edge
            printf(" ");
        }
        for (int i = 1; i <= (lines + 1); i++){
            printf("#");
        }
        printf("  "); /// gap between piramids
                
        for (int q = 0; q <= lines; q++){  //loop for printing the second piramid
                printf ("#");
        }
        printf("\n");
    }
    return 0;
}
