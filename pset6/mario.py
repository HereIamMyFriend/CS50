#!/usr/bin/env python3
import cs50

def main():
    n = get_height()  # gettint the height of the triangle
    output(n)    # printing the triangle
    
def get_height():

    while True:
        print("Enter the height: ", end="")
        n = cs50.get_int()
        if n >= 1 and n <= 23:
            break
    
    return n
    

def output(n):
    
    for line in range(n):     #height of the triangle
        for space in range(n-line-1):  #spaces for the printing the left triangle
            print(" ", end="")
            
        for tag in range(line+1):           #printing the left triangle
            print("#", end="")
            
        print("  ", end="")                 #gap between triangles
        
        for tag in range(line+1):           #printing the right triangle
            print("#", end="")
            
        print()

if __name__ == "__main__":
    main()