// ****GLOBAL VARIABLES****
int GS = 0; //Green Score
int PS = 0;  //Purple Score
int gameNum = 0;

//Text based versions of scores to print on screen
char Gscore[5] = "0";
char Pscore[5] = "0";

int screenWidth = 1000;
int screenHeight = 800;
int gameWidth = 900;
int gameHeight = 700;

// Game objects
//Vector2 and Rectangle are Raylib structs
Vector2 ballPosition;
Vector2 ballSpeed;
Rectangle greenPaddle;
Rectangle purplePaddle;

int ballRadius = 20;
float paddleHeight = 150.0f;
float bounce;
float freezeTimer = 0.0f;

// Paddle positions
struct rectPos {
    int g;
    int p;
} rectPos;

float resetBall(int direction) {
    ballPosition.x = GetScreenWidth() / 2.0f;
    ballPosition.y = GetScreenHeight() / 2.0f;

    ballSpeed.x = 10 * direction;
    ballSpeed.y = 7;

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
    GS = 0;
    PS = 0;
}

void BuildMapBasic(int screenWidth, int screenHeight) {
    ClearBackground(DARKGRAY);

    DrawLine(0, 25, 1000, 25, WHITE);
    DrawRectangle(50, 50, gameWidth, gameHeight, BLACK);

    DrawText("Press ESC to Exit", 5, 5, 15, WHITE);
    DrawText("Left Player: w + S", 205, 5, 15, WHITE);
    DrawText("Right Player: UpArrow + DownArrow",405, 5, 15, WHITE);
    DrawText("Green Score: ", 50, 760, 30, GREEN);
    DrawText(Gscore, 265, 760, 30, GREEN);
    DrawText("Purple Score: ", 710, 760, 30, PURPLE);
    DrawText(Pscore, 935, 760, 30, PURPLE);
}

// ---------------- INIT GAME ----------------
void InitGame() {
    ballPosition = (Vector2){ screenWidth / 2, screenHeight / 2 };
    ballSpeed = (Vector2){ 10, 7 };

    rectPos.g = screenHeight / 2;
    rectPos.p = screenHeight / 2;

    greenPaddle = (Rectangle){ 75, rectPos.g, 20, 150 };
    purplePaddle = (Rectangle){ 905, rectPos.p, 20, 150 };

    bounce = (rand() % 4 + 10) / 100.0f;
}

// ---------------- GAMEPLAY ----------------
void GamePlay() {

    // Ball collision with walls
    if (ballPosition.x >= (gameWidth+50 - ballRadius)) {
        greenScore();
        freezeTimer = resetBall(-1);
    }

    if (ballPosition.x <= 50+ballRadius) {
        purpleScore();
        freezeTimer = resetBall(1);
    }

    if ((ballPosition.y >= (gameHeight+50 - ballRadius)) || (ballPosition.y <= 50+ballRadius))
        ballSpeed.y *= -1.1f;

    // Paddle collision
    if (CheckCollisionCircleRec(ballPosition, (float)ballRadius, greenPaddle)) {
        if (ballSpeed.x < 0) {
            ballSpeed.x *= -1.1f;
            float paddleCenter = rectPos.g + (paddleHeight / 2.0f);
            float distanceFromCenter = ballPosition.y - paddleCenter;
            ballSpeed.y = distanceFromCenter * bounce;
        }
    }

    if (CheckCollisionCircleRec(ballPosition, (float)ballRadius, purplePaddle)) {
        if (ballSpeed.x > 0) {
            ballSpeed.x *= -1.1f;
            float paddleCenter = rectPos.p + (paddleHeight / 2.0f);
            float distanceFromCenter = ballPosition.y - paddleCenter;
            ballSpeed.y = distanceFromCenter * bounce;
        }
    }

    // Player movement
    if (IsKeyDown(KEY_W)) rectPos.g -= 15;
    if (IsKeyDown(KEY_S)) rectPos.g += 15;

    if (IsKeyDown(KEY_UP)) rectPos.p -= 15;
    if (IsKeyDown(KEY_DOWN)) rectPos.p += 15;

    // Clamp positions
    if (rectPos.g < 50) rectPos.g = 50;
    if (rectPos.g > 600) rectPos.g = 600;

    if (rectPos.p < 50) rectPos.p = 50;
    if (rectPos.p > 600) rectPos.p = 600;

    // Sync paddle positions
    greenPaddle.y = rectPos.g;
    purplePaddle.y = rectPos.p;

    // Move ball
    if (freezeTimer > 0) {
        freezeTimer -= GetFrameTime(); // Slowly counts 1.0 -> 0.0
    } else {
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
    }

    // Draw objects (NO BeginDrawing here)
    DrawRectangleRec(greenPaddle, GREEN);
    DrawRectangleRec(purplePaddle, PURPLE);
    DrawCircleV(ballPosition, ballRadius, WHITE);
}
