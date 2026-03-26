int GS = 0;
int PS = 0;
int gameNum = 0;
char Gscore[5];
char Pscore[5];


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
    DrawRectangle(50, 50, screenWidth - 100, screenHeight - 100, BLACK);

    DrawText("Press ESC to Exit", 5, 5, 15, WHITE);
    DrawText("Left Player: w + S", 205, 5, 15, WHITE);
    DrawText("Right Player: UpArrow + DownArrow",405, 5, 15, WHITE);
    DrawText("Green Score: ", 50, 760, 30, GREEN);
    DrawText(Gscore, 265, 760, 30, GREEN);
    DrawText("Purple Score: ", 710, 760, 30, PURPLE);
    DrawText(Pscore, 935, 760, 30, PURPLE);
}
