#include "include/raylib.h"
#include "include/egg.h"

struct eggStruct initEgg(int screenWidth, int screenHeight)
{

    Texture2D egg = LoadTexture("resources/Closed_Egg.png");

    Rectangle source = {0.0f, 0.0f, (float)egg.width, (float)egg.height};
    Rectangle destination = {screenWidth / 2.0f, screenHeight / 2.0f, egg.width, egg.height};
    Vector2 origin = {egg.width / 2, egg.height / 2};

    const int health = 3;
    const int warmth = 3;

    struct eggStruct eggStruct = {
        egg,
        source,
        destination,
        origin,
        health,
        warmth,
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