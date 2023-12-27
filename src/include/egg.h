#include "raylib.h"
#include "world.h"

#ifndef EGG_H
#define EGG_H

typedef struct eggStruct
{
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    int health;
    int warmth;
    float frames;
    float target;
    float reducer;
    float shakeArray[5];
} eggStruct;

eggStruct initEgg(int screenWidth, int screenHeight);
void renderEgg(eggStruct egg);
void reduceEggHealth(eggStruct *egg, worldStruct *world, double *timer);
void reduceEggWarmth(eggStruct *egg, worldStruct *world, double *timer);
void increaseEggWarmth(eggStruct *egg);
void drawEggHealthBar(eggStruct *egg);
void drawEggWarmthBar(eggStruct *egg);
void animateEgg(eggStruct *egg, float speed, int screenWidth);
#endif // EGG_H
