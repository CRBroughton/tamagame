#include "raylib.h"
#include "world.h"

#ifndef CREATURE_H
#define CREATURE_H

typedef struct creatureStruct
{
    Texture2D texture;
    Vector2 position;
    int x;
    int y;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    Rectangle frameRec;
} creatureStruct;

Texture2D loadCreatureTexture();
creatureStruct initCreature(Texture2D texture);
void initcreaturePosition(creatureStruct *creature);
void renderCreature(creatureStruct *creature);
void updateCreature(creatureStruct * creature);
#endif // CREATURE_H
