#include "raylib.h"

#ifndef WORLD_H
#define WORLD_H

typedef struct phase
{
    int x;
    int y;
} phase;

typedef struct moonStruct
{
    Texture2D moon;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    int currentPhase;
    phase phases[3];

} moonStruct;

typedef struct sun
{
    int currentPhase;
    phase phases[3];
} sun;

typedef struct world
{
    moonStruct moon;
    sun sun;
    bool night;
    bool day;
    int warmth;
} world;

struct moonStruct initMoon(int screenWidth, int screenHeight);
void renderMoon(struct moonStruct moon);
void updateMoonPhase(struct moonStruct *moon, int *timer);

#endif // WORLD_H
