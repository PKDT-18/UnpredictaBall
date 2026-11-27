#include "raylib.h"

// Call with the game's reset function to restart, e.g. RestartScreenUpdate(ResetGame)
void UpdateRestartScreen(void (*restartGame)(void))
{
	const Rectangle restartButton = {
		GetScreenWidth() / 2.0f - 120.0f,
		GetScreenHeight() / 2.0f - 30.0f,
		240.0f,
		60.0f
	};

	const bool keyboardPressed = IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE);
	const bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
							  CheckCollisionPointRec(GetMousePosition(), restartButton);

	if (restartGame != 0 && (keyboardPressed || mousePressed))
	{
		restartGame();
	}
}

void DrawRestartScreen(void)
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();
	const Rectangle restartButton = {
		screenWidth / 2.0f - 120.0f,
		screenHeight / 2.0f - 30.0f,
		240.0f,
		60.0f
	};
	const bool hovered = CheckCollisionPointRec(GetMousePosition(), restartButton);

	DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 48) / 2,
			 screenHeight / 2 - 120, 48, RAYWHITE);
	DrawRectangleRec(restartButton, hovered ? DARKGREEN : GREEN);
	DrawText("Restart", screenWidth / 2 - MeasureText("Restart", 28) / 2,
			 screenHeight / 2 - 14, 28, RAYWHITE);
	DrawText("Press ENTER or SPACE", screenWidth / 2 - MeasureText("Press ENTER or SPACE", 20) / 2,
			 screenHeight / 2 + 55, 20, LIGHTGRAY);
}
