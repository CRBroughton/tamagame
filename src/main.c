#include "include/raylib.h"
#include "include/egg.h"
#include <stdio.h>
#include <stdlib.h>

char* intToString(int number) {
    char *result;
    // Using asprintf to convert int to char *
    if (asprintf(&result, "%d", number) == -1) {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return result;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 128;
    const int screenHeight = 128;
    // ENABLE DEBUG
// SetTraceLogLevel(LOG_ERROR); 

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Texture loading
    struct eggStruct egg = initEgg(screenWidth, screenHeight);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        reduceEggHealth(&egg);

        reduceEggWarmth(&egg);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            renderEgg(egg);
            char *healthString = intToString(egg.health);
            char *warmthString = intToString(egg.warmth);

        drawEggHealthBar(&egg);
        drawEggWarmthBar(&egg);

            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

      // NOTE: Using DrawTexturePro() we can easily rotate and scale the part of the texture we draw
            // sourceRec defines the part of the texture we use for drawing
            // destRec defines the rectangle where our texture part will fit (scaling it to fit)
            // origin defines the point of the texture used as reference for rotation and scaling
            // rotation defines the texture rotation (using origin as rotation point)
            // DrawTexturePro(egg, sourceRec, destRec, origin, 0.0f, WHITE);
        free(healthString);
        free(warmthString);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(egg.egg);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

