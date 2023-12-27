#include "raylib.h"
#include "include/world.h"
#include "include/log.h"
#include "include/egg.h"

logStruct initLog(int screenWidth, int screenHeight)
{
    Texture2D texture = LoadTexture("resources/Log.png");

    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destination = {screenWidth / 2 + 10, screenHeight / 2 + 10, texture.width, texture.height};

    bool isClicked = false;

    logStruct logStruct = {
        texture,
        source,
        destination,
        isClicked,
    };

    return logStruct;
}

void renderLog(logStruct log)
{
    if (log.isClicked == false)
    {
        DrawTexturePro(log.texture, log.source, log.destination, log.origin, 0.0f, WHITE);
    }
}

// Function to perform an action when the texture is clicked
void performActionOnClick(Vector2 mousePosition, Rectangle textureRect, eggStruct *egg, logStruct *log, worldStruct *world)
{
    if (
        CheckCollisionPointRec(mousePosition, textureRect) &&
        world->night == true &&
        IsKeyPressed(KEY_SPACE) &&
        egg->warmth < 3)
    {
        egg->warmth += 1;
    }
}