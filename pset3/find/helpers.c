/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
 
int BinarySearch(int values[], int value, int low, int high) 
{  
    if (high < low)  
        return -1; // not found  
    
    int mid = low + ((high - low) / 2) ; // Divide
    
    if (values[mid] > value)
        return BinarySearch (values, value, low, mid-1);  
    else if (values[mid] < value)  
        return BinarySearch (values, value, mid+1, high);
    else
        return mid; 
}

bool search(int value, int values[], int n) // value is what to search & n is size of array
{

    /** linear search 
    if (n < 0)
        return false;
        
    for (int i = 0; i < n ; i++)
    {
        if (values[i] == value)
            return true;
    }
    return false;
    */
    
    // implementation of Binary searching algorithm as array is sorted
    
    int result = BinarySearch(values, value, 0, n);
    if (result == -1)
        return false;
    return true;
}

/**
 * Sorts array of n values.
 */
 
 
void sort(int values[], int n)
{
    //  implement an O(n^2) sorting algorithm (Selection sort)
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (values[i] > values[j])
            {
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }  
     }
    return;
}
