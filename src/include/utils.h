#ifndef UTILS_H
#define UTILS_H

char *intToString(int number);
char* floatToString(float value, int precision);
int isFloatDivisible(float num, float divisor);
Rectangle scaledRectangle(int width, int height);
float getScaleForTexture(Texture2D texture);
Vector2 getVirtualMousePosition();
#endif // UTILS_H
