#ifndef CRAYPONG_GAME_H
#define CRAYPONG_GAME_H

#include "stdbool.h"
#include "math.h"
#include "stdio.h"

#include "config.h"
#include "types.h"
#include "utils.h"
#include "screens/welcomeScreen.h"


//--------------------------------------------------
// Shared variables
//--------------------------------------------------
extern SCREEN screen;
extern MODE mode;
extern int framesCounter;

extern bool showDebug;
extern int pauseFrames;

// players
extern Player p1, p2;

// ball
extern Vector2 ballPosition, ballDirection;
extern float ballSpeed;

// sounds
extern Sound playerBeep, wallBeep;


//--------------------------------------------------
// Game functions
//--------------------------------------------------
void InitGame();
void UpdateFrame();
void DrawFrame();
void UnloadGame();
void ResetMatch(void);



//--------------------------------------------------
// Update & Draw functions
//--------------------------------------------------

void UpdateWelcomeScreen(void);
void DrawWelcomeScreen(void);

void UpdateHowToPlayScreen(void);
void DrawHowToPlayScreen(void);

void UpdateMenuScreen();
void DrawMenuScreen();

void UpdateGameScreen();
void DrawGameScreen();

void UpdatePauseScreen();
void DrawPauseScreen();

void RestartGame(void);

void UpdatePointScreen();
void DrawPointScreen();

void UpdateGameOverScreen(void);
void DrawGameOverScreen(void);

#endif //CRAYPONG_GAME_H