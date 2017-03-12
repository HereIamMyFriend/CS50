#include <stdio.h>
#include <cs50.h>

#define SHOWER (192/16) // 1 minute of shower price

int main() {
    
    int period, bottles;
 
    printf("Enter an average time you spent in shower in minutes: ");
    period = GetInt();
    bottles = period*SHOWER;
    printf("%d\n", bottles);
}