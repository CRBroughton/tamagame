#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/raylib.h"
#include "include/constants.h"
#include "utils.h"

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

char *floatToString(float value, int precision)
{
    // Calculate the size needed for the string
    int size = snprintf(NULL, 0, "%.*f", precision, value);

    // Allocate memory for the string
    char *result = (char *)malloc(size + 1);

    // Use sprintf to convert the float to a string with specified precision
    sprintf(result, "%.*f", precision, value);

    return result;
}

#define EPSILON 1e-6 // Adjust this epsilon value based on your precision requirements
int isFloatDivisible(float num, float divisor)
{
    // Check if divisor is not zero to avoid division by zero
    if (fabs(divisor) < EPSILON)
    {
        printf("Error: Division by zero.\n");
        return 0; // You can handle this error condition as needed
    }

    // Calculate the remainder using fmod function
    float remainder = fmod(num, divisor);

    // Check if the remainder is within the acceptable range of epsilon
    if (fabs(remainder) < EPSILON)
    {
        return 1; // The float is divisible by the number
    }
    else
    {
        return 0; // The float is not divisible by the number
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

float getScaleForTexture(Texture2D texture)
{
    float scaleX = (float)screenWidth / texture.width;
    float scaleY = (float)screenHeight / texture.height;

    return fminf(scaleX, scaleY);
}

float getScaleForSpriteSheet(Rectangle frameRec, int divider)
{
    // set default value
    if (divider == 0)
    {
        divider = 0;
    }

    float scaleX = (float)screenWidth / frameRec.width;
    float scaleY = (float)screenHeight / frameRec.height;

    return fminf(scaleX, scaleY) / divider;
}

Vector2 getVirtualMousePosition()
{
    // Update virtual mouse (clamped mouse value behind game screen)
    Vector2 mouse = GetMousePosition();

    Vector2 virtualMouse = {0};

    virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth * getScale())) * 0.5f) / getScale();
    virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight * getScale())) * 0.5f) / getScale();

    virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0, 0}, (Vector2){(float)gameScreenWidth, (float)gameScreenHeight});

    return virtualMouse;
}