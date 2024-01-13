#include "raylib.h"
#include "raymath.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

extern const int screenWidth;
extern const int screenHeight;

extern int gameScreenWidth;
extern int gameScreenHeight;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

float getScale();

extern int scaleFactor;
float getTextureScaleFactor();
#endif // CONSTANTS_H
