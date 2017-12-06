#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, string argv[]) 
{
    // print error message if more or less than two command-line arguments
    if (argc != 2) 
    {
        printf("Error: exactly 2 command-line arguments must be entered, the program name and cipher key.\n");
        return 1;
    }
    // print error message if the cipher key contains any non-alphabetical characters
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Error: the cipher key must contain only alphabetical characters.\n");
            return 1;
        }
    }
    // prompt for plaintext and get string
    printf("plaintext: ");
    string plaintext;
    plaintext = get_string();
    
    // declare variables (can delete when used later in program)
    int keyVal;
    int alphIndVal;
    int cipherChar;
    int j = 0;
    
    // iterate through characters in the plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        
        // go back to first keyword char when the last is reached ('wraparound')
        if (i > strlen(argv[1]) - 1) 
        {
            j = j % strlen(argv[1]);
        }
        
        // encipher only plaintext alphabetic characters
        if (isalpha(plaintext[i]))
        {
            // convert current plaintext character from ASCII to alphabetical index
            if (isupper(plaintext[i]))
            {
                alphIndVal = plaintext[i] - 65;
            }
            else if (islower(plaintext[i]))
            {
                alphIndVal = plaintext[i] - 97;
            }
        
            // convert current keyword character from ASCII to alphabetical index
            if (isupper(argv[1][j]))
            {
                keyVal = argv[1][j] - 65;
            }
            else if (islower(argv[1][j]))  
            {
                keyVal = argv[1][j] - 97;  
            }
        
            // encipher alphabetical index character using the key
            cipherChar = (alphIndVal + keyVal) % 26; 
            
            // print the enciphered char (works)
            // eprintf("%d\n", cipherChar);
            
            // convert enciphered character from alphabetical index back to ASCII
            if (isupper(plaintext[i]))
            {
                cipherChar += 65;  
            }
            else if (islower(plaintext[i]))
            {
                cipherChar += 97;
            }
            
            j++;
            
            // print the enciphered ASCII characters
            printf("%c", cipherChar);
            
        }
        // otherwise print non-alphabetic characters unchanged
        else
        {
            printf("%c", plaintext[i]);
        }

    }    
    printf("\n");
}



         