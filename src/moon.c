#include "include/raylib.h"
#include "include/world.h"
#include "include/utils.h"

#include <stdio.h>

moonStruct initMoon(int screenWidth, int screenHeight)
{
    Texture2D texture = LoadTexture("resources/Moon.png");

    phase phases[3] = {
        {29, 8},
        {64, -2},
        {99, 8},
    };
    int currentPhase = 0;

    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destination = {phases[currentPhase].x, phases[currentPhase].y, (float)texture.width, (float)texture.height};
    Vector2 origin = {texture.width / 2, texture.height / 2};

    moonStruct moonStruct = {
        texture,
        source,
        destination,
        origin,
        currentPhase,
        {
            {29, 8},
            {64, -2},
            {99, 8},
        },
    };

    return moonStruct;
}

void renderMoon(struct moonStruct moon)
{
    Rectangle destination = {
        moon.phases[moon.currentPhase].x,
        moon.phases[moon.currentPhase].y,
        (float)moon.texture.width,
        (float)moon.texture.height};
    DrawTexturePro(moon.texture, moon.source, destination, moon.origin, 0.0f, WHITE);
};

void updateMoonPhase(struct moonStruct *moon, int *timer)
{
    int elapsedTime = GetTime() - *timer;

    // return to start of phase cycle
    if (elapsedTime > 10 && moon->currentPhase == 2)
    {
        moon->currentPhase = 0;
        *timer = GetTime();
        return;
    };

    // increment the phase cycle
    for (int i = 0; i < 2; i++)
    {
        if (elapsedTime > 3 && moon->currentPhase == 0)
        {
            moon->currentPhase++;
        }
        if (elapsedTime > 5 && moon->currentPhase == 1)
        {
            moon->currentPhase++;
        }
    };
};
