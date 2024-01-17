#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/log.h"
#include "include/creature.h"
#include "include/utils.h"
#include "include/constants.h"

#include <stdio.h>
#include <stdlib.h>

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
    SetWindowMinSize(128, 128);

    // // Texture loading
    Texture2D eggTexture = loadEggTexture();
    Texture2D moonTexture = renderMoonTexture();
    Texture2D sunTexture = loadSunTexture();
    Texture2D grassTexture = loadGrassTexture();
    Texture2D nightSkyTexture = loadNightSkyTexture();
    Texture2D warmthBarTexture = loadWarmthTexture();
    Texture2D clouds1Texture = loadCloud1Texture();
    Texture2D creatureTexture = loadCreatureTexture();
    Texture2D creatureLeftTexture = loadCreatureLeftTexture();
    Texture2D createRightTexture = loadCreatureRightTexture();
    Texture2D logTexture = loadLogTexture();

    eggStruct egg = initEgg(eggTexture);
    worldStruct world = initWorld(grassTexture, moonTexture, sunTexture, nightSkyTexture);

    uiBar warmthBar = initWarmthBar(warmthBarTexture);
    clouds clouds1 = initClouds1(clouds1Texture);
    creatureStruct creature = initCreature(creatureTexture, creatureLeftTexture, createRightTexture);
    logStruct log = initLog(logTexture);

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    // // TODO - Initialise an array of logs, from which only
    // // three can appear at a given time. Use probability function.
    // logStruct log = initLog(screenWidth, screenHeight);

    SetTargetFPS(60);
    double warmthTimer = GetTime();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        initNightSkyPosition(&world.nightSky);
        initGrassPosition(&world.grass);
        initEggPosition(&egg);
        initMoonPosition(&world.moon);
        initSunPosition(&world.sun);
        initWarmthBarPosition(&warmthBar);
        initClouds1Position(&clouds1);
        initcreaturePosition(&creature);

        UpdateMoonPosition(&world.moon, screenWidth, screenHeight, 320);
        UpdateSunPosition(&world.sun, screenWidth, screenHeight, 320);
        clouds1.x -= 1;

        if (clouds1.x < -300)
        {
            clouds1.x = 500;
        };

        updateCreature(&creature);
        moveCreature(&creature);

        if (spawnNewLog(&world, &log) == true)
        {
            // TODO - Move probability of log spawning to world
            // And randomly show a log in the log array
            LogPosition newPosition = getRandomLogPosition();
            log.isClicked = false;
            log.position = (Vector2){
                gameScreenWidth / 2 - log.texture.width * getScaleForTexture(log.texture) / 4 + newPosition.x,
                gameScreenHeight / 2 - log.texture.height * getScaleForTexture(log.texture) / 4 + newPosition.y,
            };
        }

        attemptToUseLog(GetMousePosition(), (Rectangle){log.position.x, log.position.y, log.texture.width, log.texture.height},
                        &egg,
                        &log,
                        &world);

        // Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        ClearBackground(RAYWHITE); // Clear render texture background color
        renderNightSky(world.nightSky);
        renderMoon(&world.moon, screenHeight);
        renderSun(&world.sun, screenHeight);
        renderClouds1(clouds1);
        renderGrass(world.grass);
        renderEgg(egg);
        if (spawnNewLog(&world, &log) == true)
        {
            renderLog(log);
        }
        renderCreature(&creature);
        renderWarmthBar(warmthBar);
        drawEggWarmthBar(&egg, warmthBar);

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK); // Clear screen background

        // Draw render texture to screen, properly scaled
        DrawTexturePro(target.texture, (Rectangle){0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
                       (Rectangle){(GetScreenWidth() - ((float)gameScreenWidth * getScale())) * 0.5f, (GetScreenHeight() - ((float)gameScreenHeight * getScale())) * 0.5f,
                                   (float)gameScreenWidth * getScale(), (float)gameScreenHeight * getScale()},
                       (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();

        // TODO - Migrate all the below to above.

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
    UnloadTexture(eggTexture);
    UnloadTexture(moonTexture);
    UnloadTexture(sunTexture);
    UnloadTexture(grassTexture);
    UnloadTexture(clouds1Texture);
    CloseWindow();
    return 0;
}
