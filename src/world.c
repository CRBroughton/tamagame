#include "include/raylib.h"
#include "include/world.h"
#include "include/moon.h"
#include "include/sun.h"
#include "include/log.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>

WorldObject createWorldObj(Texture2D texture)
{
    Vector2 position = (Vector2){0, 0};
    int x = 0;
    int y = 0;

    WorldObject worldObject = {
        texture,
        position,
        x,
        y,
    };

    return worldObject;
}

WorldObject initWorldObj(Texture2D texture)
{
    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){0, 0};
    struct WorldObject worldObj = {
        texture,
        position,
        x,
        y};

    return worldObj;
}

WorldObject initClouds1(Texture2D texture)
{
    WorldObject clouds = createWorldObj(texture);
    clouds.x = -256 + (texture.width / 2);
    clouds.y = -256 + (texture.height / 2);

    return clouds;
}

void initMountainsPositions(WorldObject *mountains)
{
    mountains->position = (Vector2){
        gameScreenWidth / 2 - (mountains->texture.width * getScaleForTexture(mountains->texture)) / 2 + mountains->x,
        gameScreenHeight / 2 - (mountains->texture.height * getScaleForTexture(mountains->texture)) / 2 + mountains->y,
    };

    mountains->x = -256 + (mountains->texture.width / 2);
    mountains->y = -256 + 30;
}

void initClouds1Position(WorldObject *clouds)
{
    clouds->position = (Vector2){
        gameScreenWidth / 2 - (clouds->texture.width * getScaleForTexture(clouds->texture)) / 2 + clouds->x,
        gameScreenHeight / 2 - (clouds->texture.height * getScaleForTexture(clouds->texture)) / 2 + clouds->y,
    };
}

void initWarmthBarPosition(WorldObject *warmth)
{
    warmth->position = (Vector2){
        gameScreenWidth / 2 - (warmth->texture.width * getScaleForTexture(warmth->texture)) / 2 + warmth->x,
        gameScreenHeight / 2 - (warmth->texture.height * getScaleForTexture(warmth->texture)) / 2 + warmth->y,
    };

    warmth->x = -256 + (warmth->texture.width / 2) + 15;
    warmth->y = -256 + (warmth->texture.height / 2) + 55;
}

void initEXPBarPosition(WorldObject *exp)
{
    exp->position = (Vector2){
        gameScreenWidth / 2 - (exp->texture.width * getScaleForTexture(exp->texture)) / 2 + exp->x,
        gameScreenHeight / 2 - (exp->texture.height * getScaleForTexture(exp->texture)) / 2 + exp->y,
    };

    exp->x = -256 + (exp->texture.width / 2) + 35;
    exp->y = -256 + (exp->texture.height / 2) + 55;
}

void initGrassPosition(WorldObject *grass)
{
    grass->position = (Vector2){
        gameScreenWidth / 2 - (grass->texture.width * getScaleForTexture(grass->texture)) / 2 + grass->x,
        gameScreenHeight / 2 - (grass->texture.height * getScaleForTexture(grass->texture)) / 2 + grass->y,
    };

    grass->x = -256 + (grass->texture.width / 2);
    grass->y = -5;
}

void initNightSkyPosition(WorldObject *nightSky)
{
    nightSky->position = (Vector2){
        gameScreenWidth / 2 - (nightSky->texture.width * getScaleForTexture(nightSky->texture)) / 2 + nightSky->x,
        gameScreenHeight / 2 - (nightSky->texture.height * getScaleForTexture(nightSky->texture)) / 2 + nightSky->y,
    };

    nightSky->x = -256 + (nightSky->texture.width / 2);
    nightSky->y = -256 + 30;
}

void renderGrass(WorldObject grass)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(grass.texture, grass.position, 0.0f, getScaleForTexture(grass.texture) * 4, WHITE);
}

void renderMountains(WorldObject mountains)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(mountains.texture, mountains.position, 0.0f, getScaleForTexture(mountains.texture) * 4, WHITE);
}

void renderNightSky(WorldObject nightSky)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(nightSky.texture, nightSky.position, 0.0f, getScaleForTexture(nightSky.texture) * 4, WHITE);
}

void renderUIBar(WorldObject uiBar)
{
    DrawTextureEx(uiBar.texture, uiBar.position, 0.0f, getScaleForTexture(uiBar.texture), WHITE);
}

void renderClouds1(WorldObject clouds)
{
    DrawTextureEx(clouds.texture, clouds.position, 0.0f, getScaleForTexture(clouds.texture) * 4, WHITE);
}

worldStruct initWorld(Texture2D grassTexture, Texture2D moonTexture, Texture2D sunTexture, Texture2D nightSkyTexture, Texture2D mountainsTexture)
{
    WorldObject mountains = initWorldObj(mountainsTexture);
    WorldObject grass = initWorldObj(grassTexture);
    moonStruct moon = initMoon(moonTexture);
    sunStruct sun = initSun(sunTexture);
    WorldObject nightSky = initWorldObj(nightSkyTexture);

    bool night = true;
    bool day = false;
    int warmth = 3;
    int logCount = 0;

    worldStruct world = {
        mountains,
        moon,
        sun,
        grass,
        nightSky,
        night,
        day,
        warmth,
        logCount,
    };

    return world;
};

void updateDayCycle(worldStruct *world, int screenHeight)
{
    if (isNight(&world->moon, screenHeight))
    {
        world->night = true;
    }
    else
    {
        world->night = false;
    }
}

void UpdateCloudPosition(WorldObject *clouds)
{
    clouds->x -= 1;

    if (clouds->x < -300)
    {
        clouds->x = 500;
    };
}