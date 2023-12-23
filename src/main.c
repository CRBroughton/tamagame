#include "include/raylib.h"
#include "include/egg.h"
#include "include/utils.h"

#include <stdio.h>
#include <stdlib.h>

void draw(struct eggStruct egg)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    renderEgg(egg);
    char *healthString = intToString(egg.health);
    char *warmthString = intToString(egg.warmth);

    drawEggHealthBar(&egg);
    drawEggWarmthBar(&egg);

    free(healthString);
    free(warmthString);
    EndDrawing();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int screenWidth = 128;
    const int screenHeight = 128;
    // ENABLE DEBUG
    // SetTraceLogLevel(LOG_ERROR);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Texture loading
    struct eggStruct egg = initEgg(screenWidth, screenHeight);

    SetTargetFPS(60);
        float speed = 2.0f;  // Adjust this value based on your preference

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        reduceEggHealth(&egg);
        reduceEggWarmth(&egg);
        animateEgg(&egg, speed, screenWidth);
        draw(egg);
    }

    UnloadTexture(egg.egg);
    CloseWindow(); 
    return 0;
}
