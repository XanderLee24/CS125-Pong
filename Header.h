/*
Contributors:
Xander Lee
Thomas Silva
*/

#ifndef PONG_HEADER_H
#define PONG_HEADER_H

int randBallLaunch(int x);
float resetBall(int direction);
void greenScore();
void purpleScore();
long timeStamp();
void keepScore(long now);
void resetScore();
void buildMapBasic(int screenWidth, int screenHeight);
void initGame();
void gamePlay();
void forLoop();

// ****GLOBAL VARIABLES****
extern int GS; //Green Score
extern int PS;  //Purple Score
extern int gameNum;

// Text based versions of scores to print on screen
extern char Gscore[5];
extern char Pscore[5];

// Window and Game Screen Sizes
extern int screenWidth;
extern int screenHeight;
extern int gameWidth;
extern int gameHeight;

// ----Game objects----
// Vector2 and Rectangle are Raylib Structs
extern Vector2 ballPosition;
extern Vector2 ballSpeed;
extern Rectangle greenPaddle;
extern Rectangle purplePaddle;

extern int ballRadius;
extern float paddleHeight;
extern float paddleWidth;
extern float bounce;
extern float freezeTimer;

// Paddle positions
extern struct rectPos;

#endif //PONG_HEADER_H
