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

    drawEggHealthBar(&egg);
    drawEggWarmthBar(&egg);

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

    Texture2D moon = LoadTexture("resources/Moon.png");

        Rectangle source = {0.0f, 0.0f, (float)moon.width, (float)moon.height};
    Rectangle destination = {32, 18, moon.width, moon.height};
    Vector2 origin = {moon.width / 2, moon.height / 2};



    SetTargetFPS(60);
        float speed = 2.0f;  // Adjust this value based on your preference

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // TODO - Create world state for moon/sun/heat/etc
        // TODO - Move rendering of moon to world state
        // TODO - Create moon + sun orbits
        Color night = {63, 63, 116, 255};
        DrawRectangle(0, 0, screenWidth, screenHeight, night);
        Color grass = {55, 148, 110, 255};
        DrawRectangle(0, 60, screenWidth, 22, grass);

        DrawTexturePro(moon, source, destination, origin, 0.0f, WHITE);
        reduceEggHealth(&egg);
        reduceEggWarmth(&egg);
        draw(egg);
    }

    UnloadTexture(egg.egg);
    CloseWindow(); 
    return 0;
}
