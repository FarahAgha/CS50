# include<cs50.h>
# include<stdio.h>
# include<string.h>
# include<ctype.h>
#include<stdlib.h>


int main( int argc, string argv[])
{
    // check input at command line argument 
    if (argc != 2)
    {
        printf ("Valid Key is not entered\n");
        return 1;
    }
    // check key to be positive 
    int key = atoi (argv[1]);
    if (key < 0)
    {
        printf ("Key is not positive\n");
        return 1;
    }
    // get plain text from user    
    string plaintext = GetString();
    
    //get lenght of plain text
    int len = strlen (plaintext);
    
    for(int j = 0; j < len; j++) // loop to convert each character of string
    {
        if (isalpha (plaintext[j])) // conversion only for character   
        {   //A -65 Z 90 a97 z122
            
            int init = isupper (plaintext[j]) ?  65 : 97;  // A = 65 && a = 97  
            
            int asc= plaintext[j] + key ; 
            
            // A-Z or a-z range exceeds 
            if (! ((asc> 64 && asc <91) || (asc> 96 && asc <123)))
            {
                asc = asc - init; // asc('Y'+2) = 91 - 65 = 26
                asc = (asc) % 26 +init; //26 % 26 + 65 = 'A'
            }
            printf ("%c", asc ); // print alpha character 
        }
        else
        {
            //print special character or numeric character
            printf ("%c", plaintext[j] );
        }
       
    }
    printf ("\n");
}
