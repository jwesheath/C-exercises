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
        printf("This program requires a single numerical string "
               "as a command line argument.\n");
        return 1;    
    }
    else
    {
        // assign command line argument to integer key variable
        int key = atoi(argv[1]);

        // prompt user for input
        printf("Input phrase for caesar encryption: ");
        string plaintext = GetString();
        
        // get length of input and declare two arrays
        int length = strlen(plaintext);
        int alphanums[strlen(plaintext)];
        int asciinums[strlen(plaintext)];
        
        // convert plaintext string into standard 26 numbers of alphabet
        // and rotate according to key
        for (int i = 0, n = length; i < n; i++)
        {
            if (isalpha(plaintext[i]))
            {
                if (isupper(plaintext[i]))
                {
                    alphanums[i] = ((plaintext[i] - 65) + key) % 26;
                }
                else if (islower(plaintext[i]))
                {
                    alphanums[i] = ((plaintext[i] - 97) + key) % 26;
                }
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
                if (isupper(plaintext[i]))  asciinums[i] = alphanums[i] + 65;
                if (islower(plaintext[i]))  asciinums[i] = alphanums[i] + 97;
            }
            // ceave special characters as ASCII numbers
            else asciinums[i] = alphanums[i];
        }
    
        // print the encrypted string by printing ASCII numbers as characters
        for (int i = 0, n = length; i < n; i++)
        {   
            printf("%c", asciinums[i]);    
        }
        printf("\n");   
    }
}
