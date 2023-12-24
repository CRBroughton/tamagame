#include "include/raylib.h"
#include "include/world.h"
#include "include/moon.h"
#include "include/utils.h"

#include <stdio.h>

worldStruct initWorld(int screenWidth, int screenHeight)
{
    struct moonStruct moon = initMoon(screenWidth, screenHeight);
    bool night = true;
    bool day = false;
    int warmth = 3;

    struct worldStruct world = {
        moon,
        night,
        day,
        warmth,
    };

    return world;
};
