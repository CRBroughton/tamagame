#include "include/raylib.h"
#include "include/world.h"
#include "include/moon.h"
#include "include/utils.h"

#include <stdio.h>

grassStruct initGrass(int screenWidth, int screenHeight)
{
    Texture2D grass = LoadTexture("resources/Grass.png");

    Rectangle source = {0.0f, 0.0f, (float)grass.width, (float)grass.height};
    Rectangle destination = {screenWidth / 2.0f, screenHeight / 2.0f + 7, grass.width, grass.height};
    Vector2 origin = {grass.width / 2, grass.height / 2};

    struct grassStruct grassStruct = {
        grass,
        source,
        destination,
        origin,
    };

    return grassStruct;
}

void renderGrass(struct grassStruct grass)
{
    DrawTexturePro(grass.texture, grass.source, grass.destination, grass.origin, 0.0f, WHITE);
}

worldStruct initWorld(int screenWidth, int screenHeight)
{
    struct moonStruct moon = initMoon(screenWidth, screenHeight);
    struct grassStruct grass = initGrass(screenWidth, screenHeight);
    bool night = true;
    bool day = false;
    int warmth = 3;

    struct worldStruct world = {
        moon,
        grass,
        night,
        day,
        warmth,
    };

    return world;
};
