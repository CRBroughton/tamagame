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

uiBar initWarmthBar(Texture2D texture)
{
    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){
        gameScreenWidth / 2 - (texture.width * getScale()) / 2 + x,
        gameScreenHeight / 2 - (texture.height * getScale()) / 2 + y,
    };
    struct uiBar uiBar = {
        texture,
        position,
        x,
        y};

    return uiBar;
};

grassStruct initGrass(Texture2D texture, int screenWidth, int screenHeight)
{

    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){
        gameScreenWidth / 2 - (texture.width * getScale()) / 2 + x,
        gameScreenHeight / 2 - (texture.height * getScale()) / 2 + y,
    };
    struct grassStruct grassStruct = {
        texture,
        position,
        x,
        y};

    return grassStruct;
}

nightSkyStruct initNightSky(Texture2D texture, int screenWidth, int screenHeight)
{

    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){
        gameScreenWidth / 2 - (texture.width * getScale()) / 2 + x,
        gameScreenHeight / 2 - (texture.height * getScale()) / 2 + y,
    };
    struct nightSkyStruct nightSkyStruct = {
        texture,
        position,
        x,
        y};

    return nightSkyStruct;
}


void initWarmthBarPosition(uiBar *warmth)
{
    warmth->position = (Vector2){
        gameScreenWidth / 2 - (warmth->texture.width * getScaleForTexture(warmth->texture)) / 2 + warmth->x,
        gameScreenHeight / 2 - (warmth->texture.height * getScaleForTexture(warmth->texture)) / 2 + warmth->y,
    };

    warmth->x = -256 + (warmth->texture.width / 2) + 15;
    warmth->y = -256 + (warmth->texture.width / 2) + 75;
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

void renderWarmthBar(uiBar warmth)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(warmth.texture, warmth.position, 0.0f, getScaleForTexture(warmth.texture), WHITE);

}

worldStruct initWorld(Texture2D grassTexture, int screenWidth, int screenHeight)
{
    moonStruct moon = initMoon(grassTexture, screenWidth, screenHeight);
    sunStruct sun = initSun(grassTexture, screenWidth, screenHeight);

    grassStruct grass = initGrass(grassTexture, screenWidth, screenHeight);
    bool night = true;
    bool day = false;
    int warmth = 3;
    int logCount = 0;

    worldStruct world = {
        moon,
        sun,
        grass,
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