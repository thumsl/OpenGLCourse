#include "player.h"
#include <stdlib.h>

player* player_create(float walkingSpeed) {
	player *ret = (player*)malloc(sizeof(player));

	ret->walkingSpeed = walkingSpeed;
	ret->movement.forward = ret->movement.backward = ret->movement.left = ret->movement.right = false;
}