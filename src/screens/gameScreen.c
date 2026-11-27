#include "../game.h"

static float bounceAngle, ballRelativeY;

void UpdateGameScreen()
{
    ++framesCounter;


    if (
            IsKeyPressed(KEY_ESCAPE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT) ||
            (mode == MODE_2PLAYERS && IsGamepadButtonPressed(1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
            ) {
        screen = SCREEN_PAUSE;
        return;
    }

    if (IsKeyPressed(KEY_F3)) showDebug = !showDebug;

    PowerupOrb_Update(&powerupOrb, GetFrameTime());
    
    // Player movement
    float centerX = GetScreenWidth() / 2.0f;

    // PLAYER 1: WASD controls
    if (IsKeyDown(KEY_W) ||
        IsKeyDown(KEY_Z) ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.2f)
    {
        p1.position.y -= PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_S) ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.2f)
    {
        p1.position.y += PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_A) ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.2f)
    {
        p1.position.x -= PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_D) ||
        IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
        GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.2f)
    {
        p1.position.x += PLAYER_SPEED;
    }

    // PLAYER 2: Arrow key controls
    if (IsKeyDown(KEY_UP) ||
        IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
        GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y) < -0.2f)
    {
        p2.position.y -= PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_DOWN) ||
        IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
        GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y) > 0.2f)
    {
        p2.position.y += PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_LEFT) ||
        IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
        GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X) < -0.2f)
    {
        p2.position.x -= PLAYER_SPEED;
    }

    if (IsKeyDown(KEY_RIGHT) ||
        IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
        GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X) > 0.2f)
    {
        p2.position.x += PLAYER_SPEED;
    }

    // PLAYER 1 boundaries: left half
    if (p1.position.x < 0)
        p1.position.x = 0;

    if (p1.position.x + playerSize.x > centerX)
        p1.position.x = centerX - playerSize.x;

    // PLAYER 2 boundaries: right half
    if (p2.position.x < centerX)
        p2.position.x = centerX;

    if (p2.position.x + playerSize.x > GetScreenWidth())
        p2.position.x = GetScreenWidth() - playerSize.x;

    // Vertical boundaries for both players
    if (p1.position.y < 0)
        p1.position.y = 0;

    if (p1.position.y + playerSize.y > GetScreenHeight())
        p1.position.y = GetScreenHeight() - playerSize.y;

    if (p2.position.y < 0)
        p2.position.y = 0;

    if (p2.position.y + playerSize.y > GetScreenHeight())
        p2.position.y = GetScreenHeight() - playerSize.y;

#ifdef PLATFORM_WEB
    if (IsGestureDetected(GESTURE_HOLD) ||
        IsGestureDetected(GESTURE_DRAG))
    {
        p1.position.y = GetTouchPosition(0).y - playerSize.y / 2;
    }
#endif


    // Ball mouvement
    ballPosition.x += ballDirection.x;
    ballPosition.y += ballDirection.y;

    // Ball collisions with player
    p1.colliding = CheckCollisionCircleRec(
            ballPosition, BALLRADIUS,
            (Rectangle) {p1.position.x, p1.position.y, playerSize.x, playerSize.y}
    );
    p2.colliding = CheckCollisionCircleRec(
            ballPosition, BALLRADIUS,
            (Rectangle) {p2.position.x, p2.position.y, playerSize.x, playerSize.y}
    );

    if (p1.colliding) {
        PlaySound(playerBeep);

        ballRelativeY = ballPosition.y - (p1.position.y + playerSize.y/2);
        bounceAngle = ballRelativeY*MAX_BOUNCE_ANGLE/(playerSize.y/2);

        ballDirection.x = cosf(bounceAngle)*ballSpeed;
        ballDirection.y = sinf(bounceAngle)*ballSpeed;

        ballPosition.x = p1.position.x + playerSize.x + BALLRADIUS;
    } else if (p2.colliding) {
        PlaySound(playerBeep);

        ballRelativeY = ballPosition.y - (p2.position.y + playerSize.y/2);
        bounceAngle = ballRelativeY*MAX_BOUNCE_ANGLE/(playerSize.y/2);

        ballDirection.x = -cosf(bounceAngle)*ballSpeed;
        ballDirection.y = sinf(bounceAngle)*ballSpeed;

        ballPosition.x = p2.position.x - BALLRADIUS;
    }


    // Check walls collision for score
        if (ballPosition.x >= (GetScreenWidth() - BALLRADIUS)) {
        ++p1.score;
        ballPosition = (Vector2) {
            GetScreenWidth()/2.0f,
            GetScreenHeight()/2.0f
        };

        ballSpeed = DEFAULT_BALL_SPEED;
        InitBallDirection(&ballDirection, 3*PI/4 + GetRandomValue(0, 1)*PI/2);

        CenterPlayerY(&p1);
        CenterPlayerY(&p2);

        if (p1.score >= 3) {
            screen = SCREEN_GAME_OVER;
        } else {
            screen = SCREEN_POINT;
            pauseFrames = POINT_WAIT_FRAME;
        }

        } else if (ballPosition.x <= BALLRADIUS) {
        ++p2.score;
        ballPosition = (Vector2) {
            GetScreenWidth()/2.0f,
            GetScreenHeight()/2.0f
        };

        ballSpeed = DEFAULT_BALL_SPEED;
        InitBallDirection(&ballDirection, -PI/4 + GetRandomValue(0, 1)*PI/2);

        CenterPlayerY(&p1);
        CenterPlayerY(&p2);

        if (p2.score >= 3) {
            screen = SCREEN_GAME_OVER;
        } else {
            screen = SCREEN_POINT;
            pauseFrames = POINT_WAIT_FRAME;
        }
    }

    // Check walls collision for bouncing
    if ((ballPosition.y >= (GetScreenHeight() - BALLRADIUS)) || (ballPosition.y <= BALLRADIUS)) {
        PlaySound(wallBeep);
        ballDirection.y *= -1.0f;
    }

    // Increase speed periodically
    if (framesCounter%SPEED_INCREASE_INTERVAL == 0) {
        ballSpeed += 1.0f;
    }
}


void DrawGameScreen()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Black background
    ClearBackground(BLACK);

    // Player labels
    const char *player1Label = "PLAYER 1";
    const char *player2Label = "PLAYER 2";

    DrawText(player1Label, 18, 14, 16, WHITE);

    DrawText(
        player2Label,
        screenWidth - MeasureText(player2Label, 16) - 18,
        14,
        16,
        WHITE
    );

    // Scoreboard
    const char *score1 = TextFormat("%d", p1.score);
    const char *score2 = TextFormat("%d", p2.score);

    int scoreSize = 30;
    int vsSize = 30;

    DrawText(
        score1,
        screenWidth / 2 - 110 - MeasureText(score1, scoreSize) / 2,
        10,
        scoreSize,
        WHITE
    );

    DrawText(
        "VS",
        screenWidth / 2 - MeasureText("VS", vsSize) / 2,
        10,
        vsSize,
        WHITE
    );

    DrawText(
        score2,
        screenWidth / 2 + 110 - MeasureText(score2, scoreSize) / 2,
        10,
        scoreSize,
        WHITE
    );

    // Dotted center divider
    int centerX = screenWidth / 2;

    for (int y = 67; y < screenHeight - 80; y += 7)
    {
        DrawCircle(centerX, y, 1.5f, WHITE);
    }

    // Drawing ball (unchanged)
    DrawCircleV(ballPosition, BALLRADIUS, WHITE);

    // Draw power-up orb
    if (powerupOrb.active)
    {
        Color orbColor = (powerupOrb.type <= EXTENDED_RACKET) ? GREEN : RED;

        DrawCircleV(
            powerupOrb.position,
            powerupOrb.radius,
            orbColor
        );
    }


    // Drawing players / paddles (UNCHANGED)
    DrawRectangleV(p1.position, playerSize, WHITE);
    DrawRectangleV(p2.position, playerSize, WHITE);

    // Pause label
    const char *pauseLabel = "PAUSE ||";
    int pauseSize = 12;

    DrawText(
        pauseLabel,
        screenWidth / 2 - MeasureText(pauseLabel, pauseSize) / 2,
        screenHeight - 64,
        pauseSize,
        WHITE
    );

    // Drawing debug
    if (showDebug)
    {
        DrawFPS(10, 30);
        DrawText(
            TextFormat("%.3f ms", GetFrameTime() * 1000.0f),
            10, 50, 20, RAYWHITE
        );
    }
}