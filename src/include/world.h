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
    nightSkyStruct nightSky;
    bool night;
    bool day;
    int warmth;
    int logCount;
} worldStruct;

typedef struct uiBar
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
} uiBar;

typedef struct clouds
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
} clouds;

Texture2D loadGrassTexture();
Texture2D loadNightSkyTexture();
Texture2D loadWarmthTexture();
Texture2D loadCloud1Texture();
worldStruct initWorld(Texture2D grassTexture, Texture2D moonTexture, Texture2D sunTexture, Texture2D nightSkyTexture);
grassStruct initGrass(Texture2D texture);
nightSkyStruct initNightSky(Texture2D texture);
clouds initClouds1(Texture2D texture);
uiBar initUIBar(Texture2D texture);
void initWarmthBarPosition(uiBar *warth);
void initEXPBarPosition(uiBar *exp);
void initGrassPosition(grassStruct *grass);
void initNightSkyPosition(nightSkyStruct *nightSky);
void initClouds1Position(clouds *clouds);
void renderGrass(grassStruct grass);
void renderNightSky(nightSkyStruct nightSky);
void renderUIBar(uiBar warmth);
void renderClouds1(clouds clouds);
void updateDayCycle(worldStruct *world, int screenHeight);

#endif // WORLD_H
