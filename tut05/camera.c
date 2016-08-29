#include <stdlib.h>
#include "camera.h"
#include "utils.h"

camera* camera_create(vec3 eye, vec3 up, vec3 center) {
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

	if (center != NULL)
		vec3_copy(ret->center, center);
	else {
		ret->center[0] = 0.f;
		ret->center[1] = 0.f;
		ret->center[2] = 0.f;
	}

	return ret;
 }