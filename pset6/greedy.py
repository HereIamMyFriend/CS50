#!/usr/bin/env python3
import cs50

QUARTER = 25 # 25 cents
DIME = 10    # 10 cents
NICKEL = 5   # 5 cents
PENNY = 1    # 1 cent

def main():
    z = input_data()
    change = z*100
    calculation(change)
    
def input_data():
    print("How much change is owed? ",end="")
    
    while True: 
        z = cs50.get_float()
        if z > 0:
            break
        print("It's should be a positive value")
    
    return z
    
def calculation(x):
    
    qcoin, dcoin, ncoin, pcoin = 0, 0, 0, 0
    
    while x > 0:
        while x >= QUARTER:
            x -= QUARTER
            qcoin+=1
        while x >= DIME:
            x -= DIME
            dcoin+=1
        while x >= NICKEL:
            x -= NICKEL
            ncoin+=1
        while x >= PENNY:
            x -= PENNY
            pcoin+=1
            
    summary = qcoin + dcoin + ncoin + pcoin
    print("{}".format(summary))
    
if __name__ == "__main__":
    main()