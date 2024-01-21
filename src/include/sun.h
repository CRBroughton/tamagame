#include "raylib.h"

#ifndef SUN_H
#define SUN_H

typedef struct sunStruct
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
    float angle;

} sunStruct;

sunStruct initSun(Texture2D texture);
void initSunPosition(sunStruct *sun);
void renderSun(sunStruct *sun, int screenHeight);
void UpdateSunPosition(sunStruct *entity, int screenWidth, int screenHeight, int orbitRadius);
bool isDay(sunStruct *sun, int screenHeight);
#endif // SUN_H
