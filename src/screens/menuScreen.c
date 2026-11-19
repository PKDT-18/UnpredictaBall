
#include "../game.h"

// Button dimensions and positions
#define BUTTON_WIDTH  300
#define BUTTON_HEIGHT 65
#define BUTTON_GAP    20

Rectangle howToPlayButton;
Rectangle playButton;
Rectangle exitButton;

void UpdateMenuScreen(void)
{
    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;

    // Position the three buttons
    howToPlayButton = (Rectangle) {
        centerX - BUTTON_WIDTH / 2,
        centerY - 70,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    playButton = (Rectangle) {
        centerX - BUTTON_WIDTH / 2,
        centerY + 15,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    exitButton = (Rectangle) {
        centerX - BUTTON_WIDTH / 2,
        centerY + 100,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    // Mouse interaction
    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, howToPlayButton))
        {
            screen = SCREEN_HOW_TO_PLAY;
        }
        else if (CheckCollisionPointRec(mousePosition, playButton))
        {
            screen = SCREEN_GAME;
        }
        else if (CheckCollisionPointRec(mousePosition, exitButton))
        {
            CloseWindow();
        }
    }

    // Keyboard shortcuts
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_P))
    {
        screen = SCREEN_GAME;
    }
}

void DrawMenuScreen(void)
{
    ClearBackground(RAYWHITE);

    const char *title = "MAIN MENU";
    int titleSize = 60;

    DrawText(
        title,
        GetScreenWidth()/2 - MeasureText(title, titleSize)/2,
        GetScreenHeight()/2 - 160,
        titleSize,
        BLACK
    );

    // Button outlines
    DrawRectangleLinesEx(howToPlayButton, 3, BLACK);
    DrawRectangleLinesEx(playButton, 3, BLACK);
    DrawRectangleLinesEx(exitButton, 3, BLACK);

    // Button labels
    const char *labels[] = {
        "How to Play?",
        "Play",
        "Exit"
    };

    Rectangle buttons[] = {
        howToPlayButton,
        playButton,
        exitButton
    };

    for (int i = 0; i < 3; i++)
    {
        int fontSize = 28;

        DrawText(
            labels[i],
            buttons[i].x + buttons[i].width/2 -
                MeasureText(labels[i], fontSize)/2,
            buttons[i].y + buttons[i].height/2 - fontSize/2,
            fontSize,
            BLACK
        );
    }
}

Rectangle backButton;

void UpdateHowToPlayScreen(void)
{
    backButton = (Rectangle) {
        GetScreenWidth()/2 - 150,
        GetScreenHeight() - 110,
        300,
        60
    };

    Vector2 mousePosition = GetMousePosition();

    if (
        IsKeyPressed(KEY_ESCAPE) ||
        (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
         CheckCollisionPointRec(mousePosition, backButton))
    )
    {
        screen = SCREEN_MENU;
    }
}

void DrawHowToPlayScreen(void)
{
    ClearBackground(RAYWHITE);

    const char *title = "HOW TO PLAY";
    int titleSize = 55;

    DrawText(
        title,
        GetScreenWidth()/2 - MeasureText(title, titleSize)/2,
        70,
        titleSize,
        BLACK
    );

    int textSize = 25;
    int centerX = GetScreenWidth()/2;

    DrawText("PLAYER 1", centerX - 350, 210, 30, BLACK);
    DrawText("W - Move Up", centerX - 350, 260, textSize, DARKGRAY);
    DrawText("S - Move Down", centerX - 350, 300, textSize, DARKGRAY);

    DrawText("PLAYER 2", centerX + 80, 210, 30, BLACK);
    DrawText("UP ARROW - Move Up", centerX + 80, 260, textSize, DARKGRAY);
    DrawText("DOWN ARROW - Move Down", centerX + 80, 300, textSize, DARKGRAY);

    DrawText(
        "OBJECTIVE",
        centerX - MeasureText("OBJECTIVE", 30)/2,
        390,
        30,
        BLACK
    );

    const char *objective = "Be the first player to score 3 points!";

    DrawText(
        objective,
        centerX - MeasureText(objective, textSize)/2,
        435,
        textSize,
        DARKGRAY
    );

    DrawRectangleLinesEx(backButton, 3, BLACK);

    const char *back = "BACK TO MAIN MENU";

    DrawText(
        back,
        backButton.x + backButton.width/2 - MeasureText(back, 22)/2,
        backButton.y + 18,
        22,
        BLACK
    );
}
