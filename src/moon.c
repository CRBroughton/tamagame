#include "include/raylib.h"
#include "include/world.h"
#include "include/utils.h"

#include <stdio.h>
#include <math.h>

moonStruct initMoon(int screenWidth, int screenHeight)
{
    Texture2D texture = LoadTexture("resources/Moon.png");

    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destination = {0, 0, (float)texture.width, (float)texture.height};
    Vector2 origin = {texture.width / 2, texture.height / 2};

    moonStruct moonStruct = {
        texture,
        source,
        destination,
        origin,
    };

    return moonStruct;
}

bool isNight(moonStruct *moon, int screenHeight)
{
    return (moon->y <= screenHeight / 2);
}

void renderMoon(moonStruct *moon, int screenHeight)
{
    Rectangle destination = {
        moon->x,
        moon->y,
        (float)moon->texture.width,
        (float)moon->texture.height};
    if (isNight(moon, screenHeight) == true) {
        DrawTexturePro(moon->texture, moon->source, destination, moon->origin, 0.0f, WHITE);
    }
}

void UpdateMoonPosition(moonStruct *moon, int screenWidth, int screenHeight, int orbitRadius) {
    // Update the moon's position based on the circular path
    float speed = 0.5f;
    moon->angle += speed * GetFrameTime();
    moon->x = screenWidth / 2 + orbitRadius * cosf(moon->angle);
    moon->y = screenHeight / 2 + orbitRadius * sinf(moon->angle);
}

