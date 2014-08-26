/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include<stdio.h>
#include "helpers.h"

void radixsort(int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int array[], int n)
{
// TODO: implement a searching algorithm
return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //  implementation of an O(n) sorting algorithm

    radixsort( values,n);
return;
}

void radixsort(int values[], int n)
{
    int i, b[n], m = 0, exp = 1;
    for (i = 0; i < n; i++)
    {
        if (values[i] > m)
        m = values[i];
    }
 
    while (m / exp > 0)
    {
        // bucket [10] as sorting is of decimal places 0 to 9
        int bucket[10] = {0};
        
        for (i = 0; i < n; i++){
            bucket[values[i] / exp % 10]++;
        }
               
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
            
        for (i = n - 1; i >= 0; i--)
            b[--bucket[values[i] / exp % 10]] = values[i];
            
        for (i = 0; i < n; i++)
            values[i] = b[i];
            
        exp *= 10;
 
    }
}



