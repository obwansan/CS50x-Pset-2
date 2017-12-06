#include <stdio.h>

#define SIZE 8

void sort(int values[], int n)
{
    // set swap counter to non-zero value
    int counter = 1;
    
    // do while swap counter is greater than zero
    do 
    {
        // reset swap counter to zero
        counter = 0;
        
        // iterate through entire array
        for (int i = 0; i < n; i++)
        {
            // check if each adjacent pair are in order
            if (values[i] > values[i + 1])
            {
                // if not, swap them
                int tmp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = tmp;
                
                // increment counter
                counter++;
            }
        }
    }
    while (counter > 0);

}

int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108 };
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    }
    
    printf("\n");
    
    sort(numbers, SIZE);
    
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}
