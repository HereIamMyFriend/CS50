/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
#include <cs50.h>
#include "helpers.h"

void bubblesort(int* , int );

bool search(int value, int* values, int n) {
    
    int leftedge, rightedge, middle;
    leftedge = 0;
    rightedge = n - 1;
    while (rightedge >= leftedge) {
        middle =leftedge + (rightedge - leftedge)/2;   // always find the middle of the array
        if (n < 2)              // if length of array < 2  return false
            return false;
        if (values[middle] == value)        
            return true;
        if (values[middle] > value)// if middle value greater than value ==> ignore right side of array
            rightedge = middle  - 1;
        else        // otherwise ignore left side of array
            leftedge = middle + 1;
    }   
   return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (values[j] > values[j+1]) {
                int tmp = values[j];
                values[j] = values[j+1];
                values[j+1] = tmp;
            }
        }
    }

}
