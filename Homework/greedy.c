#include <stdio.h>
#include <cs50.h>
#include <math.h>
// value of coins
#define QUARTER 25     //25 cents
#define DIME 10         //10 cents
#define NICKEL 5        //5 cents   
#define PENNY 1         //1 cent

int main () {
    
    int qcoin, dcoin, ncoin, pcoin, sum;
    qcoin = dcoin = ncoin = pcoin = 0;  // counter for number of coins
    float x;
    
    do {                  // loop for checking input values
    printf ("How much change is owed? ");     
    x = GetFloat();
    }
    while (x < 0);
    
    int change = round(x * 100);        // transform dollars to cents
    
    while (change > 0) {        
        while (change >= QUARTER) {
            change = change - QUARTER;
            qcoin++;
        }
        while (change >= DIME) {
            change = change - DIME;
            dcoin++;
        }
        while (change >= NICKEL) {
            change = change - NICKEL;
            ncoin++;
        }
        while (change >= PENNY) {
            change = change - PENNY;
            pcoin++;
        }
    }
    sum = qcoin + dcoin + ncoin + pcoin;
    printf ("%d\n", sum);       // output data
}