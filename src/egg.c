#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Texture2D loadEggTexture()
{
    Texture2D texture = LoadTexture("resources/Closed_Egg.png");

    return texture;
}

eggStruct initEgg(Texture2D texture, int screenWidth, int screenHeight)
{
    int eggx = 0;
    int eggy = 0;
    Vector2 eggPosition = (Vector2){
        gameScreenWidth / 2 - (texture.width * getScale()) / 2 + eggx,
        gameScreenHeight / 2 - (texture.height * getScale()) / 2 + eggy,
    };
    const int health = 3;
    const int warmth = 3;
    const int x = 0;
    const int y = 0;

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
        health,
        warmth,
        eggPosition,
        x,
        y,
        frames,
        target,
        reducer,
        x,
        y};

    return eggStruct;
};

void renderEgg(eggStruct egg)
{
    DrawTextureEx(egg.texture, egg.eggPosition, 0.0f, getScaleForTexture(egg.texture) / 2, WHITE);
}

void initEggPosition(eggStruct *egg)
{
    egg->eggPosition = (Vector2){
        gameScreenWidth / 2 - (egg->texture.width * getScaleForTexture(egg->texture)) / 4 + egg->x,
        gameScreenHeight / 2 - (egg->texture.height * getScaleForTexture(egg->texture)) / 4 + egg->y,
    };
}

// Function that randomly decides whether to execute another function
bool passProbabilityCheck()
{
    float randomValue = ((float)rand() / (float)RAND_MAX); // Generate a random float between 0 and

    float probability = 0.002f;

    if (randomValue < probability)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void reduceEggHealth(eggStruct *egg, worldStruct *world, double *timer)
{
    if (egg->health <= 0)
    {
        return;
    }
    if (
        world->night == true &&
        isNightAndMoonVisible(&world->moon, GetScreenHeight()) == true &&
        passProbabilityCheck() == true)
    {
        egg->health -= 1;
        *timer = GetTime();
    }
}

void reduceEggWarmth(eggStruct *egg, worldStruct *world, double *timer)
{
    if (egg->warmth <= 0)
    {
        reduceEggHealth(egg, world, timer);
        return;
    }
    if (
        world->night == true &&
        isNightAndMoonVisible(&world->moon, GetScreenHeight()) == true &&
        passProbabilityCheck() == true)
    {
        egg->warmth -= 1;
    }
}

void increaseEggWarmth(eggStruct *egg)
{
    if (egg->warmth < 3)
    {
        egg->warmth += 1;
    }
}

void drawEggWarmthBar(eggStruct *egg, uiBar warmth)
{
    if (egg->warmth == 3)
    {
        DrawRectangle(warmth.position.x + 3, warmth.position.y + 3, 10, warmth.texture.height * 3 + 3, RED);
    }
    if (egg->warmth == 2)
    {
         DrawRectangle(warmth.position.x + 3, warmth.position.y + 2 + warmth.texture.height, 10, warmth.texture.height * 2 + 3, RED);
    }
    if (egg->warmth == 1)
    {
          DrawRectangle(warmth.position.x + 3, warmth.position.y + 2 + warmth.texture.height * 2, 10, warmth.texture.height + 3, RED);
    }
}

void drawEggHealthBar(eggStruct *egg)
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
    egg->x += 1;

    if (egg->x >= width)
    {
        egg->x = screenWidth / 2.0f;
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