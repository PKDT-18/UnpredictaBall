
#include "game.h"
#include "screens/welcomeScreen.h"

void InitGame()
{
    screen = SCREEN_WELCOME;
    mode = MODE_2PLAYERS;
    framesCounter = 1;

    showDebug = false;
    pauseFrames = 0;

    // Players
    p1 = (Player) {
        {10, GetScreenHeight()/2 - playerSize.y/2},
        0,
        false
    };

    p2 = (Player) {
        {GetScreenWidth() - playerSize.x - 10,
         GetScreenHeight()/2 - playerSize.y/2},
        0,
        false
    };

    // Ball
    ballPosition = (Vector2) {
        GetScreenWidth()/2,
        GetScreenHeight()/2
    };

    ballSpeed = DEFAULT_BALL_SPEED;
    InitBallDirection(&ballDirection, -PI/4 + GetRandomValue(0, 1)*PI/2);

    // Sounds
    playerBeep = LoadSound("resources/playerBeep.wav");
    wallBeep = LoadSound("resources/wallBeep.wav");
}

void UpdateFrame()
{
    switch (screen) {
        case SCREEN_WELCOME:
            UpdateWelcomeScreen();
            break;

        case SCREEN_MENU:
            UpdateMenuScreen();
            break;

        case SCREEN_HOW_TO_PLAY:
            UpdateHowToPlayScreen();
            break;

        case SCREEN_GAME:
            UpdateGameScreen();
            break;

        case SCREEN_POINT:
            UpdatePointScreen();
            break;

        case SCREEN_PAUSE:
            UpdatePauseScreen();
            break;

        case SCREEN_GAME_OVER:
            break;

        default:
            break;
    }
}

void DrawFrame()
{
    switch (screen) {
        case SCREEN_WELCOME:
            DrawWelcomeScreen();
            break;

        case SCREEN_MENU:
            DrawMenuScreen();
            break;

        case SCREEN_HOW_TO_PLAY:
            DrawHowToPlayScreen();
            break;

        case SCREEN_GAME:
            DrawGameScreen();
            break;

        case SCREEN_POINT:
            DrawGameScreen();
            DrawPointScreen();
            break;

        case SCREEN_PAUSE:
            DrawGameScreen();
            DrawPauseScreen();
            break;

        case SCREEN_GAME_OVER:
            break;

        default:
            break;
    }
}

void UnloadGame()
{
    UnloadSound(playerBeep);
    UnloadSound(wallBeep);
}

void RestartGame()
{
    InitGame();
}