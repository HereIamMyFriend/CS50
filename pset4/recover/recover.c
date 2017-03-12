#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;
#define FATBLOCK 512

int main (int argc, char* argv[]) {
    
    if (argc !=2) {
        fprintf(stderr, "Incorrect usage! Enter the name of a forensic image from which to recover JPEGs\n");
        return 1;
    }
    
    FILE* inputf = fopen(argv[1], "r");
    
    if (inputf == NULL) {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }
    
    int countname = 0;          // variable for different  jpeg names;
    FILE* img;                       // create variable called img of type FILE
    while (true)  {                      //endless loop, until EOF is not found
    BYTE buffer[FATBLOCK] = {};         // buffer with sizeof 512
    
        for(int i = 0; i < FATBLOCK; i++){      //Lets find JPEG file 
            if (feof(inputf)) {             //  end of file is herein? - exit the process
                fclose(inputf);             // closing files
                if (img != NULL) {          // close img file if  it was open
                    fclose(img);
                }
                return 0;
            }
        fread(&buffer[i], sizeof(BYTE), 1, inputf); // reading file bytes one by one;  
        }
            
        if(buffer[0] == 0xff && buffer[1] == 0xd8 &&      //  searching for the first bites of jpg
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
    
            char filename[10];     //  an array for storing the filename
            sprintf(filename, "%03i.jpg", countname);
            countname++;  // increment counter for new filename next iteration
            img = fopen(filename, "w");
            
            if (img == NULL) {
                    fclose(inputf);
                    fprintf(stderr,"FAILURE!\n");
                    return -1;
                 }
            fwrite(&buffer[0], FATBLOCK * sizeof(BYTE), 1, img);
        }
        else if (img != NULL) { // continue to write data in file if it still opened
            fwrite(&buffer[0], FATBLOCK * sizeof(BYTE), 1, img);
        }
   }
   fclose(inputf);
   return 0;
}
   
   
    