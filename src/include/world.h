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

worldStruct initWorld(Texture2D grassTexture, Texture2D moonTexture, Texture2D sunTexture, Texture2D nightSkyTexture, Texture2D mountainsTexture);
WorldObject initWorldObj(Texture2D texture);
WorldObject initClouds1(Texture2D texture);
void initMountainsPositions(WorldObject *mountains);
void initWarmthBarPosition(WorldObject *warth);
void initEXPBarPosition(WorldObject *exp);
void initGrassPosition(WorldObject *grass);
void initNightSkyPosition(WorldObject *nightSky);
void initClouds1Position(WorldObject *clouds);
void renderGrass(WorldObject grass);
void renderNightSky(WorldObject nightSky);
void renderUIBar(WorldObject uiBar);
void renderClouds1(WorldObject clouds);
void renderMountains(WorldObject mountains);
void updateDayCycle(worldStruct *world, int screenHeight);
void UpdateCloudPosition(WorldObject *clouds);
#endif // WORLD_H
