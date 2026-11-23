#include "../game.h"

void UpdatePauseScreen()
{
    if (
            IsKeyPressed(KEY_ESCAPE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT) ||
            (mode == MODE_2PLAYERS && IsGamepadButtonPressed(1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
            ) {
        screen = SCREEN_GAME;
    }
}

void DrawPauseScreen()
{
    DrawText("Pause", TextCenterX("Pause", 10), TextCenterY(10), 50, WHITE);
    DrawText("Resume", TextCenterX("Resume", 20), TextCenterY(10), 50, WHITE);
    DrawText("Restart", TextCenterX("Restart", 30), TextCenterY(10), 50, WHITE);
    DrawText("Main Menu", TextCenterX("Main Menu", 40), TextCenterY(10), 50, WHITE);
    DrawText("Exit", TextCenterX("Exit", 50), TextCenterY(10), 50, WHITE);
}