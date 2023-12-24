#include "raylib.h"
#include "moon.h"

#ifndef WORLD_H
#define WORLD_H

typedef struct sun
{
    int currentPhase;
    phase phases[3];
} sun;


typedef struct grassStruct
{
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
} grassStruct;

typedef struct worldStruct
{
    moonStruct moon;
    grassStruct grass;
    bool night;
    bool day;
    int warmth;
} worldStruct;

worldStruct initWorld(int screenWidth, int screenHeight);
void renderGrass(grassStruct grass);

#endif // WORLD_H
