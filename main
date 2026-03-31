#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"

int main()
{
    // Initialization
    int screenWidth = 1000;
    int screenHeight = 800;
    int currentscreen = 0;
    double startTime;
    greenScore();
    purpleScore();

    InitWindow(screenWidth, screenHeight, "Pong window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        BuildMapBasic(screenWidth, screenHeight); // Custom Function

        switch (currentscreen) {
            case 0: {
                // Start Screen
                DrawText("Press Enter to Start Game!", 270, 400, 30, WHITE);
                if (IsKeyPressed(KEY_ENTER))
                    currentscreen = 1;
                    startTime = 0;  //reset timer in case the player goes back to the title screen
                break;
            }

            case 1: {
                //timer
                if (startTime == 0)
                    startTime = GetTime();   // start timer once

                double elapsed = GetTime() - startTime;
                int countdown = 3 - (int)elapsed;

                if (countdown > 0)
                {
                    char text[10];
                    sprintf(text, "%d", countdown);
                    DrawText(text, 495, 350, 80, WHITE);
                }
                else
                {
                    currentscreen = 2;
                }
                break;
            }
            case 2: {
                //playGame()
                DrawText("insert gameplay function here", 250, 400, 30, WHITE);
                break;
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
