#include "../game.h"

void UpdatePauseScreen()
{
    if (
        IsKeyPressed(KEY_ESCAPE) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT) ||
        (mode == MODE_2PLAYERS &&
         IsGamepadButtonPressed(1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
    )
    {
        screen = SCREEN_GAME;
    }

    const char *options[] = {
        "Resume",
        "Restart",
        "Main Menu",
        "Exit"
    };

    int fontSize = 30;
    int spacing = 55;
    int startY = GetScreenHeight() / 2 - 50;

    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        int textWidth = MeasureText(options[i], fontSize);
        int x = (GetScreenWidth() - textWidth) / 2;
        int y = startY + (i * spacing);

        Rectangle button = {
            x - 15,
            y - 5,
            textWidth + 30,
            fontSize + 10
        };

        if (CheckCollisionPointRec(mouse, button) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (i == 0)
            {
                screen = SCREEN_GAME;
            }
            else if (i == 1)
            {
                screen = SCREEN_RESTART;
            }
            else if (i == 2)
            {
                screen = SCREEN_MENU;
            }
            else if (i == 3)
            {
                CloseWindow();
            }
        }
    }
}

void DrawPauseScreen()
{
    const char *options[] = {
        "Resume",
        "Restart",
        "Main Menu",
        "Exit"
    };

    int fontSize = 30;
    int spacing = 55;
    int startY = GetScreenHeight() / 2 - 50;

    DrawText(
        "Pause",
        (GetScreenWidth() - MeasureText("Pause", 50)) / 2,
        startY - 100,
        50,
        WHITE
    );

    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        int textWidth = MeasureText(options[i], fontSize);
        int x = (GetScreenWidth() - textWidth) / 2;
        int y = startY + (i * spacing);

        Rectangle button = {
            x - 15,
            y - 5,
            textWidth + 30,
            fontSize + 10
        };

        Color color = CheckCollisionPointRec(mouse, button)
                      ? YELLOW
                      : WHITE;

        DrawText(options[i], x, y, fontSize, color);
    }
}