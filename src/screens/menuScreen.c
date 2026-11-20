#include "../game.h"

// Button dimensions and positions
#define BUTTON_WIDTH  300
#define BUTTON_HEIGHT 65
#define BUTTON_GAP    20

Rectangle howToPlayButton;
Rectangle playButton;
Rectangle exitButton;
Rectangle menuHeading;
Rectangle backButton;

void UpdateMenuScreen(void)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Main Menu heading
    menuHeading = (Rectangle) {
        screenWidth / 2.0f - 100,
        screenHeight * 0.46f,
        200,
        45
    };

    // Button dimensions
    float buttonWidth = 170;
    float buttonHeight = 45;
    float buttonGap = 55;

    // Centered button positions
    float totalWidth = (buttonWidth * 3) + (buttonGap * 2);
    float startX = (screenWidth - totalWidth) / 2.0f;
    float buttonY = screenHeight * 0.64f;

    howToPlayButton = (Rectangle) {
        startX, buttonY, buttonWidth, buttonHeight
    };

    playButton = (Rectangle) {
        startX + buttonWidth + buttonGap,
        buttonY,
        buttonWidth,
        buttonHeight
    };

    exitButton = (Rectangle) {
        startX + (buttonWidth + buttonGap) * 2,
        buttonY,
        buttonWidth,
        buttonHeight
    };

    // Mouse interaction
    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mousePosition, howToPlayButton))
            screen = SCREEN_HOW_TO_PLAY;
        else if (CheckCollisionPointRec(mousePosition, playButton))
            screen = SCREEN_GAME;
        else if (CheckCollisionPointRec(mousePosition, exitButton))
            CloseWindow();
    }

    // Keyboard shortcuts
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_P))
        screen = SCREEN_GAME;
}

void DrawMenuScreen(void)
{
    ClearBackground(RAYWHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    

    // Game title
    const char *title = "UNPREDICTABALL";
    int titleSize = 52;

    DrawText(
        title,
        screenWidth / 2 - MeasureText(title, titleSize) / 2,
        screenHeight * 0.18f,
        titleSize,
        BLACK
    );

    // Tagline
    const char *tagline = "Expect the Unexpected!";
    int taglineSize = 22;

    DrawText(
        tagline,
        screenWidth / 2 - MeasureText(tagline, taglineSize) / 2,
        screenHeight * 0.30f,
        taglineSize,
        BLACK
    );

    // Main Menu heading
    DrawRectangleLinesEx(menuHeading, 2, BLACK);

    const char *heading = "MAIN MENU";
    int headingSize = (int)(screenWidth * 0.021f);

    DrawText(
        heading,
        menuHeading.x + menuHeading.width / 2 -
            MeasureText(heading, headingSize) / 2,
        menuHeading.y + menuHeading.height / 2 -
            headingSize / 2,
        headingSize,
        BLACK
    );

    // Button labels and positions
    const char *labels[] = {
        "HOW TO PLAY?",
        "PLAY",
        "EXIT"
    };

    Rectangle buttons[] = {
        howToPlayButton,
        playButton,
        exitButton
    };

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < 3; i++)
    {
        bool hovered = CheckCollisionPointRec(
            mousePosition,
            buttons[i]
        );

        // Hover effect
        if (hovered)
        {
            DrawRectangleRec(buttons[i], LIGHTGRAY);
        }

        // Button outline
        DrawRectangleLinesEx(buttons[i], 2, BLACK);

        // Button text
        int fontSize = (i == 0)
            ? (int)(screenWidth * 0.016f)
            : (int)(screenWidth * 0.022f);

        DrawText(
            labels[i],
            buttons[i].x + buttons[i].width / 2 -
                MeasureText(labels[i], fontSize) / 2,
            buttons[i].y + buttons[i].height / 2 -
                fontSize / 2,
            fontSize,
            BLACK
        );
    }
}

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
