#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/utils.h"

#include <stdio.h>
#include <stdlib.h>

void draw(struct eggStruct egg, struct moonStruct moon, struct grassStruct grass)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    renderGrass(grass);
    renderMoon(moon);
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
    struct worldStruct world = initWorld(screenWidth, screenHeight);

    SetTargetFPS(60);
    int timer = GetTime();
    int warmthTimer = GetTime();
    int healthTimer = GetTime();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // TODO - Create world state for moon/sun/heat/etc
        // TODO - Move rendering of moon to world state
        // TODO - Create moon + sun orbits
        Color night = {63, 63, 116, 255};
        DrawRectangle(0, 0, screenWidth, screenHeight, night);
        // Color grass = {55, 148, 110, 255};
        // DrawRectangle(0, 60, screenWidth, 22, grass);

        reduceEggHealth(&egg, &healthTimer);
        reduceEggWarmth(&egg, &world, &warmthTimer);
        updateMoonPhase(&world.moon, &timer);
        draw(egg, world.moon, world.grass);
    }

    UnloadTexture(egg.egg);
    UnloadTexture(world.moon.moon);
    CloseWindow();
    return 0;
}
