#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

eggStruct initEgg(int screenWidth, int screenHeight)
{

    Texture2D texture = LoadTexture("resources/Closed_Egg.png");

    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destination = {screenWidth / 2.0f, screenHeight / 2.0f, texture.width, texture.height};
    Vector2 origin = {texture.width / 2, texture.height / 2};

    const int health = 3;
    const int warmth = 3;

    // Set random seed gen
    srand((unsigned int)time(NULL));

    // Generate a random index to select a float from the array
    int randomIndex = rand() % 5;
    int secondRanIndex = rand() % 5;
    float shakeArray[5] = {10.0f, 15.0f, 25.0f, 12.0f, 18.0f};
    float frames = 0.0f;
    float target = shakeArray[randomIndex];
    float reducer = shakeArray[secondRanIndex];

    struct eggStruct eggStruct = {
        texture,
        source,
        destination,
        origin,
        health,
        warmth,
        frames,
        target,
        reducer,
    };

    return eggStruct;
};

void renderEgg(eggStruct egg)
{
    DrawTexturePro(egg.texture, egg.source, egg.destination, egg.origin, 0.0f, WHITE);
}

void reduceEggHealth(eggStruct *egg, int *timer)
{
    int elapsedTime = GetTime() - *timer;

    if (egg->health <= 0)
        return;
    if (egg->warmth <= 0 && elapsedTime == 3)
    {
        egg->health -= 1;
        *timer = GetTime();
    }
}

void reduceEggWarmth(eggStruct *egg, worldStruct *world, int *timer)
{
    int elapsedTime = GetTime() - *timer;

    if (egg->warmth <= 0)
    {
        reduceEggHealth(egg, timer);
    }
    if (world->night == true && elapsedTime == 3)
    {
        egg->warmth -= 1;
        *timer = GetTime();
    }
}

void increaseEggWarmth(eggStruct *egg)
{
    if (egg->warmth < 3)
    {
        egg->warmth += 1;
    }
}

void drawEggHealthBar(eggStruct *egg)
{
    // TODO - draw fancy outline
    if (egg->health == 3)
    {
        DrawRectangle(11, 12, 3, 30, RED);
    }
    if (egg->health == 2)
    {
        DrawRectangle(11, 22, 3, 20, RED);
    }
    if (egg->health == 1)
    {
        DrawRectangle(11, 32, 3, 10, RED);
    }
    DrawRectangle(11, 32, 3, 0, RED);
}

void drawEggWarmthBar(eggStruct *egg)
{
    // TODO - draw fancy outline
    if (egg->warmth == 3)
    {
        DrawRectangle(21, 12, 3, 30, ORANGE);
    }
    if (egg->warmth == 2)
    {
        DrawRectangle(21, 22, 3, 20, ORANGE);
    }
    if (egg->warmth == 1)
    {
        DrawRectangle(21, 32, 3, 10, ORANGE);
    }
    DrawRectangle(21, 32, 3, 0, ORANGE);
}

void animateEgg(eggStruct *egg, float speed, int screenWidth)
{
    int width = screenWidth / 2.0f + 2;

    // get to 60, then vibrate
    if (egg->frames < egg->target)
    {
        egg->frames += 1;
        return;
    };

    // jiggle egg
    egg->destination.x += 1;

    if (egg->destination.x >= width)
    {
        egg->destination.x = screenWidth / 2.0f;
    };

    // decrease the reducer
    if (egg->reducer > 0)
    {
        egg->reducer -= 0.5f;
    };

    // reset
    if (egg->reducer <= 0.0f)
    {
        egg->frames = 0.0f;
        int randomIndex = rand() % 5;
        int secondRanIndex = rand() % 5;

        float shakeArray[5] = {10.0f, 15.0f, 25.0f, 12.0f, 18.0f};
        egg->reducer = shakeArray[randomIndex];
        egg->target = shakeArray[secondRanIndex];
    }
}