#include "include/raylib.h"
#include "include/world.h"
#include "include/sun.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>
#include <math.h>

sunStruct initSun(Texture2D texture)
{
    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){0, 0};
    float angle = 10.0f;

    sunStruct sunStruct = {
        texture,
        position,
        x,
        y,
        angle,
    };

    return sunStruct;
}

void initSunPosition(sunStruct *sun)
{
    sun->position = (Vector2){
        gameScreenWidth / 2 - sun->texture.width * getScaleForTexture(sun->texture) / 4 + sun->x,
        gameScreenHeight / 2 - sun->texture.height * getScaleForTexture(sun->texture) / 4 + sun->y,
    };
}

bool isDay(sunStruct *sun, int screenHeight)
{
    return (sun->y <= screenHeight / 2);
}

void renderSun(sunStruct *sun, int screenHeight)
{
    if (isDay(sun, screenHeight) == true)
    {
        DrawTextureEx(sun->texture, sun->position, 0.0f, getScaleForTexture(sun->texture) / 2, WHITE);
    }
}

// Update the sun's position based on the circular path
void UpdateSunPosition(sunStruct *sun, int screenWidth, int screenHeight, int orbitRadius)
{
    // TODO - set to 0.03f;
    float speed = 0.03f;
    sun->angle += speed * GetFrameTime();
    sun->x = orbitRadius * cosf(sun->angle);
    sun->y = orbitRadius * sinf(sun->angle);
}
