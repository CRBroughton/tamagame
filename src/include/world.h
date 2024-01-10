#include "raylib.h"
#include "moon.h"
#include "sun.h"

#ifndef WORLD_H
#define WORLD_H

typedef struct grassStruct
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
} grassStruct;

typedef struct nightSkyStruct
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
} nightSkyStruct;

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
Texture2D loadNightSkyTexture();
worldStruct initWorld(Texture2D grassTexture, int screenWidth, int screenHeight);
grassStruct initGrass(Texture2D grass, int screenWidth, int screenHeight);
nightSkyStruct initNightSky(Texture2D texture, int screenWidth, int screenHeight);
void initGrassPosition(grassStruct *grass);
void initNightSkyPosition(nightSkyStruct *nightSky);
void renderGrass(grassStruct grass);
void renderNightSky(nightSkyStruct nightSky);
void updateDayCycle(worldStruct *world, int screenHeight);

#endif // WORLD_H
