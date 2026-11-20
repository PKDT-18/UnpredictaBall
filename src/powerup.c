#include <stdlib.h>

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

#define POWERUP_DURATION 6.0f

static void apply_effects(const PowerupSystem *system,
						  PowerupPlayer players[2], PowerupBall *ball)
{
	int i;
	int ghost_active = 0;

	for (i = 0; i < 2; ++i) {
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
		players[i].frozen = system->remaining[i][FREEZE] > 0.0f;
		if (system->remaining[i][GHOST_BALL] > 0.0f)
			ghost_active = 1;
	}

	if (ball != NULL)
		ball->alpha = ghost_active ? ball->base_alpha * 0.35f : ball->base_alpha;
}

void Powerup_Init(PowerupSystem *system, PowerupPlayer players[2],
				  PowerupBall *ball)
{
	int player;
	int type;

	if (system == NULL || players == NULL)
		return;
	for (player = 0; player < 2; ++player)
		for (type = 0; type < POWERUP_COUNT; ++type)
			system->remaining[player][type] = 0.0f;
	apply_effects(system, players, ball);
}

PowerupType Powerup_Collect(PowerupSystem *system, int collector,
							PowerupPlayer players[2], PowerupBall *ball)
{
	PowerupType type;
	int target;

	if (system == NULL || players == NULL || collector < 0 || collector > 1)
		return POWERUP_COUNT;

	type = (PowerupType)(rand() % POWERUP_COUNT);
	target = (type == SLOW_DOWN || type == INVERT_CONTROLS ||
			  type == FREEZE) ? 1 - collector : collector;
	system->remaining[target][type] = POWERUP_DURATION;
	apply_effects(system, players, ball);
	return type;
}

void Powerup_Update(PowerupSystem *system, float delta_seconds,
					PowerupPlayer players[2], PowerupBall *ball)
{
	int player;
	int type;

	if (system == NULL || players == NULL || delta_seconds <= 0.0f)
		return;
	for (player = 0; player < 2; ++player) {
		for (type = 0; type < POWERUP_COUNT; ++type) {
			float *time_left = &system->remaining[player][type];
			if (*time_left > 0.0f) {
				*time_left -= delta_seconds;
				if (*time_left < 0.0f)
					*time_left = 0.0f;
			}
		}
	}
	apply_effects(system, players, ball);
}