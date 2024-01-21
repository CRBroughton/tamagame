#include "raylib.h"
#include "world.h"

#ifndef EGG_H
#define EGG_H

typedef struct eggStruct
{
    bool isCracked;
    Rectangle frameRec;
    int frameCounter;
    int frameSpeed;
    int currentFrame;
    Texture2D texture;
    int health;
    int warmth;
    Vector2 eggPosition;
    int x;
    int y;
    int exp;
    float frames;
    float target;
    float reducer;
    float shakeArray[5];
} eggStruct;

eggStruct initEgg(Texture2D texture);
void renderEgg(eggStruct *egg);
void initEggPosition(eggStruct *egg);
void reduceEggHealth(eggStruct *egg, worldStruct *world, double *timer);
void reduceEggWarmth(eggStruct *egg, worldStruct *world, double *timer);
void increaseEggWarmth(eggStruct *egg);
void drawEggHealthBar(eggStruct *egg);
void drawEggWarmthBar(eggStruct *egg, WorldObject warmth);
void drawEggEXPBar(eggStruct *egg, WorldObject exp);
void animateEgg(eggStruct *egg, float speed, int screenWidth);
void crackEgg(eggStruct *egg);
#endif // EGG_H
