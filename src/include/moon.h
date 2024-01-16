#include "raylib.h"

#ifndef MOON_H
#define MOON_H

typedef struct moonStruct
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
    float angle;

} moonStruct;

Texture2D renderMoonTexture();
moonStruct initMoon(Texture2D texture);
void renderMoon(moonStruct *moon, int screenHeight);
void initMoonPosition(moonStruct *moon);
void UpdateMoonPosition(moonStruct *entity, int screenWidth, int screenHeight, int orbitRadius);
bool isNight(moonStruct *moon, int screenHeight);
bool isNightAndMoonVisible(moonStruct *moon, int screenHeight);
#endif // MOON_H
