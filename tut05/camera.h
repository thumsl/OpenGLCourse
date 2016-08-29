#ifndef CAMERA_H
#define CAMERA_H

#include "linmath.h"

typedef struct camera {
	vec3 eye;
	vec3 up;
	vec3 center;
} camera;

camera* camera_create(vec3 eye, vec3 up, vec3 center);

#endif // CAMERA_H