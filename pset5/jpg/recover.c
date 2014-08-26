/*
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

# include<stdio.h>
#include<stdint.h>
#include <stdlib.h>

// 1 byte allocation definition
typedef uint8_t BYTE;

// size of 512 block
#define BLOCK 512 

int main (int argc , char* argv[])
{ 
    //open card file
     FILE* file = fopen ("card.raw" , "r");
 
    // condition if car file not found
    if (file == NULL)
    {
         printf ("Cannot open card.raw\n");
         return 1;
     }
 
     //buffer creation
     BYTE buffer[BLOCK]; 
 
     //file title creation
     char title[8];
 
     //image file pointer
     FILE * outfile = NULL;
 
     //file name control variable
     int jpgcount = 0 ;
 
     //Repeate till there are bytes in card file
     while (!feof (file))
     {
         //read buffer
         fread (buffer , sizeof (buffer) , 1 , file);
        
         //if buffer is header
         if ( (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] ==0xff && buffer[3] ==0xe0) 
             || (buffer[0] == 0xff && buffer[1] ==0xd8 && buffer[2] ==0xff && buffer[3] ==0xe1))
         {
             // if there is an existing jpg file
             if (outfile != NULL)
             {
                 fclose (outfile);
             } 
             
             //construct title of the jpg file 
             sprintf (title ,"%03d.jpg" , jpgcount);
             
             //create jpg file
             outfile = fopen (title , "a");
 
             //increase count for next title
             jpgcount++;
 
             //if new jpg file is not created
             if (outfile== NULL)
             {
                 printf ("Cannot create %s file.. Exiting now...\n" ,title);
                return 1;
            }
 
            //write header buffer to jpg file
            fwrite (&buffer , sizeof (buffer) ,1 ,outfile);
 
           } // end of buffer's if
           else
           {
                // if jpg file exist 
                if (outfile != NULL)
                {
                    // and card file does not have data 
                    if (feof (file))
                    {
                        fclose (outfile);
                    }
                    else
                    {
                        //write buffer to already existed file
                        fwrite (&buffer , sizeof (buffer) ,1 ,outfile);
                    } 
                }
            } // end of buffer's else condition
        } // end of while
 
 return 0;
}
