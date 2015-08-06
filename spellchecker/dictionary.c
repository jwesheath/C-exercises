#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// define the dword struct
typedef struct dword {
    char* word;    
    struct dword* next;
} dword;

// define the number of heads for the hash table,
// this affects efficiency
#define HEADNUM 1500

// the hash table
dword* heads[HEADNUM];

// word count
int count = 0;

/**
 * Returns true if word is in dictionary else false.
 */

bool check(const char* word)
{
    // pass function argument word to checkword
    char checkword[strlen(word)]; 
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        checkword[i] = tolower(word[i]);
    }
    checkword[strlen(word)] = '\0';
    
    // hash the word to check
    int hashindex = hash(checkword);
    
    // load the head from the appropriate bin
    dword* curr = heads[hashindex];
    
    // traverse linked list "bin" and return true if checkword found
    while (curr != NULL)
    {
        if(strcmp(curr->word, checkword) == 0) 
        {
            return true;
        }
        curr = curr->next;  
    } 
    
    // return false if word not found
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the dictionary file
    FILE* dic = fopen(dictionary, "r");
    
    // create a buffer into which to load words from the dictionary
    char word[LENGTH+1];
    
    // loop over dictionary words until end of file
    while(fscanf(dic, "%s", word) != EOF)
    {
        // hash the word
        int hashindex = hash(word);
        
        // create a new dword with the word loaded from dictionary
        dword* newword = malloc(sizeof(dword));
        newword->word = malloc(strlen(word) + 1);
        strcpy(newword->word, word);
        newword->word[strlen(word)] = '\0';
        
        // insert new dword into the hash table
        if (heads[hashindex] == NULL)
        {
            heads[hashindex] = newword;
            heads[hashindex]->next = NULL;
            count++;
        }
        else
        {
            dword* curr = heads[hashindex];
            heads[hashindex] = newword;
            heads[hashindex]->next = curr;
            count++;
        }
    }
    
    // close the file
    fclose(dic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // declare pointer one time to be used in loop many times
    dword* curr;
    
    // loop over each letter/head
    for (int i = 0; i < 1500; i++)
    {
        // declare next as the current head
        dword* next = heads[i];
        
        // walk through linked list and free all nodes
        while (next != NULL)
        {
            curr = next;
            next = curr->next;
            free(curr->word);
            free(curr);
        }    
    }
    return true;
}

/**
 * Hash function - words are summed, divided by the number of heads
 * in the hash table, and the remainder is returned as the hash
 */
int hash(char* hashword)
{
    int length = strlen(hashword);
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += hashword[i];
    }
    
    return sum % HEADNUM;
}
