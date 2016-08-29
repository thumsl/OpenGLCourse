#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#include "utils.h"

shader* shader_createFromFile(const char *vertexShaderPath, const char *fragmentShaderPath) {
	char *vertexSource, *fragmentSource;

	if (!readFile(&vertexSource, vertexShaderPath)) {
		fprintf(stderr, "Failed to open shader file \"%s\".\n", vertexShaderPath);
		return NULL;
	}


	if (!readFile(&fragmentSource, fragmentShaderPath)) {
		fprintf(stderr, "Failed to open shader file \"%s\".\n", fragmentShaderPath);
		return NULL;
	}
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char* const*)&vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char* const*)&fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint status1, status2;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status1);
	if (status1 != GL_TRUE) {
		char buffer[512];
		fprintf(stderr, "Compilation error for file \"%s\"\n", vertexShaderPath);
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		fprintf(stderr, "%s\n", buffer);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status2);
	if (status2 != GL_TRUE) {
		char buffer[512];
		fprintf(stderr, "Compilation error for file \"%s\"\n", fragmentShaderPath);
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		fprintf(stderr, "%s\n", buffer);
	}

	if (status1 != GL_TRUE || status2 != GL_TRUE)
		return NULL;

	shader *ret = (shader*)malloc(sizeof(shader));
	ret->program = glCreateProgram();

	glAttachShader(ret->program, vertexShader);
	glAttachShader(ret->program, fragmentShader);
	glLinkProgram(ret->program);

	shader_init(ret);
	
	return ret;
}

static void shader_init(shader *S) {
	S->locations.MVP = glGetUniformLocation(S->program, "MVP");

	S->locations.ambientLightColor = glGetUniformLocation(S->program, "ambientLightColor");
	S->locations.ambientLightIntensity = glGetUniformLocation(S->program, "ambientLightIntensity");

	S->locations.pointLightColor = glGetUniformLocation(S->program, "pointLightColor");
	S->locations.pointLightPosition = glGetUniformLocation(S->program, "pointLightPosition");
	S->locations.pointLightIntensity = glGetUniformLocation(S->program, "pointLightIntensity");
	S->locations.pointLightAttenuation = glGetUniformLocation(S->program, "pointLightAttenuation");

	S->locations.transformationMatrix = glGetUniformLocation(S->program, "transformationMatrix");
	S->locations.normalTransformationMatrix = glGetUniformLocation(S->program, "normalTransformationMatrix");
}

void shader_use(shader *S) {
	glUseProgram(S->program);
}
