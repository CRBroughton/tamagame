#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/log.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>
#include <stdlib.h>

void draw(worldStruct *world, eggStruct egg, logStruct log, int screenHeight)
{
    // BeginDrawing();

    // ClearBackground(RAYWHITE);

    // renderGrass(world->grass);
    // renderSun(&world->sun, screenHeight);
    // renderMoon(&world->moon, screenHeight);
    // renderEgg(egg);
    // renderLog(log);

    // drawEggHealthBar(&egg);
    // drawEggWarmthBar(&egg);

    // EndDrawing();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    // ENABLE DEBUG
    // SetTraceLogLevel(LOG_ERROR);

    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetWindowMinSize(512, 512);

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT); // Texture scale filter to use
    // Texture2D grass = LoadTexture("resources/Grass.png");
    Texture2D grassTexture = loadGrassTexture();
    Texture2D eggTexture = loadEggTexture();

    // Texture loading

    // TODO - Initialise an array of logs, from which only
    // three can appear at a given time. Use probability function.
    logStruct log = initLog(screenWidth, screenHeight);

    SetTargetFPS(60);
    double warmthTimer = GetTime();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update virtual mouse (clamped mouse value behind game screen)
        Vector2 mouse = GetMousePosition();
        Vector2 virtualMouse = {0};
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (gameScreenWidth * getScale())) * 0.5f) / getScale();
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (gameScreenHeight * getScale())) * 0.5f) / getScale();
        virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0, 0}, (Vector2){(float)gameScreenWidth, (float)gameScreenHeight});

        // Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        ClearBackground(RAYWHITE); // Clear render texture background color

        DrawText("If executed inside a window,\nyou can resize the window,\nand see the screen scaling!", 10, 25, 1, BLACK);
        DrawText(TextFormat("Default Mouse: [%i , %i]", (int)mouse.x, (int)mouse.y), 350, 25, 1, GREEN);
        DrawText(TextFormat("Virtual Mouse: [%i , %i]", (int)virtualMouse.x, (int)virtualMouse.y), 350, 55, 1, BLACK);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK); // Clear screen background

        // Draw render texture to screen, properly scaled
        DrawTexturePro(target.texture, (Rectangle){0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
                       (Rectangle){(GetScreenWidth() - ((float)gameScreenWidth * getScale())) * 0.5f, (GetScreenHeight() - ((float)gameScreenHeight * getScale())) * 0.5f,
                                   (float)gameScreenWidth * getScale(), (float)gameScreenHeight * getScale()},
                       (Vector2){0, 0}, 0.0f, WHITE);

    // worldStruct world = initWorld(grassTexture, screenWidth, screenHeight);

    grassStruct grass = initGrass(grassTexture, screenWidth, screenHeight);
    eggStruct egg = initEgg(eggTexture, screenWidth, screenHeight);

        // draw(&world, egg, log, screenHeight);

        renderGrass(grass);
        renderEgg(egg);

        EndDrawing();


        // TODO - Migrate all the below to above.

        // TODO - Create world state for moon/sun/heat/etc
        // TODO - Create moon + sun orbits
        // Color night = {63, 63, 116, 255};
        // DrawRectangle(0, 0, screenWidth, screenHeight, night);
        // attemptToUseLog(GetMousePosition(), (Rectangle){log.destination.x, log.destination.y, log.texture.width, log.texture.height}, &egg, &log, &world);

        // reduceEggWarmth(&egg, &world, &warmthTimer);
        // updateDayCycle(&world, screenHeight);
        // UpdateMoonPosition(&world.moon, screenWidth, screenHeight, 75);
        // UpdateSunPosition(&world.sun, screenWidth, screenHeight, 75);
        // if (spawnNewLog(&world, &log) == true)
        // {
        //     // TODO - Move probability of log spawning to world
        //     // And randomly show a log in the log array
        //     LogPosition newPosition = getRandomLogPosition();
        //     log.isClicked = false;
        //     log.destination.x = screenWidth / 2 + newPosition.x;
        //     log.destination.y = screenHeight / 2 + newPosition.y;
        // }
    }

    UnloadTexture(target.texture);
    UnloadTexture(grassTexture);
    UnloadTexture(eggTexture);
    // UnloadTexture(world.moon.texture);
    // UnloadTexture(world.sun.texture);
    UnloadTexture(log.texture);
    CloseWindow();
    return 0;
}
