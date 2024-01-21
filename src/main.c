#include "include/raylib.h"
#include "include/egg.h"
#include "include/world.h"
#include "include/log.h"
#include "include/creature.h"
#include "include/utils.h"
#include "include/constants.h"
#include "include/titleScreen.h"

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
    Texture2D titleScreenTexture = LoadTexture("resources/titleScreen.png");
    Texture2D startTextTexture = LoadTexture("resources/begin.png");
    Texture2D eggTexture = LoadTexture("resources/EggCracking.png");
    Texture2D moonTexture = LoadTexture("resources/Moon/png");
    Texture2D sunTexture = LoadTexture("resources/Sun.png");
    Texture2D grassTexture = LoadTexture("resources/Grass.png");
    Texture2D nightSkyTexture = LoadTexture("resources/Night_Sky.png");
    Texture2D warmthBarTexture = LoadTexture("resources/UI_Bar.png");
    Texture2D clouds1Texture = LoadTexture("resources/Clouds1.png");
    Texture2D creatureTexture = LoadTexture("resources/CreatureSpriteSheet.png");
    Texture2D creatureLeftTexture = LoadTexture("resources/CreatureLeftSpriteSheet.png");
    Texture2D createRightTexture = LoadTexture("resources/CreatureRightSpriteSheet.png");
    Texture2D logTexture = LoadTexture("resources/Log.png");
    Texture2D mountainsTexture = LoadTexture("resources/Mountains.png");

    WorldObject titleScreen = initTitleScreen(titleScreenTexture);
    WorldObject startText = initStartText(startTextTexture);
    eggStruct egg = initEgg(eggTexture);
    worldStruct world = initWorld(grassTexture, moonTexture, sunTexture, nightSkyTexture, mountainsTexture);

    WorldObject warmthBar = initWorldObj(warmthBarTexture);
    WorldObject EXPBar = initWorldObj(warmthBarTexture);
    WorldObject clouds1 = initClouds1(clouds1Texture);
    creatureStruct creature = initCreature(creatureTexture, creatureLeftTexture, createRightTexture);
    logStruct log = initLog(logTexture);
    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);

    SetTargetFPS(60);
    double warmthTimer = GetTime();

    bool game_start = false;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        initTitleScreenPosition(&titleScreen);
        initTitleScreenPosition(&startText);
        initNightSkyPosition(&world.nightSky);
        initGrassPosition(&world.grass);
        initEggPosition(&egg);
        initMoonPosition(&world.moon);
        initSunPosition(&world.sun);
        initWarmthBarPosition(&warmthBar);
        initEXPBarPosition(&EXPBar);
        initClouds1Position(&clouds1);
        initcreaturePosition(&creature);
        initMountainsPositions(&world.mountains);

        UpdateMoonPosition(&world.moon, screenWidth, screenHeight, 260);
        UpdateSunPosition(&world.sun, screenWidth, screenHeight, 260);
        UpdateCloudPosition(&clouds1);

        if (IsKeyPressed(KEY_SPACE) && game_start == false)
        {
            game_start = true;
        }

        if (egg.exp == 3 && egg.isCracked == false)
        {
            crackEgg(&egg);
        }

        if (game_start == true)
        {
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

            Vector2 virtualMouse = getVirtualMousePosition();

            attemptToUseLog(virtualMouse, (Rectangle){log.position.x, log.position.y, log.texture.width * getScaleForTexture(log.texture) / 2, log.texture.height * getScaleForTexture(log.texture) / 2},
                            &egg,
                            &log,
                            &world);

            if (isNightAndMoonVisible(&world.moon, screenHeight) == true)
            {
                reduceEggWarmth(&egg, &world, &warmthTimer);
            }
        }

        updateDayCycle(&world, screenHeight);

        // Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        BeginTextureMode(target);
        ClearBackground(RAYWHITE); // Clear render texture background color
        DrawRectangle(0, 0, gameScreenWidth, gameScreenHeight, (Color){34, 32, 52, 255});
        renderNightSky(world.nightSky);
        renderMoon(&world.moon, screenHeight);
        renderSun(&world.sun, screenHeight);
        renderMountains(world.mountains);
        renderClouds1(clouds1);
        renderGrass(world.grass);

        if (game_start == false)
        {
            renderTitleScreen(titleScreen);
            renderTitleScreen(startText);
        }

        if (game_start == true)
        {
            renderEgg(&egg);

            renderLog(log);

            if (egg.exp == 3 && egg.isCracked == true)
            {
                renderCreature(&creature);
            }

            renderUIBar(warmthBar);
            renderUIBar(EXPBar);
            drawEggWarmthBar(&egg, warmthBar);
            drawEggEXPBar(&egg, EXPBar);
        }
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK); // Clear screen background

        // Draw render texture to screen, properly scaled
        DrawTexturePro(target.texture, (Rectangle){0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height},
                       (Rectangle){(GetScreenWidth() - ((float)gameScreenWidth * getScale())) * 0.5f, (GetScreenHeight() - ((float)gameScreenHeight * getScale())) * 0.5f,
                                   (float)gameScreenWidth * getScale(), (float)gameScreenHeight * getScale()},
                       (Vector2){0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(titleScreenTexture);
    UnloadTexture(startTextTexture);
    UnloadTexture(eggTexture);
    UnloadTexture(moonTexture);
    UnloadTexture(sunTexture);
    UnloadTexture(grassTexture);
    UnloadTexture(nightSkyTexture);
    UnloadTexture(warmthBarTexture);
    UnloadTexture(clouds1Texture);
    UnloadTexture(creatureTexture);
    UnloadTexture(creatureLeftTexture);
    UnloadTexture(createRightTexture);
    UnloadTexture(logTexture);
    UnloadTexture(target.texture);
    CloseWindow();
    return 0;
}
