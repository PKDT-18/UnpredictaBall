#include "../game.h"

#define BUTTON_WIDTH  170
#define BUTTON_HEIGHT 45
#define BUTTON_GAP    25

static Rectangle playAgainButton;
static Rectangle mainMenuButton;
static Rectangle exitButton;

void UpdateGameOverScreen(void)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float totalWidth = (BUTTON_WIDTH * 3) + (BUTTON_GAP * 2);
    float startX = (screenWidth - totalWidth) / 2.0f;
    float buttonY = screenHeight * 0.78f;

    playAgainButton = (Rectangle){startX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT};

    mainMenuButton = (Rectangle){
        startX + BUTTON_WIDTH + BUTTON_GAP,
        buttonY, BUTTON_WIDTH, BUTTON_HEIGHT
    };

    exitButton = (Rectangle){
        startX + (BUTTON_WIDTH + BUTTON_GAP) * 2,
        buttonY, BUTTON_WIDTH, BUTTON_HEIGHT
    };

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, playAgainButton))
            ResetMatch();
        else if (CheckCollisionPointRec(mousePosition, mainMenuButton))
            screen = SCREEN_MENU;
        else if (CheckCollisionPointRec(mousePosition, exitButton))
            CloseWindow();
    }
}

void DrawGameOverScreen(void)
{
    ClearBackground(RAYWHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char *title = "GAME OVER!";
    int titleSize = 48;

    DrawText(title,
        screenWidth / 2 - MeasureText(title, titleSize) / 2,
        screenHeight * 0.08f, titleSize, BLACK);

    const char *winner = (p1.score >= 3)
        ? "PLAYER 1 WINS!"
        : "PLAYER 2 WINS!";

    int winnerSize = 32;

    DrawText(winner,
        screenWidth / 2 - MeasureText(winner, winnerSize) / 2,
        screenHeight * 0.25f, winnerSize, BLACK);

    int dividerY = screenHeight * 0.43f;

    DrawLineEx(
        (Vector2){screenWidth * 0.20f, dividerY},
        (Vector2){screenWidth * 0.80f, dividerY},
        3, BLACK);

    DrawCircle(screenWidth * 0.20f, dividerY, 6, BLACK);
    DrawCircle(screenWidth * 0.80f, dividerY, 6, BLACK);

    const char *scoreTitle = "FINAL SCORE";
    int scoreTitleSize = 25;

    DrawText(scoreTitle,
        screenWidth / 2 - MeasureText(scoreTitle, scoreTitleSize) / 2,
        screenHeight * 0.50f, scoreTitleSize, BLACK);

    const char *finalScore = TextFormat("%d - %d", p1.score, p2.score);
    int scoreSize = 48;

    DrawText(finalScore,
        screenWidth / 2 - MeasureText(finalScore, scoreSize) / 2,
        screenHeight * 0.59f, scoreSize, BLACK);

    const char *labels[] = {
        "PLAY AGAIN", "MAIN MENU", "EXIT"
    };

    Rectangle buttons[] = {
        playAgainButton, mainMenuButton, exitButton
    };

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < 3; i++)
    {
        bool hovered = CheckCollisionPointRec(mousePosition, buttons[i]);

        if (hovered)
            DrawRectangleRec(buttons[i], LIGHTGRAY);

        DrawRectangleLinesEx(buttons[i], 2, BLACK);

        int fontSize = 17;

        DrawText(labels[i],
            buttons[i].x + buttons[i].width / 2 -
                MeasureText(labels[i], fontSize) / 2,
            buttons[i].y + buttons[i].height / 2 - fontSize / 2,
            fontSize, BLACK);
    }
}
