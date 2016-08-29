#include <stdlib.h>
#include "camera.h"
#include "engine.h"
#include "utils.h"

camera* camera_create(vec3 eye, vec3 up, vec3 direction) {
	camera *ret = (camera*)malloc(sizeof(camera));

	if (eye != NULL)
		vec3_copy(ret->eye, eye);
	else {
		ret->eye[0] = 0.0f;
		ret->eye[1] = 0.0f;
		ret->eye[2] = -2.0f;
	}

	if (up != NULL)
		vec3_copy(ret->up, up);
	else {
		ret->up[0] = 0.0f;
		ret->up[1] = 1.0f;
		ret->up[2] = 0.0f;
	}

	if (direction != NULL)
		vec3_copy(ret->direction, direction);
	else {
		ret->direction[0] = 0.f;
		ret->direction[1] = 0.f;
		ret->direction[2] = 1.0f;
	}

	vec3 normalizedDirection, normalizedUp;
	vec3_norm(normalizedDirection, ret->direction);
	vec3_norm(normalizedUp, ret->up);

	vec3_mul_cross(ret->right, normalizedDirection, normalizedUp);

	return ret;
}

void camera_lookAround(camera *C, float horizontalAngle, float verticalAngle) {
	C->direction[0] = cosf(verticalAngle) * sinf(horizontalAngle);
	C->direction[1] = sinf(verticalAngle);
	C->direction[2] = cosf(verticalAngle) * cosf(horizontalAngle);

	C->right[0] = sinf(horizontalAngle - PI/2.0f);
	C->right[1] = 0;
	C->right[2] = cosf(horizontalAngle - PI/2.0f);

	vec3_mul_cross(C->up, C->right, C->direction);
}

void camera_move(camera *C, player *P) {
	vec3 scaledDirection, scaledRight;
	vec3_scale(scaledDirection, C->direction, P->walkingSpeed);
	vec3_scale(scaledRight, C->right, P->walkingSpeed);

	if (P->movement.forward)
		vec3_add(C->eye, C->eye, scaledDirection);
	if (P->movement.backward)
		vec3_sub(C->eye, C->eye, scaledDirection);

	if (P->movement.right)
		vec3_add(C->eye, C->eye, scaledRight);
	if (P->movement.left)
		vec3_sub(C->eye, C->eye, scaledRight);
}