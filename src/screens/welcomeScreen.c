
#include "../game.h"

void UpdateWelcomeScreen(void)
{
    // Press any key to continue
    if (GetKeyPressed() != 0)
    {
        screen = SCREEN_MENU;
    }
}

void DrawWelcomeScreen(void)
{
    const char *title = "UNPREDICTABALL";
    const char *tagline = "Expect the Unexpected!";
    const char *message = "Ready for an unpredictable match?";
    const char *prompt = "PRESS ANY KEY TO CONTINUE";

    ClearBackground(RAYWHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Main title
    int titleSize = 55;

    DrawText(
        title,
        screenWidth / 2 - MeasureText(title, titleSize) / 2,
        screenHeight * 0.30f,
        titleSize,
        BLACK
    );

    // Tagline
    int taglineSize = 23;

    DrawText(
        tagline,
        screenWidth / 2 - MeasureText(tagline, taglineSize) / 2,
        screenHeight * 0.45f,
        taglineSize,
        BLACK
    );

    // Introductory message
    int messageSize = 20;

    DrawText(
        message,
        screenWidth / 2 - MeasureText(message, messageSize) / 2,
        screenHeight * 0.60f,
        messageSize,
        DARKGRAY
    );

    // Continue prompt
    int promptSize = 18;

    DrawText(
        prompt,
        screenWidth / 2 - MeasureText(prompt, promptSize) / 2,
        screenHeight * 0.70f,
        promptSize,
        BLACK
    );
}
