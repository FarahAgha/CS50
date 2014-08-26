/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */


    
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scale infile outfile\n");
        return 1;
    }
    
    int factor = atoi(argv[1]);
    //n times the size of infile will not exceed 2^32 - 1(4294967295)
    if(factor < 1 || factor > 100 )
    {
        printf("Could not create with given factor");
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    BITMAPFILEHEADER outbf = bf;
    BITMAPINFOHEADER outbi = bi;
    
    outbi.biHeight = factor * bi.biHeight;
    outbi.biWidth = factor * bi.biWidth;
    
    int outpadding =  (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //outbi.biSizeImage = factor * bi.biSizeImage;
    outbi.biSizeImage = ( (outbi.biWidth * sizeof(RGBTRIPLE)) + outpadding ) * abs(outbi.biHeight); 
    
    outbf.bfSize = outbi.biSizeImage + 14 + 40;
    //outbf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + factor * (bf.bfSize - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER));
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    //int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) / factor) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
    
        RGBTRIPLE  array[outbi.biWidth];//*array = malloc(sizeof(RGBTRIPLE) * outbi.biWidth);
        //printf("Newly created Array %d  RGBTRIPLE %d and bWidth %d\n",sizeof((sizeof(RGBTRIPLE) * outbi.biWidth)),sizeof(RGBTRIPLE) ,sizeof(outbi.biWidth));
        int index = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            //index = 0;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            //printf("just read in %02x %02x %02x\n", triple.rgbtBlue, triple.rgbtGreen, triple.rgbtRed);
            //printf("%d -------------\n", i);
            
            for(int p = 0; p < factor; p++, index++)
            {
                array[index] = triple;
                //printf("just wrote: %02x %02x %02x\n", array[index].rgbtBlue, array[index].rgbtGreen, array[index].rgbtRed);
            }
            
            
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
            
        for(int p = 0; p < factor; p++)
        {
                // write RGB triple to outfile
                //fwrite(array, sizeof(array), outbi.biWidth, outptr);
                fwrite(array, sizeof(array), 1, outptr);
                
                //printf("just wrote: %02x %02x %02x\n", array[p].rgbtBlue, array[p].rgbtGreen, array[p].rgbtRed);
                //printf("\n");
                
                
                // add new padding to outfile
                for (int k = 0; k < outpadding; k++)
                {
                    fputc(0x00, outptr);
                    //printf("padding: \n");
                }
        }
        
        //free(array);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
