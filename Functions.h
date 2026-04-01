#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "raylib.h"

// ****GLOBAL VARIABLES****
int GS = 0; //Green Score
int PS = 0;  //Purple Score
int gameNum = 0;

// Text based versions of scores to print on screen
char Gscore[5] = "0";
char Pscore[5] = "0";

// Window and Game Screen Sizes
int screenWidth = 1000;
int screenHeight = 800;
int gameWidth = 900;
int gameHeight = 700;

// ----Game objects----
// Vector2 and Rectangle are Raylib Structs
Vector2 ballPosition;
Vector2 ballSpeed;
Rectangle greenPaddle;
Rectangle purplePaddle;

int ballRadius = 20;
float paddleHeight = 150.0f;
float paddleWidth = 20.0f;
float bounce;
float freezeTimer = 0.0f;

// Paddle positions
struct rectPos {
    int g;
    int p;
} rectPos;

// ****Functions****
int randBallLaunch(int x) {
    if ((rand()% 2 + 1) == 1) {
        return x;  // If rand=1 ball launches down/left
    }

    else {
        return x*-1;  // Else, the ball launches up/right
    }
}

float resetBall(int direction) {
    //Center Ball (After a Score)
    ballPosition.x = GetScreenWidth() / 2.0f;
    ballPosition.y = GetScreenHeight() / 2.0f;

    // Ball Vector Direction (After a Score)
    ballSpeed.x = 10 * direction;  //Initial direction decided by previous winner
    ballSpeed.y = randBallLaunch(7);  // Randomized

    return 1.5f;
}

void greenScore() {
    GS++;
    sprintf(Gscore, "%d", GS);
}

void purpleScore() {
    PS++;
    sprintf(Pscore, "%d", PS);
}

void keepScore() {
    FILE* score = fopen("score.txt", "a");
    fprintf(score, "Game %d: \nGreen Score: %d\n Purple Score: %d\n\n", gameNum, GS, PS);
    fclose(score);
}

void resetScore() {
    GS = 0; //Green Score
    PS = 0;  //Purple Score
    strcpy(Gscore, "0");
    strcpy(Pscore, "0");
}

// NOTE**(Raylib Y-axis begins from the top)
void buildMapBasic(int screenWidth, int screenHeight) { //Stages consistent map features
    ClearBackground(DARKGRAY);

    //Game Play Area
    DrawRectangle(50, 50, gameWidth, gameHeight, BLACK);

    //Instructions Bar
    DrawLine(0, 25, 1000, 25, WHITE);
    DrawText("Press ESC to Exit", 5, 5, 15, WHITE);
    DrawText("Left Player: w + S", 205, 5, 15, WHITE);
    DrawText("Right Player: UpArrow + DownArrow",405, 5, 15, WHITE);
    DrawText("Press Enter to End Game",800, 5, 15, PINK);

    //Scores
    DrawText("Green Score: ", 50, 760, 30, GREEN);
    DrawText(Gscore, 265, 760, 30, GREEN);
    DrawText("Purple Score: ", 710, 760, 30, PURPLE);
    DrawText(Pscore, 935, 760, 30, PURPLE);
}

// Set Ball/Paddle Locations and Features
void initGame() {
    // Set Ball in the Center of Screen and Randomize Vectors
    ballPosition = (Vector2){ screenWidth / 2, screenHeight / 2 };
    ballSpeed = (Vector2){ randBallLaunch(10), randBallLaunch(7) };

    // Position Paddles Halfway Up Screen
    rectPos.g = screenHeight / 2;
    rectPos.p = screenHeight / 2;

    // Set Size of Paddles
    greenPaddle = (Rectangle){ 75, rectPos.g, paddleWidth, paddleHeight };
    purplePaddle = (Rectangle){ 905, rectPos.p, paddleWidth, paddleHeight };

    bounce = (rand() % 4 + 10) / 100.0f;  //Random bounce coefficient

    // Momentarily Freeze Ball on Game Initialization
    freezeTimer = 1.5f;
}

// ****GAMEPLAY****
void gamePlay() {
    // ----Collision----
    // ....Ball Collision With Walls....
    if (ballPosition.x >= (gameWidth+50 - ballRadius)) {  //Ball hits purple side (green score)
        greenScore();
        freezeTimer = resetBall(-1);  //Resets ball and sets direction of ball vector
    }

    if (ballPosition.x <= 50+ballRadius) {  //Ball hits green side (purple score)
        purpleScore();
        freezeTimer = resetBall(1);  //Resets ball and sets direction of ball vector
    }

    // Ball Upper and Lower Bounds
    if ((ballPosition.y >= (gameHeight+50 - ballRadius)) || (ballPosition.y <= 50+ballRadius))
        ballSpeed.y *= -1.1f;  //Changes direction and increases speed with floor or roof collision

    // ....Paddle Collision....
    if (CheckCollisionCircleRec(ballPosition, (float)ballRadius, greenPaddle)) {
        if (ballSpeed.x < 0) {  //Moving towards green paddle
            ballSpeed.x *= -1.1f;  //Changes direction and increases speed with paddle collision
            float paddleCenter = rectPos.g + (paddleHeight / 2.0f);  //Vertical paddle center
            float distanceFromCenter = ballPosition.y - paddleCenter;  //Calculate ball's distance from center
            ballSpeed.y = distanceFromCenter * bounce;  //Adjust ball's vertical speed based on paddle hit location
        }
    }

    if (CheckCollisionCircleRec(ballPosition, (float)ballRadius, purplePaddle)) {
        if (ballSpeed.x > 0) {  //Moving towards purple paddle
            ballSpeed.x *= -1.1f;  //Changes direction and increases speed with paddle collision
            float paddleCenter = rectPos.p + (paddleHeight / 2.0f);  //Vertical paddle center
            float distanceFromCenter = ballPosition.y - paddleCenter;  //Calculate ball's distance from center
            ballSpeed.y = distanceFromCenter * bounce;  //Adjust ball's vertical speed based on paddle hit location
        }
    }

    // ----Player Movement----
    // Green Character Movement
    if (IsKeyDown(KEY_W)) rectPos.g -= 15;  //UP
    if (IsKeyDown(KEY_S)) rectPos.g += 15;  //Down

    // Purple Character Movement
    if (IsKeyDown(KEY_UP)) rectPos.p -= 15;  //Up
    if (IsKeyDown(KEY_DOWN)) rectPos.p += 15;  //Down

    // ....Restrict Positions (Min to Max Height)....
    // Green Range
    if (rectPos.g < 50) rectPos.g = 50;  //Max height
    if (rectPos.g > 600) rectPos.g = 600;  //Min Height

    // Purple Range
    if (rectPos.p < 50) rectPos.p = 50; //Max Height
    if (rectPos.p > 600) rectPos.p = 600;  //Min Height

    // Sync Paddle Positions
    greenPaddle.y = rectPos.g;
    purplePaddle.y = rectPos.p;

    // ----Ball Movement----
    if (freezeTimer > 0) {  //Freezes the ball in place after a score to make the next round start smoother
        freezeTimer -= GetFrameTime(); // Slowly counts 1.0 -> 0.0
    } else {
        // Begin Moving the Ball Again
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
    }

    // Draw Objects
    DrawRectangleRec(greenPaddle, GREEN);
    DrawRectangleRec(purplePaddle, PURPLE);
    DrawCircleV(ballPosition, ballRadius, WHITE);
}
