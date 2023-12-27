#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/log.h"
#include "include/utils.h"

#include <stdio.h>
#include <stdlib.h>

void draw(worldStruct *world, eggStruct egg, logStruct log, int screenHeight)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    renderGrass(world->grass);
    renderSun(&world->sun, screenHeight);
    renderMoon(&world->moon, screenHeight);
    renderEgg(egg);
    renderLog(log);

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
    eggStruct egg = initEgg(screenWidth, screenHeight);
    worldStruct world = initWorld(screenWidth, screenHeight);
    logStruct log = initLog(screenWidth, screenHeight);

    SetTargetFPS(60);
    double warmthTimer = GetTime();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // TODO - Create world state for moon/sun/heat/etc
        // TODO - Create moon + sun orbits
        Color night = {63, 63, 116, 255};
        DrawRectangle(0, 0, screenWidth, screenHeight, night);
        performActionOnClick(GetMousePosition(), (Rectangle){log.destination.x, log.destination.y, log.texture.width, log.texture.height}, &egg, &log, &world);

        reduceEggWarmth(&egg, &world, &warmthTimer);
        updateDayCycle(&world, screenHeight);
        UpdateMoonPosition(&world.moon, screenWidth, screenHeight, 75);
        UpdateSunPosition(&world.sun, screenWidth, screenHeight, 75);
        draw(&world, egg, log, screenHeight);

    }

    UnloadTexture(egg.texture);
    UnloadTexture(world.moon.texture);
    UnloadTexture(world.sun.texture);
    UnloadTexture(log.texture);
    CloseWindow();
    return 0;
}
