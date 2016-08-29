#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

typedef struct shaderLocations {
	GLuint MVP;

	GLuint ambientLightColor;
	GLuint ambientLightIntensity;

	GLuint pointLightColor;
	GLuint pointLightPosition;
	GLuint pointLightIntensity;
	GLuint pointLightAttenuation;

	GLuint transformationMatrix;
	GLuint normalTransformationMatrix;
} shaderLocations;

typedef struct shader {
	GLuint program;
	shaderLocations locations;
} shader;

shader* shader_createFromFile(const char *vertexShaderPath, const char *fragmentShaderPath);
static void shader_init(shader *S);

void shader_use(shader *S);

#endif // SHADER_H
