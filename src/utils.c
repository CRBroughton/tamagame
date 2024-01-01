#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/raylib.h"
#include "include/constants.h"

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

char* floatToString(float value, int precision) {
    // Calculate the size needed for the string
    int size = snprintf(NULL, 0, "%.*f", precision, value);

    // Allocate memory for the string
    char *result = (char *)malloc(size + 1);

    // Use sprintf to convert the float to a string with specified precision
    sprintf(result, "%.*f", precision, value);

    return result;
}

#define EPSILON 1e-6  // Adjust this epsilon value based on your precision requirements
int isFloatDivisible(float num, float divisor) {
    // Check if divisor is not zero to avoid division by zero
    if (fabs(divisor) < EPSILON) {
        printf("Error: Division by zero.\n");
        return 0;  // You can handle this error condition as needed
    }

    // Calculate the remainder using fmod function
    float remainder = fmod(num, divisor);

    // Check if the remainder is within the acceptable range of epsilon
    if (fabs(remainder) < EPSILON) {
        return 1;  // The float is divisible by the number
    } else {
        return 0;  // The float is not divisible by the number
    }
}

Rectangle scaledRectangle(int width, int height)
{
    Rectangle scaledRectangle = {
        (GetScreenWidth() - ((float)width * getTextureScaleFactor())) * 0.5f,
        (GetScreenHeight() - ((float)height * getTextureScaleFactor())) * 0.5f,
        (float)width * getTextureScaleFactor(),
        (float)height * getTextureScaleFactor()};

    return scaledRectangle;
};
