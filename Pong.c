#include "raylib.h"
#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    // ****Initialization****
    int currentScreen = 0;  //Start screen
    double startTime;  //Later used for timer

    InitWindow(screenWidth, screenHeight, "Pong window");  //Opens GUI
    srand(time(NULL));  //Random seed
    initGame();

    SetTargetFPS(60);  //Set game to run at 60 frames-per-second

    // ****Main game loop****
    while (!WindowShouldClose()) {  //Detect window close button or ESC key
        BeginDrawing();
        buildMapBasic(screenWidth, screenHeight);

        // ----Game movement between states----
        switch (currentScreen) {
            // ....Start Screen....
            case 0: {
                DrawText("Press Enter to Start Game!", 270, 400, 30, WHITE);
                if (IsKeyPressed(KEY_ENTER))  //Change game states if enter is pressed
                    currentScreen = 1;  //Countdown
                    startTime = 0;  //Reset timer between games
                break;
            }

            // ....Timer....
            case 1: {
                if (startTime == 0)  //Prevents the timer from resetting every frame
                    startTime = GetTime();

                // Keeps Track of Time Waiting
                double elapsed = GetTime() - startTime;
                int countdown = 3 - (int)elapsed;

                //While timer isn't 0
                if (countdown > 0) {
                    //Draws seconds left on screen
                    char text[10];
                    sprintf(text, "%d", countdown);
                    DrawText(text, 495, 350, 80, WHITE);
                }

                // When Timer Hits 0
                else {
                    resetScore();
                    currentScreen = 2;  //Game play
                }
                break;
            }

            // ....Game Play....
            case 2: {
                gamePlay();
                if (IsKeyPressed(KEY_ENTER)) {  //Move to score screen if enter is pressed
                    keepScore();  //Save Score in file
                    currentScreen = 3;  //Score screen
                }
                break;
            }

            // ....Score Screen....
            case 3: {
                //Draw Score Features
                DrawText("SCORE: ", 385, (screenHeight/2)-80, 75, PINK);
                DrawRectangle(225, screenHeight/2, 550, 25, WHITE);
                DrawText(Gscore, (screenWidth/2)-125, (screenHeight/2)+50, 75, GREEN);
                DrawText(Pscore, (screenWidth/2)+125, (screenHeight/2)+50, 75, PURPLE);
                DrawText("Press Enter to Play Again", (screenWidth/2)-345   , (screenHeight/2)-200, 50, PINK);

                if (IsKeyPressed(KEY_ENTER)) {  //Move back to timer if enter is pressed
                    currentScreen = 1;  //Timer
                    startTime = 0;  //reset timer in case the player goes back to the title screen
                }
                break;
            }
        }



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    return 0;
}
