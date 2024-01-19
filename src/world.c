#include "include/raylib.h"
#include "include/world.h"
#include "include/moon.h"
#include "include/sun.h"
#include "include/log.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>

Texture2D loadGrassTexture()
{
    Texture2D texture = LoadTexture("resources/Grass.png");

    return texture;
};

Texture2D loadNightSkyTexture()
{
    Texture2D texture = LoadTexture("resources/Night_Sky.png");

    return texture;
}

Texture2D loadWarmthTexture()
{
    Texture2D texture = LoadTexture("resources/UI_Bar.png");

    return texture;
}

Texture2D loadCloud1Texture()
{
    Texture2D texture = LoadTexture("resources/Clouds1.png");

    return texture;
}

clouds initClouds1(Texture2D texture)
{
    int x = -256 + (texture.width / 2);
    int y = -256 + (texture.height / 2);
    Vector2 position = (Vector2){0,0};
    struct clouds clouds = {
        texture,
        position,
        x,
        y};

    return clouds;
}

uiBar initUIBar(Texture2D texture)
{
    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){0,0};
    struct uiBar uiBar = {
        texture,
        position,
        x,
        y};

    return uiBar;
};

grassStruct initGrass(Texture2D texture)
{

    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){0,0};
    struct grassStruct grassStruct = {
        texture,
        position,
        x,
        y};

    return grassStruct;
}

nightSkyStruct initNightSky(Texture2D texture)
{

    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){0,0};
    struct nightSkyStruct nightSkyStruct = {
        texture,
        position,
        x,
        y};

    return nightSkyStruct;
}


void initClouds1Position(clouds *clouds)
{
    clouds->position = (Vector2){
        gameScreenWidth / 2 - (clouds->texture.width * getScaleForTexture(clouds->texture)) / 2 + clouds->x,
        gameScreenHeight / 2 - (clouds->texture.height * getScaleForTexture(clouds->texture)) / 2 + clouds->y,
    };
}

void initWarmthBarPosition(uiBar *warmth)
{
    warmth->position = (Vector2){
        gameScreenWidth / 2 - (warmth->texture.width * getScaleForTexture(warmth->texture)) / 2 + warmth->x,
        gameScreenHeight / 2 - (warmth->texture.height * getScaleForTexture(warmth->texture)) / 2 + warmth->y,
    };

    warmth->x = -256 + (warmth->texture.width / 2) + 15;
    warmth->y = -256 + (warmth->texture.height / 2) + 55;
}

void initEXPBarPosition(uiBar *exp)
{
    exp->position = (Vector2){
        gameScreenWidth / 2 - (exp->texture.width * getScaleForTexture(exp->texture)) / 2 + exp->x,
        gameScreenHeight / 2 - (exp->texture.height * getScaleForTexture(exp->texture)) / 2 + exp->y,
    };

    exp->x = -256 + (exp->texture.width / 2) + 35;
    exp->y = -256 + (exp->texture.height / 2) + 55;
}

void initGrassPosition(grassStruct *grass)
{
    grass->position = (Vector2){
        gameScreenWidth / 2 - (grass->texture.width * getScaleForTexture(grass->texture)) / 2 + grass->x,
        gameScreenHeight / 2 - (grass->texture.height * getScaleForTexture(grass->texture)) / 2 + grass->y,
    };

    grass->x = -256 + (grass->texture.width / 2);
    grass->y = -5;
}

void initNightSkyPosition(nightSkyStruct *nightSky)
{
    nightSky->position = (Vector2){
        gameScreenWidth / 2 - (nightSky->texture.width * getScaleForTexture(nightSky->texture)) / 2 + nightSky->x,
        gameScreenHeight / 2 - (nightSky->texture.height * getScaleForTexture(nightSky->texture)) / 2 + nightSky->y,
    };

    nightSky->x = -256 + (nightSky->texture.width / 2);
    nightSky->y = -256 + 30;
}

void renderGrass(grassStruct grass)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(grass.texture, grass.position, 0.0f, getScaleForTexture(grass.texture) * 4, WHITE);
}

void renderNightSky(nightSkyStruct nightSky)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(nightSky.texture, nightSky.position, 0.0f, getScaleForTexture(nightSky.texture) * 4, WHITE);
}

void renderUIBar(uiBar warmth)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(warmth.texture, warmth.position, 0.0f, getScaleForTexture(warmth.texture), WHITE);
}

void renderClouds1(clouds clouds)
{
    DrawTextureEx(clouds.texture, clouds.position, 0.0f, getScaleForTexture(clouds.texture) * 4, WHITE);
}

worldStruct initWorld(Texture2D grassTexture, Texture2D moonTexture, Texture2D sunTexture, Texture2D nightSkyTexture)
{
    grassStruct grass = initGrass(grassTexture);
    moonStruct moon = initMoon(moonTexture);
    sunStruct sun = initSun(sunTexture);
    nightSkyStruct nightSky = initNightSky(nightSkyTexture);

    bool night = true;
    bool day = false;
    int warmth = 3;
    int logCount = 0;

    worldStruct world = {
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