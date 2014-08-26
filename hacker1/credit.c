#include <stdio.h>
#include <cs50.h>

/**
 * Credit card number is (syntactically) valid by using Hans Peter Luhn algorithm 
 * The program generates the output as  AMEX\n or MASTERCARD\n or VISA\n or INVALID\n 
 * In case card is not in above gives output as VALID\n
 */

// ........................................... Function Prototypes .......................................................

long long GetCard();
int CardValid(long long card);
int SumEven(long long card);
int SumOdd(long long card);
int NumberOfDigits(long long card);
int GetCardPrefix(long long card,int digits);

// ........................................... Main Function  .......................................................

int main(void)
{
    // Get card information from 
    long long cardnum =  GetCard();  
    
    // Validate card 
    int cardtype = CardValid(cardnum);
    
    // show user card type
    switch (cardtype) 
    {
        case 1:
            printf("AMEX\n");
            break;
            
        case 2:
            printf("MASTERCARD\n");
            break;
            
        case 3:
            printf("VISA\n");
            break;
            
        case 4:
            printf("VALID\n");
            break;
            
        default:
            printf("INVALID\n");
            
    return 0;
    } // End of switch
    
} //End of Main


// ........................................... Function Declaration .......................................................

/**
 * @return Credit Card Number taken from the user 
 */
long long GetCard(){

    long long cardnum = 0;
    
    do
    {
        printf("Enter credit card number ");
        cardnum = GetLongLong();
        
    } while(cardnum  <= 0);
    
    return cardnum;
} // end of GetCard

/**
 * @param card is the Credit Card Number to be validated by the CardValid function
 * @return 0 for INVALID, 1 for AMEX, 2 for MASTERCARD, 3 for VISA and 4 for card Valid but type is not listed 
 */
int CardValid(long long card){
    
    //INVALID\n
    int result = 0;
   
    if (((SumOdd(card) + SumEven(card))  % 10 == 0))
    {
        int digits = NumberOfDigits(card);
        
        if (digits  <= 16 && digits  >= 13)
        {
        
            // card valid but Credit Card Type not known
            result = 4; 
            int type = GetCardPrefix(card, 1);
            
            //VISA\n 
            if (type == 4)
                result =  3;  
            
            //MASTERCARD\n    
            
            type = GetCardPrefix(card, 2);    
            
            if (type  <= 56 && type  >= 51)
                result = 2;
                
            //AMEX\n    
            if (type == 34  || type == 37)
                result = 1;
                
        }
    }
    return result;
} // End of CardValid


/**
 * multiply each digit of the @param card. add the product's digit (not the products themselves) together
 * @return sum of twice the product of each digit
 */
int SumEven(long long card)
{
    int numdigits=NumberOfDigits(card)-1;
    int sum=0,i;
    card /= 10;
    
    for (i = 0; i < numdigits; i += 2)
    {
        int digit = (int)(card  %  10); 
        
        if (digit > 4)
            sum += (2 * digit - 9);
        else  
            sum += (2 * digit);
        card /= 100;
    }
    
    return sum;
    
} // End of SumEven


/**
 * sum of the digits of the @param card that are at odd location (weren't multiplied by 2) 
 * @return sum of digits at odd location
 */
int SumOdd(long long card)
{
    int numberofdigits = NumberOfDigits(card);
    int sum = 0,i;
    
    for(i=0; i < numberofdigits; i+=2)
    {
        sum += card % 10;
        card /= 100;
    }
    return sum;
    
} // End of SumOdd


/**
 * count number of digits entered for @param card 
 * @return number of digits on the card e.g. 15 will be returned for card 378282246310005
 */
int NumberOfDigits(long long card)
{
    int digits = 0;
    
    while (card != 0)
    {
        card  /=  10;
        digits++;
    }
    
    return digits;
    
} // End of NumberOfDigits


/**
 * @param card Credit card number 
 * @param digits are number of digits to be extracted from beginning 
 * @return returned extreacted digits from the card e.g. 2 digit for card 378282246310005 is 37
 */
int GetCardPrefix(long long card , int digits)
{
    int cardDigits = NumberOfDigits(card);
    
    if(cardDigits-digits > 0)
    {
        for(int i=0; i < cardDigits-digits; i++)
            card /= 10;
        
        return card;
    }
    else
        return card;
        
} // End of GetCardPrefix

