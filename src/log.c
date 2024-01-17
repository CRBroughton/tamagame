#include "raylib.h"
#include "include/world.h"
#include "include/log.h"
#include "include/egg.h"
#include "include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Texture2D loadLogTexture()
{
    Texture2D texture = LoadTexture("resources/Log.png");

    return texture;
}

logStruct initLog(Texture2D texture)
{
    bool isClicked = false;

    Vector2 position = (Vector2){0,0};

    logStruct logStruct = {
        texture,
        position,
        isClicked,
    };

    return logStruct;
}

void renderLog(logStruct log)
{
    if (log.isClicked == false)
    {
        // DrawTexturePro(log.texture, log.source, log.destination, log.origin, 0.0f, WHITE);
        DrawTextureEx(log.texture, log.position, 0.0f, getScaleForTexture(log.texture) / 2, WHITE);
    }
}

void attemptToUseLog(Vector2 mousePosition, Rectangle textureRect, eggStruct *egg, logStruct *log, worldStruct *world)
{
    if (
        CheckCollisionPointRec(mousePosition, textureRect) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        egg->warmth < 3)
    {
        egg->warmth += 1;
        log->isClicked = true;
    }
}

bool spawnNewLog(worldStruct *world, logStruct *log) {
    return true;
    if (log->isClicked == false) {
        return false;
    }
    if (world->night == false) {
        return false;
    }

    float randomValue = ((float)rand() / (float)RAND_MAX); // Generate a random float between 0 and 1
    
    float probability = 0.005f;

    if (randomValue < probability) {
       return true;
    } else {
        return false;
    }
}

LogPosition getRandomLogPosition() {
    const int ARRAY_SIZE = 3;
    LogPosition possiblePositions[ARRAY_SIZE] = {
        {x: 10, y: 10},
        {x: 20, y: 10},
        {x: 30, y: 15}};

    srand((unsigned int)time(NULL));

    int randomIndex = rand() % ARRAY_SIZE;

    return possiblePositions[randomIndex];
};

