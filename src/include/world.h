#include "raylib.h"
#include "moon.h"
#include "sun.h"

#ifndef WORLD_H
#define WORLD_H

typedef struct WorldObject
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
} WorldObject;

typedef struct worldStruct
{
    WorldObject mountains;
    moonStruct moon;
    sunStruct sun;
    WorldObject grass;
    WorldObject nightSky;
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

worldStruct initWorld(Texture2D grassTexture, Texture2D moonTexture, Texture2D sunTexture, Texture2D nightSkyTexture, Texture2D mountainsTexture);
WorldObject initGrass(Texture2D texture);
WorldObject initNightSky(Texture2D texture);
WorldObject initClouds1(Texture2D texture);
WorldObject initMountains(Texture2D texture);
void initMountainsPositions(WorldObject *mountains);
uiBar initUIBar(Texture2D texture);
void initWarmthBarPosition(uiBar *warth);
void initEXPBarPosition(uiBar *exp);
void initGrassPosition(WorldObject *grass);
void initNightSkyPosition(WorldObject *nightSky);
void initClouds1Position(WorldObject *clouds);
void renderGrass(WorldObject grass);
void renderNightSky(WorldObject nightSky);
void renderUIBar(uiBar warmth);
void renderClouds1(WorldObject clouds);
void renderMountains(WorldObject mountains);
void updateDayCycle(worldStruct *world, int screenHeight);

#endif // WORLD_H
