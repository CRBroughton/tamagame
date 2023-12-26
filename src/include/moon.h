#include "raylib.h"

#ifndef MOON_H
#define MOON_H

typedef struct moonStruct
{
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    int x;
    int y;
    float angle;

} moonStruct;

moonStruct initMoon(int screenWidth, int screenHeight);
void renderMoon(moonStruct *moon, int screenHeight);
void UpdateMoonPosition(moonStruct *entity, int screenWidth, int screenHeight, int orbitRadius);
bool isNight(moonStruct *moon, int screenHeight);
#endif // MOON_H
