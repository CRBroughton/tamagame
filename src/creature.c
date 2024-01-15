#include "include/raylib.h"
#include "include/utils.h"
#include "include/constants.h"
#include "include/creature.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Texture2D loadCreatureTexture()
{
    Texture2D texture = LoadTexture("resources/CreatureSpriteSheet.png");

    return texture;
}

Texture2D loadCreatureLeftTexture()
{
    Texture2D texture = LoadTexture("resources/CreatureLeftSpriteSheet.png");

    return texture;
}

Texture2D loadCreatureRightTexture()
{
    Texture2D texture = LoadTexture("resources/CreatureRightSpriteSheet.png");

    return texture;
}

creatureStruct initCreature(Texture2D texture, Texture2D left, Texture2D right)
{
    int x = 0;
    int y = 0;
    Rectangle frameRec = {
        0.0f,
        0.0f,
        (float)texture.width / 2,
        (float)texture.height,
    };
    Vector2 position = (Vector2){0,0};
    int frameCounter = 0;
    int frameSpeed = 1;
    int currentFrame = 0;

    struct creatureStruct creatureStruct = {
        texture,
        left,
        right,
        position,
        x,
        y,
        frameCounter,
        frameSpeed,
        currentFrame,
        frameRec,
    };

    return creatureStruct;
};

void initcreaturePosition(creatureStruct *creature)
{
    creature->position = (Vector2){
        gameScreenWidth / 2 - creature->frameRec.width * getScaleForTexture(creature->texture) / 2 + creature->x,
        gameScreenHeight / 2 - creature->frameRec.height * getScaleForTexture(creature->texture) / 2 + creature->y,
    };
}

void renderCreature(creatureStruct *creature)
{
    if (IsKeyDown(KEY_A))
    {
        DrawTexturePro(
            creature->left,
            creature->frameRec,
            (Rectangle){
                creature->position.x,
                creature->position.y,
                creature->frameRec.width * getScaleForTexture(creature->texture),
                creature->frameRec.height * getScaleForTexture(creature->texture)},
            (Vector2){0, 0},
            0.0f,
            WHITE);

        return;
    }

    if (IsKeyDown(KEY_D))
    {
        DrawTexturePro(
            creature->right,
            creature->frameRec,
            (Rectangle){
                creature->position.x,
                creature->position.y,
                creature->frameRec.width * getScaleForTexture(creature->texture),
                creature->frameRec.height * getScaleForTexture(creature->texture)},
            (Vector2){0, 0},
            0.0f,
            WHITE);

        return;
    }

    DrawTexturePro(
        creature->texture,
        creature->frameRec,
        (Rectangle){
            creature->position.x,
            creature->position.y,
            creature->frameRec.width * getScaleForTexture(creature->texture),
            creature->frameRec.height * getScaleForTexture(creature->texture)},
        (Vector2){0, 0},
        0.0f,
        WHITE);
}

void updateCreature(creatureStruct *creature)
{
    creature->frameCounter++;

    if (creature->frameCounter >= (60 / creature->frameSpeed))
    {
        creature->frameCounter = 0;
        creature->currentFrame++;

        if (creature->currentFrame > 1)
            creature->currentFrame = 0;

        creature->frameRec.x = (float)creature->currentFrame * (float)creature->texture.width / 2;
    }
}

void moveCreature(creatureStruct *creature)
{
    bool isLeftSideScreen = creature->x <= -256 + creature->texture.width * getScaleForTexture(creature->texture) / 4;
    bool isRightSideScreen = creature->x >= 256 - creature->texture.width *
                                                            getScaleForTexture(creature->texture) / 4;
    if (IsKeyDown(KEY_D) && !isRightSideScreen)
    {
        creature->x += 1;
    }
    if (IsKeyDown(KEY_A) && !isLeftSideScreen)
    {
        creature->x -= 1;
    }
}