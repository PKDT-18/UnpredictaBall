#ifndef CRAYPONG_TYPES_H
#define CRAYPONG_TYPES_H

#include "stdbool.h"
#include "raylib.h"

typedef struct Player {
    Vector2 position;
    unsigned short score;
    bool colliding;
} Player;

typedef enum SCREEN {
    SCREEN_WELCOME,
    SCREEN_MENU,
    SCREEN_HOW_TO_PLAY,
    SCREEN_GAME,
    SCREEN_PAUSE,
    SCREEN_POINT,
    SCREEN_GAME_OVER
} SCREEN;

typedef enum MODE {
    MODE_2PLAYERS
} MODE;

#endif
