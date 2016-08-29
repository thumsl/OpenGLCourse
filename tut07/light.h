#ifndef LIGHT_H
#define LIGHT_H

#include "linmath.h"
#include "shader.h"

typedef struct pointLight {
	vec3 color;
	vec3 position;
	float intensity;
	float attenuation;
} pointLight;

void light_setAmbientLight(shader *S, vec3 color, float intensity);

pointLight* light_createPointLight(shader *S, vec3 color, vec3 position, float intensity, float attenuation);
void light_updatePointLight(shader *S, pointLight *point);

#endif // LIGHT_H