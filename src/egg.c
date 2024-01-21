#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

eggStruct initEgg(Texture2D texture)
{
    Vector2 eggPosition = (Vector2){0, 0};
    const int health = 3;
    int warmth = 3;
    const int x = 0;
    const int y = 0;
    int exp = 0;
    bool isCracked = false;

    // Set random seed gen
    srand((unsigned int)time(NULL));

    // Generate a random index to select a float from the array
    int randomIndex = rand() % 5;
    int secondRanIndex = rand() % 5;
    float shakeArray[5] = {10.0f, 15.0f, 25.0f, 12.0f, 18.0f};
    float frames = 0.0f;
    float target = shakeArray[randomIndex];
    float reducer = shakeArray[secondRanIndex];

    Rectangle frameRec = {
        0.0f,
        0.0f,
        (float)texture.width / 6,
        (float)texture.height,
    };
    int frameCounter = 0;
    int frameSpeed = 1;
    int currentFrame = 0;

    struct eggStruct eggStruct = {
        isCracked,
        frameRec,
        frameCounter,
        frameSpeed,
        currentFrame,
        texture,
        health,
        warmth,
        eggPosition,
        x,
        y,
        exp,
        frames,
        target,
        reducer,
    };

    return eggStruct;
};

void renderEgg(eggStruct *egg)
{
    if (egg->isCracked == false)
    {
        DrawTexturePro(
            egg->texture,
            egg->frameRec,
            (Rectangle){
                egg->eggPosition.x,
                egg->eggPosition.y,
                egg->frameRec.width * getScaleForSpriteSheet(egg->frameRec, 2),
                egg->frameRec.height * getScaleForSpriteSheet(egg->frameRec, 2)},
            (Vector2){0, 0},
            0.0f,
            WHITE);
    }
}

void initEggPosition(eggStruct *egg)
{

    float scaleX = (float)screenWidth / egg->frameRec.width;
    float scaleY = (float)screenHeight / egg->frameRec.height;

    float scale = fminf(scaleX, scaleY) / 4;

    egg->eggPosition = (Vector2){
        gameScreenWidth / 2 - egg->frameRec.width * scale + egg->x,
        gameScreenHeight / 2 - egg->frameRec.height * scale + egg->y,
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

void drawEggWarmthBar(eggStruct *egg, WorldObject warmth)
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

void drawEggEXPBar(eggStruct *egg, WorldObject exp)
{
    if (egg->exp == 3)
    {
        DrawRectangle(exp.position.x + 3, exp.position.y + 3, 10, exp.texture.height * 3 + 3, YELLOW);
    }
    if (egg->exp == 2)
    {
        DrawRectangle(exp.position.x + 3, exp.position.y + 2 + exp.texture.height, 10, exp.texture.height * 2 + 3, YELLOW);
    }
    if (egg->exp == 1)
    {
        DrawRectangle(exp.position.x + 3, exp.position.y + 2 + exp.texture.height * 2, 10, exp.texture.height + 3, YELLOW);
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

void crackEgg(eggStruct *egg)
{
    if (egg->exp == 3 && egg->isCracked == false)
    {
        egg->frameCounter++;

        if (egg->frameCounter >= (60 / egg->frameSpeed))
        {
            egg->frameCounter = 0;
            egg->currentFrame++;

            if (egg->currentFrame > 5)
            {
                egg->currentFrame = 0;
                egg->isCracked = true;
            }

            egg->frameRec.x = (float)egg->currentFrame * (float)egg->texture.width / 6;
        }
    }
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