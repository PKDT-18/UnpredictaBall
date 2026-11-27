#include "game.h"

PowerupSystem powerupSystem;
PowerupPlayer powerupPlayers[2];
PowerupBall powerupBall;
PowerupOrb powerupOrb;

void InitGame()
{
    PowerupOrb_Init(&powerupOrb);
    powerupOrb.spawnTimer = POWERUP_RESPAWN_TIME;

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

    // Power-ups
    powerupPlayers[0] = (PowerupPlayer) {
        PLAYER_SPEED,
        playerSize.y,
        PLAYER_SPEED,
        playerSize.y,
        0,
        0
    };

    powerupPlayers[1] = powerupPlayers[0];

    powerupBall.base_alpha = 1.0f;
    powerupBall.alpha = 1.0f;

    Powerup_Init(&powerupSystem, powerupPlayers, &powerupBall);
}

void ResetMatch()
{
    PowerupOrb_Init(&powerupOrb);
    powerupOrb.spawnTimer = POWERUP_RESPAWN_TIME;

    // Reset scores and player positions
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

    // Reset ball
    ballPosition = (Vector2) {
        GetScreenWidth()/2,
        GetScreenHeight()/2
    };

    ballSpeed = DEFAULT_BALL_SPEED;
    InitBallDirection(&ballDirection, -PI/4 + GetRandomValue(0, 1)*PI/2);

    // Reset game counters
    framesCounter = 1;
    pauseFrames = 0;

    Powerup_Init(&powerupSystem, powerupPlayers, &powerupBall);

    // Start a new match
    screen = SCREEN_GAME;
}

void UpdateFrame()
{
    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }

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
        UpdateGameOverScreen();
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
        DrawGameOverScreen();
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