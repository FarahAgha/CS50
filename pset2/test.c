# include<cs50.h>
# include<stdio.h>
# include<string.h>
# include<ctype.h>
#include<stdlib.h>


int main( )
{
    string plaintext = GetString();
    string sequenceKeys = GetString();
    int plaintextLen = strlen (plaintext);
    int sequenceLen = strlen(sequenceKeys);
    
    int k =0 ; 
    for(int j = 0; j <  plaintextLen ; j++)
    {
        int asc = plaintext[j];
        if(isalpha(plaintext[j]))
        {
        int i = k % sequenceLen; 
        k++;
        char p = plaintext[j];
        char s = sequenceKeys[i];
        int ascP, ascS;
        
        if (isupper(p))
        {
            s= toupper(s);
            ascS = s-65;
        }
        else
        {
            s=tolower(s);
            ascS = s-97;/etc/passwd
            
        }
        
        
        
        ascP = isupper (plaintext[j]) ?  65 : 97;  // A = 65 && a = 97  
        
        if (isupper(p) &&  (asc> 64 && asc <91)) //(asc> 96 && asc <123))
        {
                asc = asc + ascS;
                asc = asc - ascP; // asc('Y'+2) = 91 - 65 = 26
                asc = (asc) % 26 +ascP; //26 % 26 + 65 = 'A'
        }
        
        else if (islower(p) &&  (asc> 96 && asc <123))
        {
                asc = asc + ascS;
                asc = asc - ascP; // asc('Y'+2) = 91 - 65 = 26
                asc = (asc) % 26 +ascP; //26 % 26 + 65 = 'A'
        }
        }
        printf("%c", asc);
    }
    printf("\n");
}
