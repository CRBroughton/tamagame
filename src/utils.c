#include <stdio.h>
#include <stdlib.h>

char *intToString(int number)
{
    char *result;
    // Using asprintf to convert int to char *
    if (asprintf(&result, "%d", number) == -1)
    {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return result;
}