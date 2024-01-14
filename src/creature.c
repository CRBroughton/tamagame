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

creatureStruct initCreature(Texture2D texture)
{
    int x = 0;
    int y = -20;
    Vector2 position = (Vector2){
        gameScreenWidth / 2 - (texture.width * getScale()) / 2 + x,
        gameScreenHeight / 2 - (texture.height * getScale()) / 2 + y,
    };
    int frameCounter = 0;
    int frameSpeed = 1;
    int currentFrame = 0;
    Rectangle frameRec = {
        0.0f,
        0.0f,
        (float)texture.width / 2,
        (float)texture.height,
    };

    struct creatureStruct creatureStruct = {
        texture,
        position,
        x,
        y,
        frameCounter,
        frameSpeed,
        currentFrame,
        frameRec,
    };
    frameRec.x = (float)currentFrame * (float)texture.width / 6;

    return creatureStruct;
};

void initcreaturePosition(creatureStruct *creature)
{
    creature->position = (Vector2){
        gameScreenWidth / 2 - (creature->texture.width * getScaleForTexture(creature->texture)) / 4 + creature->x,
        gameScreenHeight / 2 - (creature->texture.height * getScaleForTexture(creature->texture)) / 4 + creature->y,
    };
}

void renderCreature(creatureStruct *creature)
{

    DrawTexturePro(
        creature->texture,
        creature->frameRec,
        (Rectangle){
            creature->position.x,
            creature->position.y,
            creature->frameRec.width * 3,
            creature->frameRec.height * 3},
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