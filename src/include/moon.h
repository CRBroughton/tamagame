#include "raylib.h"
#include "phase.h"

#ifndef MOON_H
#define MOON_H

typedef struct moonStruct
{
    Texture2D moon;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    int currentPhase;
    phase phases[3];

} moonStruct;

struct moonStruct initMoon(int screenWidth, int screenHeight);
void renderMoon(struct moonStruct moon);
void updateMoonPhase(struct moonStruct *moon, int *timer);

#endif // MOON_H
