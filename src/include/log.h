#include "raylib.h"
#include "world.h"
#include "egg.h"

#ifndef LOG_H
#define LOG_H

typedef struct logStruct
{
    Texture2D texture;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    bool isClicked;

} logStruct;

logStruct initLog(int screenWidth, int screenHeight);
void renderLog(logStruct log);
void attemptToUseLog(Vector2 mousePosition, Rectangle textureRect, eggStruct *egg, logStruct *log, worldStruct *world);
bool spawnNewLog(worldStruct *world);
#endif // LOG_H
