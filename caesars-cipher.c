#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, string argv[]) 
{
    // validate command-line arguments (must be 2)
    if (argc != 2) 
    {
        printf("Error: exactly 2 command-line arguments must be entered, the program name and cipher key integer.\n");
        return 1;
    }
    // Turn cipher key into an integer (is a string in argv[])
    int k = atoi(argv[1]);
    
    // prompt for plaintext and get string
    printf("plaintext: ");
    string s = get_string();
    
    // declare variable to use in for loop (get an error if declare it in the assignment)
    int alphInd;
    
    // output "ciphertext:" before loop so it doesn't repeat (don't know how to put chars in an array/string to print)
    printf("ciphertext: ");
    
    // iterate through the characters in plaintext string 
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // encipher alphabetic characters
        if (isalpha(s[i]))
        {
            // convert plaintext character from ASCII to alphabetical index
            if (isupper(s[i]))
            {
                alphInd = s[i] - 65;
            }
            else if (islower(s[i]))
            {
                alphInd = s[i] - 97;
            }
            // encipher alphabetical index character using the key
            int cipherChar = (alphInd + k) % 26;

            // convert enciphered character from alphabetical index back to ASCII
            if (isupper(s[i]))
            {
                cipherChar += 65;
            }
            else if (islower(s[i]))
            {
                cipherChar += 97;
            }
            //print the enciphered ASCII characters
            printf("%c", cipherChar);
        }
        // print non-alphabetic characters unchanged
        else
        {
            printf("%c", s[i]);
        }
    }

    printf("\n");
    return 0;
}