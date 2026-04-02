/*
Contributors:
Xander Lee
Thomas Silva
*/

#include "raylib.h"
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    // ****Initialization****
    int currentScreen = 0;  //Start screen
    double startTime;  //Later used for timer
    long now = timeStamp();  //Save game session time stamp for score.txt

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
                    resetScore();  //Resets score every time a new game is about to start
                    currentScreen = 2;  //Game play
                }
                break;
            }

            // ....Game Play....
            case 2: {
                gamePlay();
                if (IsKeyPressed(KEY_ENTER)) {  //Move to score screen if enter is pressed
                    keepScore(now);  //Save score in file
                    gameNum++;  //Update number
                    currentScreen = 3;  //Score screen
                }
                break;
            }

            // ....Score Screen....
            case 3: {
                //Draw Score Features
                DrawText("SCORE: ", 365, (screenHeight/2)-80, 75, PINK);
                DrawRectangle(225, screenHeight/2, 550, 25, WHITE);
                DrawText(Gscore, (screenWidth/2)-150, (screenHeight/2)+50, 75, GREEN);
                DrawText(Pscore, (screenWidth/2)+115, (screenHeight/2)+50, 75, PURPLE);
                DrawText("Press Enter to Play Again", (screenWidth/2)-345   , (screenHeight/2)-200, 50, PINK);

                if (IsKeyPressed(KEY_ENTER)) {  //Move back to timer if enter is pressed
                    initGame();  // Reset paddle positions, ball vectors, and ball freeze
                    currentScreen = 1;  //Timer
                    startTime = 0;  //reset timer in case the player goes back to the title screen
                }
                break;
            }
        }

        EndDrawing();
    }

    // ****De-Initialization****
    if (currentScreen == 2) { //Log score if players close game mid-match
        keepScore(now);
    }

    CloseWindow();
    forLoop();
    return 0;
}
