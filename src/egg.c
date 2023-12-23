#include "include/raylib.h"
#include "include/egg.h"
#include "include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct eggStruct initEgg(int screenWidth, int screenHeight)
{

    Texture2D egg = LoadTexture("resources/Closed_Egg.png");

    Rectangle source = {0.0f, 0.0f, (float)egg.width, (float)egg.height};
    Rectangle destination = {screenWidth / 2.0f, screenHeight / 2.0f, egg.width, egg.height};
    Vector2 origin = {egg.width / 2, egg.height / 2};

    const int health = 3;
    const int warmth = 3;

    // Set random seed gen
    srand((unsigned int)time(NULL));

    // Generate a random index to select a float from the array
    int randomIndex = rand() % 5;
    int secondRanIndex = rand() % 5;
    float shakeArray[5] = {10.0f, 15.0f, 25.0f, 12.0f, 18.0f};

    struct eggStruct eggStruct = {
        egg,
        source,
        destination,
        origin,
        health,
        warmth,
        frames: 0.0f,
        target: shakeArray[randomIndex],
        reducer: shakeArray[secondRanIndex],
    };

    return eggStruct;
};

void renderEgg(struct eggStruct egg)
{
    DrawTexturePro(egg.egg, egg.source, egg.destination, egg.origin, 0.0f, WHITE);
}

void reduceEggHealth(struct eggStruct *egg)
{
    if (egg->health <= 0)
        return;
    if (IsKeyPressed(KEY_ENTER))
    {
        egg->health -= 1;
    }
}

void reduceEggWarmth(struct eggStruct *egg)
{
    if (egg->warmth <= 0)
        return;
    if (IsKeyPressed(KEY_SPACE))
    {
        egg->warmth -= 1;
    }
}

void increaseEggWarmth(struct eggStruct *egg) {
    if (egg->warmth < 3) {
        egg->warmth += 1;
    }
}   

void drawEggHealthBar(struct eggStruct *egg) {
    // TODO - draw fancy outline
    if (egg->health == 3) {
        DrawRectangle(11, 12, 3, 30, RED);
    }
    if (egg->health == 2) {
        DrawRectangle(11, 22, 3, 20, RED);
    }
    DrawRectangle(11, 32, 3, 10, RED);
}

void drawEggWarmthBar(struct eggStruct *egg) {
    // TODO - draw fancy outline
    if (egg->warmth == 3) {
        DrawRectangle(21, 12, 3, 30, ORANGE);
    }
    if (egg->warmth == 2) {
        DrawRectangle(21, 22, 3, 20, ORANGE);
    }
    DrawRectangle(21, 32, 3, 10, ORANGE);
}

void animateEgg(struct eggStruct *egg, float speed, int screenWidth) {
    int width = screenWidth / 2.0f + 2;

    char *frameTimeString = floatToString(egg->frames, 1);
    char *target = floatToString(egg->target, 1);
    char *burr = floatToString(egg->reducer, 1);

    // get to 60, then vibrate
    if (egg->frames < egg->target) {
        egg->frames += 1;
        return;
    };

    // jiggle egg
    egg->destination.x += 1;

    if (egg->destination.x >= width) {
        egg->destination.x = screenWidth / 2.0f;
    };

    // decrease the reducer
    if (egg->reducer > 0) {
        egg->reducer -= 0.5f;
    };

    //reset
    if (egg->reducer <= 0.0f) {
        egg->frames = 0.0f;
        int randomIndex = rand() % 5;
        int secondRanIndex = rand() % 5;

        float shakeArray[5] = {10.0f, 15.0f, 25.0f, 12.0f, 18.0f};
        egg->reducer = shakeArray[randomIndex];
        egg->target = shakeArray[secondRanIndex];
    }
}