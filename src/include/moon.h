#include "raylib.h"
#include "phase.h"

#ifndef MOON_H
#define MOON_H

typedef struct moonStruct
{
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    int currentPhase;
    phase phases[3];

} moonStruct;

moonStruct initMoon(int screenWidth, int screenHeight);
void renderMoon(moonStruct moon);
void updateMoonPhase(moonStruct *moon, int *timer);

#endif // MOON_H
