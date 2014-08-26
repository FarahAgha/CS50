/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"


typedef struct s_node node;

struct s_node
{
    //char *word;
    char word[LENGTH +1];
    
    struct s_node* next;
    //struct NODE* next;
};

node *hash[HASHSIZE] = {NULL};

/**
  * user defined key function
  */
  
/*unsigned int key(char* word)*/
/*{*/
/*    unsigned int index=0;*/
/*    for (int i = 0; i < strlen(word); i++) {*/
/*        index = (index << 4) + word[i];*/
/*        index = (index & 0x0fffffff) ^ ((index & 0xf0000000) >> 24);*/
/*    }*/

/*    for(int i =0; i< strlen(word); i++)*/
/*    {*/
/*        index = (127 * index + word[i]) % HASHSIZE;*/
/*    }*/
/*    return index;*/
/*}*/
unsigned int key(char* word)
{
    int first, second, third ;
    first = 0; second = 0; third = 0;
    
    first = (int) tolower(word[0])-'a';
    
    if(word[1] !='\0')
    {
        second = (int) tolower(word[1])-'a';
        if(word[2] !='\0')
        {
            third = (int) tolower(word[2])-'a';
        }
    }
    
    unsigned int index = ((first *26 *26) + (second * 26) + third ) % HASHSIZE;
    
    return index;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char copy[LENGTH+1];
   
    //make a lower case copy of it  strncpy/strcpy
    for(int i = 0 ; i<strlen(word); i++)
    {
        copy[i]= tolower(word[i]);
    }
    
    
    //replace \n with \0 in the file
    copy[strlen(word)] = '\0';
    
    unsigned int index = key(copy);
    
    if(hash[index] == NULL)
    {
        return false;
    }
    else
    {
        node* temp = hash[index];
        while(temp->next !=NULL)
        {
            if (strcmp (copy, temp->word) == 0)
                return true;
            temp = temp->next;
        }
        
        if (strcmp(copy, temp->word) == 0)
            return true;
        else
            return false;
    }
    
    //if word found return true else false 
    return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file
    FILE * fp = fopen(dictionary,"r");
    
    // file not exists
    if(fp == NULL)
    {
        return false;
    }  
    
    //read all words in the file
    char buffer[LENGTH+2]; 
    
    //fread fgets(includes new line) fgetc fscan(same as fgets fscan("%s " whitespace then no need for \n check )  
    while(fgets(buffer,LENGTH+2 ,fp)) // not use efof
    {
        //replace \n with \0 in the file
        buffer[strlen(buffer)-1] = '\0';
        
        //make a lower case
        for(int i = 0 ; i<strlen(buffer); i++)
        {
            buffer[i]= tolower(buffer[i]);
        }
        
        //copy the buffer to temp variable
        node* temp = malloc(sizeof(node));
        strncpy(temp->word, buffer, LENGTH+1);
        temp->next = NULL;
        
        int index = key(buffer);
        
        
        //insert into hash table
        if(hash[index] == NULL)
        {
            hash[index] = temp;
            SIZE++;
        }
        else
        {   
            // capture address of existing node
            node *existingnode = hash[index];
            //make emp first node i.e. insert at begining
            hash[index] = temp;
            //attach 
            temp->next = existingnode;
            SIZE++;
        }
        //free(temp);
    
    }
    
    //printf("Size %i \n",size());
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // size GLOBAL variable defined
    return SIZE;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0 ; i < HASHSIZE; i++)
    {
        node* temp = hash[i];
        while(temp !=NULL)
        {
            if(temp !=NULL)
            {
                SIZE--;
                node* anothertemp = temp;
                temp = temp->next;
                free(anothertemp);
            }
        }
    }
    
    return true;
}
