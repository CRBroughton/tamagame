#include "include/raylib.h"
#include "include/world.h"
#include "include/sun.h"
#include "include/utils.h"

#include <stdio.h>
#include <math.h>

sunStruct initSun(int screenWidth, int screenHeight)
{
    Texture2D texture = LoadTexture("resources/Sun.png");

    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destination = {0, 0, (float)texture.width, (float)texture.height};
    Vector2 origin = {texture.width / 2, texture.height / 2};

    int x = 0;
    int y = 0;
    float angle = 10.0f;

    sunStruct sunStruct = {
        texture,
        source,
        destination,
        origin,
        x,
        y,
        angle,
    };

    return sunStruct;
}

bool isDay(sunStruct *sun, int screenHeight)
{
    return (sun->y <= screenHeight / 2);
}

void renderSun(sunStruct *sun, int screenHeight)
{
    Rectangle destination = {
        sun->x,
        sun->y,
        (float)sun->texture.width,
        (float)sun->texture.height};
    if (isDay(sun, screenHeight) == true) {
        DrawTexturePro(sun->texture, sun->source, destination, sun->origin, 0.0f, WHITE);
    }
}

// Update the sun's position based on the circular path
void UpdateSunPosition(sunStruct *sun, int screenWidth, int screenHeight, int orbitRadius) {
    float speed = 0.03f;
    sun->angle += speed * GetFrameTime();
    sun->x = screenWidth / 2 + orbitRadius * cosf(sun->angle);
    sun->y = screenHeight / 2 + orbitRadius * sinf(sun->angle);
}

