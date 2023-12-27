#include "raylib.h"
#include "include/world.h"
#include "include/heart.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

heartStruct initHeart(int screenWidth, int screenHeight)
{
    Texture2D texture = LoadTexture("resources/Log.png");

    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle destination = {screenWidth / 2 + 10, screenHeight / 2 + 10, texture.width, texture.height};

    bool isClicked = false;

    heartStruct heartStruct = {
        texture,
        source,
        destination,
        isClicked,
    };

    return heartStruct;
}

void renderHeart(heartStruct heart)
{
    DrawTexturePro(heart.texture, heart.source, heart.destination, heart.origin, 0.0f, WHITE);
}
