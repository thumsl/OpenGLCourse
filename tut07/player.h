#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct playerMovement {
	bool forward;
	bool backward;
	bool left;
	bool right;
} playerMovement;

typedef struct player {
	// vec3 position;
	// float hp;
	// float runningSpeed;;
	playerMovement movement;
	float walkingSpeed;
} player;

player* player_create(float walkingSpeed);

#endif // PLAYER_H