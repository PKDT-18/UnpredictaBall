#ifndef UNPREDICTABALL_POWERUP_H
#define UNPREDICTABALL_POWERUP_H

#include "raylib.h"

typedef enum {
    SPEED_UP,
    GHOST_BALL,
    EXTENDED_RACKET,
    SLOW_DOWN,
    INVERT_CONTROLS,
    FREEZE,
    POWERUP_COUNT
} PowerupType;

typedef struct {
    float base_speed;
    float base_size;
    float speed;
    float size;
    int invert_controls;
    int frozen;
} PowerupPlayer;

typedef struct {
    float base_alpha;
    float alpha;
} PowerupBall;

typedef struct {
    float remaining[2][POWERUP_COUNT];
} PowerupSystem;

typedef struct {
    Vector2 position;
    float radius;
    PowerupType type;
    bool active;
    float spawnTimer;
} PowerupOrb;

#define POWERUP_DURATION 6.0f
#define POWERUP_RESPAWN_TIME 5.0f
#define POWERUP_ORB_RADIUS 12.0f

void Powerup_Init(PowerupSystem *system, PowerupPlayer players[2], PowerupBall *ball);

PowerupType Powerup_Collect(
    PowerupSystem *system,
    int collector,
    PowerupType type,
    PowerupPlayer players[2],
    PowerupBall *ball
);

void Powerup_Update(
    PowerupSystem *system,
    float delta_seconds,
    PowerupPlayer players[2],
    PowerupBall *ball
);

void PowerupOrb_Init(PowerupOrb *orb);
void PowerupOrb_Spawn(PowerupOrb *orb);
void PowerupOrb_Update(PowerupOrb *orb, float delta_seconds);

#endif