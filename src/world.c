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
    Texture2D grass = LoadTexture("resources/Grass.png");

    return grass;
};

grassStruct initGrass(Texture2D grass, int screenWidth, int screenHeight)
{

    Rectangle source = {0.0f, 0.0f, (float)grass.width, (float)grass.height};
    Rectangle destination = scaledRectangle(grass.width, grass.height);
    Vector2 origin = {(float)grass.width * getScale(), (float)grass.height * getScale()};
    
    grassStruct grassStruct = {
        grass,
        source,
        destination,
        origin,
    };

    return grassStruct;
}

void renderGrass(grassStruct grass)
{
    DrawTexturePro(grass.texture, grass.source, grass.destination, (Vector2){0, 0}, 0.0f, WHITE);
}

worldStruct initWorld(Texture2D grassTexture, int screenWidth, int screenHeight)
{
    moonStruct moon = initMoon(grassTexture, screenWidth, screenHeight);
    sunStruct sun = initSun(screenWidth, screenHeight);

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