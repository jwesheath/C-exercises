#include "cs50.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[])
{
    // check that one and only one command line argument is provided
    if (argc != 2)
    {
        printf("This program requires a single alphabetical string "
               "as a command line argument.\n");
        return 1;
    }
    else
    {        
        // assign command line argument to key and get its length
        string key = argv[1];
        int keylength = strlen(key);
        
        // stop program if command line argument contains more than letters
        int validkey = 1;
        
        for (int i = 0, n = keylength; i < n; i++)
        {
            if (!isalpha(key[i])) 
            {
                validkey = 0;
            }
        }
        
        if (validkey == 0)
        {
            printf("This program requires a single alphabetical string "
                   "as a command line argument.\n");
            return 1;    
        }
        else
        {
            // prompt user for a string
            printf("Input phrase for vigenere encryption: ");
            string plaintext = GetString();
            
            // initialize key position variable to 0
            int keypos = 0;
            
            // get length of plaintext string
            int length = strlen(plaintext);
            
            //  declare integer arrays to be populated later
            int keynums[keylength];
            int alphanums[strlen(plaintext)];
            int asciinums[strlen(plaintext)];
            
            // get standard 26 numbers for the letters in the key
            for (int i = 0, n = keylength; i < n; i++)  
            {
                if (isupper(key[i]))  keynums[i] = key[i] - 'A';
                if (islower(key[i]))  keynums[i] = key[i] - 'a';
            }
          
            // convert plaintext string into standard 26 numbers of alphabet
            // and rotate according to key
            for (int i = 0, n = length; i < n; i++)
            {
                if (isalpha(plaintext[i]))
                {
                    if (isupper(plaintext[i]))
                    {
                        alphanums[i] = (plaintext[i]-'A'+keynums[keypos])%26;
                    }
                    else if (islower(plaintext[i]))
                    {
                        alphanums[i] = (plaintext[i]-'a'+keynums[keypos])%26;
                    }
                    
                    // update key position
                    if (keypos < keylength - 1)  keypos++;
                    else keypos=0;
                }
                else  
                {
                    // convert special characters to ASCII by assigning to ints
                    alphanums[i] = plaintext[i];
                }
            }
        
            // convert standard alphabet numbers to ASCII numbers
            for (int i = 0, n = length; i < n; i++)
            {
                if (alphanums[i] <= 26)
                {
                    if (isupper(plaintext[i]))
                    {
                        asciinums[i] = alphanums[i] + 65;
                    }
                    else if (islower(plaintext[i]))
                    {
                        asciinums[i] = alphanums[i] + 97;
                    }
                }
                // leave special characters as ASCII numbers
                else asciinums[i] = alphanums[i];
            }
    
            // print encrypted string by printing ASCII numbers as characters
            for (int i = 0, n = length; i < n; i++)
            {   
                printf("%c", asciinums[i]);    
            }
            printf("\n");
        }
    }     
}
