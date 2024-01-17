#include "raylib.h"
#include "world.h"
#include "egg.h"

#ifndef LOG_H
#define LOG_H

typedef struct logStruct
{
    Texture2D texture;
    Vector2 position;
    bool isClicked;

} logStruct;


typedef struct LogPosition {
    int x;
    int y;
} LogPosition;

Texture2D loadLogTexture();
logStruct initLog(Texture2D texture);
void renderLog(logStruct log);
void attemptToUseLog(Vector2 mousePosition, Rectangle textureRect, eggStruct *egg, logStruct *log, worldStruct *world);
bool spawnNewLog(worldStruct *world, logStruct *log);
LogPosition getRandomLogPosition();
#endif // LOG_H
