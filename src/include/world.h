#include "raylib.h"
#include "moon.h"

#ifndef WORLD_H
#define WORLD_H

typedef struct sun
{
    int currentPhase;
    phase phases[3];
} sun;

typedef struct worldStruct
{
    moonStruct moon;
    bool night;
    bool day;
    int warmth;
} worldStruct;

worldStruct initWorld(int screenWidth, int screenHeight);

#endif // WORLD_H
