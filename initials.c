#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/**
* Implement a program that capitalises a user's name.
**/

int main(void)
{
    //Prompt the user for their name
    printf("Enter your name: ");
    
    // Assign their name to a string variable
    string s = get_string();
    
    // Print the first character of the string
    printf("%c", toupper(s[0]));
    
    // Loop through characters in the string 
    for (int i = 0, n = strlen(s); i < n; i++) 
    {
        // Print each character after a space
        if (s[i] == ' ') 
        {
            printf("%c", toupper(s[i + 1]));
        }
    }
    printf("\n");
}