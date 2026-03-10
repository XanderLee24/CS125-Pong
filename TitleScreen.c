#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Initialization
    int screenWidth = 1000;
    int screenHeight = 800;
    int currentscreen = 0;

    InitWindow(screenWidth, screenHeight, "Pong window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);

        DrawLine(0, 25, 1000, 25, WHITE);
        DrawRectangle(50, 50, screenWidth - 100, screenHeight - 100, BLACK);

        DrawText("Press ESC to Exit", 5, 5, 15, WHITE);
        DrawText("Left Player: w + S", 205, 5, 15, WHITE);
        DrawText("Right Player: UpArrow + DownArrow",405, 5, 15, WHITE);


        switch (currentscreen) {
            case 0: {
                // Start Screen
                DrawText("Press Enter to Start Game!", 250, 400, 30, WHITE);
                if (IsKeyPressed(KEY_ENTER))
                    currentscreen = 1;
                break;

            }
            case 1: {
                //timer
                
                //playGame()
                DrawText("insert gameplay function here", 250, 400, 30, WHITE);
                //break;
            }
        }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
