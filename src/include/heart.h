#include "raylib.h"
#include "world.h"

#ifndef HEART_H
#define HEART_H

typedef struct heartStruct
{
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    bool isClicked;

} heartStruct;

heartStruct initHeart(int screenWidth, int screenHeight);
void renderHeart(heartStruct heart);
#endif // HEART_H
