#include "raylib.h"
#include "world.h"

#ifndef EGG_H
#define EGG_H

typedef struct eggStruct
{
    Texture2D texture;
    int health;
    int warmth;
    Vector2 eggPosition;
    int x;
    int y;
    float frames;
    float target;
    float reducer;
    float shakeArray[5];
} eggStruct;

Texture2D loadEggTexture();
eggStruct initEgg(Texture2D texture, int screenWidth, int screenHeight);
void renderEgg(eggStruct egg);
void initEggPosition(eggStruct *egg);
void reduceEggHealth(eggStruct *egg, worldStruct *world, double *timer);
void reduceEggWarmth(eggStruct *egg, worldStruct *world, double *timer);
void increaseEggWarmth(eggStruct *egg);
void drawEggHealthBar(eggStruct *egg);
void drawEggWarmthBar(eggStruct *egg, uiBar warmth);
void animateEgg(eggStruct *egg, float speed, int screenWidth);
#endif // EGG_H
