#ifndef EGG_H
#define EGG_H

typedef struct eggStruct
{
    // int health;
    // int warmth;
    Texture2D egg;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    int health;
    int warmth;
} eggStruct;

struct eggStruct initEgg(int screenWidth, int screenHeight);
void renderEgg(struct eggStruct egg);
void reduceEggHealth(struct eggStruct *egg);
void reduceEggWarmth(struct eggStruct *egg);
void increaseEggWarmth(struct eggStruct *egg);
void drawEggHealthBar(struct eggStruct *egg);
void drawEggWarmthBar(struct eggStruct *egg);
#endif // EGG_H
