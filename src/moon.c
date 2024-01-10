#include "include/raylib.h"
#include "include/world.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>
#include <math.h>

Texture2D renderMoonTexture() {
    Texture2D texture = LoadTexture("resources/Moon.png");

    return texture;
}

moonStruct initMoon(Texture2D texture, int screenWidth, int screenHeight)
{

    int x = 0;
    int y = 0;
    Vector2 position = (Vector2){
        gameScreenWidth / 2 - (texture.width * getScale()) / 2 + x,
        gameScreenHeight / 2 - (texture.height * getScale()) / 2 + y,
    };
    float angle = 120.0f;

    moonStruct moonStruct = {
        texture,
        position,
        x,
        y,
        angle,
    };

    return moonStruct;
}

void initMoonPosition(moonStruct *moon) {
          // Calculate scaling factors
    moon->position = (Vector2){
        gameScreenWidth / 2 - (moon->texture.width * getScaleForTexture(moon->texture)) / 2 + moon->x,
        gameScreenHeight / 2 - (moon->texture.height * getScaleForTexture(moon->texture)) / 2 + moon->y,
    };
} 

bool isNight(moonStruct *moon, int screenHeight)
{
    return (moon->y <= screenHeight / 2);
}

bool isNightAndMoonVisible(moonStruct *moon, int screenHeight)
{
    return (moon->y <= screenHeight / 2 - 50);
}

void renderMoon(moonStruct *moon, int screenHeight)
{
    // Rectangle destination = {
    //     moon->x,
    //     moon->y,
    //     (float)moon->texture.width,
    //     (float)moon->texture.height};
    // if (isNight(moon, screenHeight) == true) {
        // DrawTexturePro(moon->texture, moon->source, destination, moon->origin, 0.0f, WHITE);
                 // Calculate scaling factors
    float scaleX = (float)screenWidth / moon->texture.width;
    float scaleY = (float)screenHeight / moon->texture.height;
    DrawTextureEx(moon->texture, moon->position, 0.0f, getScaleForTexture(moon->texture) / 2, WHITE);
    // }
}

// Update the moon's position based on the circular path
void UpdateMoonPosition(moonStruct *moon, int screenWidth, int screenHeight, int orbitRadius) {
    // TODO - set to 0.03f;
    float speed = 1.53f;
    moon->angle += speed * GetFrameTime();
    moon->x = orbitRadius * cosf(moon->angle);
    moon->y = orbitRadius * sinf(moon->angle);
}

