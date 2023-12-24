#include "raylib.h"
#include "moon.h"

#ifndef WORLD_H
#define WORLD_H

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

#endif // WORLD_H
