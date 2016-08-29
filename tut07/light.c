#include <stdlib.h>
#include <stdio.h>
#include "light.h"
#include "utils.h"

void light_setAmbientLight(shader *S, vec3 color, float intensity) {
	glUniform3fv(S->locations.ambientLightColor, 1, (GLfloat*)color);
	glUniform1f(S->locations.ambientLightIntensity, intensity);
}

pointLight* light_createPointLight(shader *S, vec3 color, vec3 position, float intensity, float attenuation) {
	pointLight *point = (pointLight*)malloc(sizeof(pointLight));

	vec3_copy(point->color, color);
	vec3_copy(point->position, position);

	point->intensity = intensity;
	point->attenuation = attenuation;

	light_updatePointLight(S, point);

	return point;
}

void light_updatePointLight(shader *S, pointLight *point) {
	glUniform3fv(S->locations.pointLightColor, 1, (GLfloat*)point->color);
	glUniform3fv(S->locations.pointLightPosition, 1, (GLfloat*)point->position);
	glUniform1f(S->locations.pointLightIntensity, point->intensity);
	glUniform1f(S->locations.pointLightAttenuation, point->attenuation);
}