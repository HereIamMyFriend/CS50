/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
 //   Expecting a command-line argument for n (argc 2) and s (argc 3)... argc 1 - is the name of program
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

  //  conver string to integer by the atoi function
    int n = atoi(argv[1]);

    // if we have entered 3rd argument == [s], we have a seed for srand function. This seed is stored in argv[2]
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // Printing n times pseudorandom numbers calling a  function drand48, that transformed to int and have a LIMIN for itself
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }
    // success
    return 0;
}
