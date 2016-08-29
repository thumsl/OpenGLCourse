#ifndef CAMERA_H
#define CAMERA_H

#include "linmath.h"
#include "player.h"

typedef struct camera {
	vec3 eye;
	vec3 up;
	vec3 direction;
	vec3 right;
} camera;

camera* camera_create(vec3 eye, vec3 up, vec3 direction);
void camera_lookAround(camera *C, float horizontalAngle, float verticalAngle);
void camera_move(camera *C, player *P);

#endif // CAMERA_H