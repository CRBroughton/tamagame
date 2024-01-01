#include "raylib.h"
#include "moon.h"
#include "sun.h"

#ifndef WORLD_H
#define WORLD_H

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
    sunStruct sun;
    grassStruct grass;
    bool night;
    bool day;
    int warmth;
    int logCount;
} worldStruct;

Texture2D loadGrassTexture();
worldStruct initWorld(Texture2D grassTexture, int screenWidth, int screenHeight);
grassStruct initGrass(Texture2D grass, int screenWidth, int screenHeight);
void renderGrass(grassStruct grass);
void updateDayCycle(worldStruct *world, int screenHeight);

#endif // WORLD_H
