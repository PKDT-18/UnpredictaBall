#include "powerup.h"
#include <stdlib.h>

static void apply_effects(
    const PowerupSystem *system,
    PowerupPlayer players[2],
    PowerupBall *ball
)
{
    int i;
    int ghost_active = 0;

    for (i = 0; i < 2; ++i)
    {
        players[i].speed = players[i].base_speed;

        if (system->remaining[i][SPEED_UP] > 0.0f)
            players[i].speed *= 1.5f;

        if (system->remaining[i][SLOW_DOWN] > 0.0f)
            players[i].speed *= 0.5f;

        players[i].size = players[i].base_size;

        if (system->remaining[i][EXTENDED_RACKET] > 0.0f)
            players[i].size *= 1.5f;

        players[i].invert_controls =
            system->remaining[i][INVERT_CONTROLS] > 0.0f;

        players[i].frozen =
            system->remaining[i][FREEZE] > 0.0f;

        if (system->remaining[i][GHOST_BALL] > 0.0f)
            ghost_active = 1;
    }

    if (ball != NULL)
        ball->alpha = ghost_active ? ball->base_alpha * 0.35f : ball->base_alpha;
}

void Powerup_Init(
    PowerupSystem *system,
    PowerupPlayer players[2],
    PowerupBall *ball
)
{
    int player;
    int type;

    if (system == NULL || players == NULL)
        return;

    for (player = 0; player < 2; ++player)
    {
        for (type = 0; type < POWERUP_COUNT; ++type)
        {
            system->remaining[player][type] = 0.0f;
        }
    }

    apply_effects(system, players, ball);
}

PowerupType Powerup_Collect(
    PowerupSystem *system,
    int collector,
    PowerupType type,
    PowerupPlayer players[2],
    PowerupBall *ball
)
{
    int target;

    if (system == NULL || players == NULL ||
        collector < 0 || collector > 1 ||
        type < 0 || type >= POWERUP_COUNT)
    {
        return POWERUP_COUNT;
    }

    target = (
        type == SLOW_DOWN ||
        type == INVERT_CONTROLS ||
        type == FREEZE
    ) ? 1 - collector : collector;

    system->remaining[target][type] = POWERUP_DURATION;

    apply_effects(system, players, ball);

    return type;
}

void Powerup_Update(
    PowerupSystem *system,
    float delta_seconds,
    PowerupPlayer players[2],
    PowerupBall *ball
)
{
    int player;
    int type;

    if (system == NULL || players == NULL || delta_seconds <= 0.0f)
        return;

    for (player = 0; player < 2; ++player)
    {
        for (type = 0; type < POWERUP_COUNT; ++type)
        {
            float *time_left = &system->remaining[player][type];

            if (*time_left > 0.0f)
            {
                *time_left -= delta_seconds;

                if (*time_left < 0.0f)
                    *time_left = 0.0f;
            }
        }
    }

    apply_effects(system, players, ball);

}
void PowerupOrb_Init(PowerupOrb *orb)
{
    if (orb == NULL)
        return;

    orb->position = (Vector2){0, 0};
    orb->radius = POWERUP_ORB_RADIUS;
    orb->type = POWERUP_COUNT;
    orb->active = false;
    orb->spawnTimer = 0.0f;
}

void PowerupOrb_Spawn(PowerupOrb *orb)
{
    if (orb == NULL)
        return;

    // Choose a random power-up
    orb->type = (PowerupType)GetRandomValue(0, POWERUP_COUNT - 1);

    // Keep the orb away from the court edges
    orb->position.x = GetRandomValue(
        GetScreenWidth() / 4,
        3 * GetScreenWidth() / 4
    );

    orb->position.y = GetRandomValue(
        50,
        GetScreenHeight() - 50
    );

    orb->active = true;
    orb->spawnTimer = 0.0f;
}

void PowerupOrb_Update(PowerupOrb *orb, float delta_seconds)
{
    if (orb == NULL || orb->active)
        return;

    if (orb->spawnTimer > 0.0f)
    {
        orb->spawnTimer -= delta_seconds;

        if (orb->spawnTimer <= 0.0f)
        {
            orb->spawnTimer = 0.0f;
            PowerupOrb_Spawn(orb);
        }
    }
}