#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bmp.h"

#define BMPOFFBITS  54

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4 && (!isdigit(argv[1]))){
        fprintf(stderr, "Usage: ./copy N - must be an integer, infile, outfile\n");
        return 1;
    }
    int n = atoi(argv[1]);

    if (n <= 0 || n > 100) {
        fprintf(stderr, "N - should be  from 1 till 100\n");
        return 1;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // File "in" parameters
    int fileInPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int fileInWidth = bi.biWidth;
    int fileInHeight = abs(bi.biHeight);
    int fileInValue = fileInWidth * 3 + fileInPadding;
    // Update width and height witn new size
    bi.biWidth *= n;
    bi.biHeight *= n;
    
    //Update padding for new file
    int fileOutPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Update BITMAPINFO, BITMAPFILE -HEAREDs
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + fileOutPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);         // write outfile's BITMAPFILEHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);        // write outfile's BITMAPINFOHEADER

    for (int i = 0; i < fileInHeight; i++) {     // verticaly positions
          for (int k = 0; k < n; k++) { // iterate n times for adding new bits to each old bits
               fseek(inptr, BMPOFFBITS + fileInValue * i , SEEK_SET); // move pointer  though the RGB bits
               for (int j = 0; j < fileInWidth; j++) { // horizontaly positions
                    RGBTRIPLE triple;  
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);      // reading current RGB triple from the file;
                    for (int s= 0; s < n; s++) {       // adding new bits to the file n times
                         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
               }
        //  add padding
               for (int p = 0; p < fileOutPadding; p++) {
                    fputc(0x00, outptr);
               }
          }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
