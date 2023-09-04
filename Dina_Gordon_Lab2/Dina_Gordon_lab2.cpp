#include <stdlib.h>
#include <stdio.h>
//#define scanf_s scanf
 

int main()
{
    // Seed the random number generator
    srand(1);
    // Specify the original array size, stored in variable n1.
    printf("Enter original array size: ");
    int n1 = 0;

    scanf("%d", &n1); // using scanf_s(), the secure version of scanf()
    // Create a new array called a1 of n1 ints
    int* a1 = (int*) malloc(sizeof(int)*n1);
    int i;
    for (i = 0; i < n1; i++)
    {
        // Set each value in a1 to a random int < 100
        a1[i] = rand() % 100;
        // Print each element out (to make sure things look right)
        printf("%d ", a1[i]);
    }
    // User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2 = 0;
    scanf("%d", &n2); // using scanf_s(), the secure version of scanf()
    // Dynamically change the array a1 to size n2
    a1 = (int*) realloc(a1, sizeof(int)*n2); // Resize the array
    // If the new array is a larger size, set all new members to 0.
    // so we don’t have uninitialized array members.

    if (n2 > n1)
    {
        for (int j = n1; j < n2; j++)
        {
            a1[j] = 0;
        }
    }
    for (i = 0; i < n2; i++)
    {
        // Print out each element of the new array
        printf("%d ", a1[i]);
    }

    printf("\n");
    // We're done with the array.
    free(a1);
    printf("\nEnter new array size: ");
    int n3 = 0;
    scanf("%d", &n2);

    return 0;
}