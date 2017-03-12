#!/usr/bin/env python3
import cs50
import sys

def main():
    cl_check()
    k = sys.argv[1]
    key = int(k)                    #convert from string to integer
    print("plaintext: ", end="")
    message = cs50.get_string()
    print("ciphertext: ", end="")
    cipherByCaesar(message, key)
        
def cl_check():
    if len(sys.argv) == 2 and int(sys.argv[1]) > 0:
        return
    else:
        sys.exit("Usage: ./caesar k (where k is a non-negative integer key for Caesar cipher)")
        

def cipherByCaesar(message, key):
    for char in message:
        if char.isalpha():
            code = ord(char)  # getting the integer equivalent of char
            if char.islower():
                code = (code - ord("a") + key) % 26 + ord("a")
            if char.isupper():
                code = (code - ord("A") + key) % 26 + ord("A")
            encrypted = chr(code)  # transform to the char from integer
        else:
            encrypted = char
        print("{}".format(encrypted), end="")
    print()
    
if __name__ == "__main__":
    main()