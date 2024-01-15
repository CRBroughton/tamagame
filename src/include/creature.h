#include "raylib.h"
#include "world.h"

#ifndef CREATURE_H
#define CREATURE_H

typedef struct creatureStruct
{
    Texture2D texture;
    Texture2D left;
    Texture2D right;
    Vector2 position;
    int x;
    int y;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    Rectangle frameRec;
} creatureStruct;

Texture2D loadCreatureTexture();
Texture2D loadCreatureLeftTexture();
Texture2D loadCreatureRightTexture();
creatureStruct initCreature(Texture2D texture, Texture2D left, Texture2D right);
void initcreaturePosition(creatureStruct *creature);
void renderCreature(creatureStruct *creature);
void updateCreature(creatureStruct * creature);
void moveCreature(creatureStruct *creature);
#endif // CREATURE_H
