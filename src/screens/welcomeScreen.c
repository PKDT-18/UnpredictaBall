#include "../game.h"

void UpdateWelcomeScreen(void)
{
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        screen = SCREEN_MENU;
    }
}

void DrawWelcomeScreen(void)
{
    const char *title = "UNPREDICTABALL";
    const char *tagline = "A GAME OF UNPREDICTABLE TWISTS";
    const char *prompt = "PRESS ENTER TO CONTINUE";

    ClearBackground(RAYWHITE);

    int titleSize = 65;

    DrawText(
        title,
        GetScreenWidth()/2 - MeasureText(title, titleSize)/2,
        GetScreenHeight()/2 - 90,
        titleSize,
        BLACK
    );

    int taglineSize = 20;

    DrawText(
        tagline,
        GetScreenWidth()/2 - MeasureText(tagline, taglineSize)/2,
        GetScreenHeight()/2 + 5,
        taglineSize,
        BLACK
    );

    int promptSize = 18;

    DrawText(
        prompt,
        GetScreenWidth()/2 - MeasureText(prompt, promptSize)/2,
        GetScreenHeight() - 70,
        promptSize,
        DARKGRAY
    );
}