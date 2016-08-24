#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>

typedef struct shader {
	GLuint program;
} shader;

shader* shader_createFromFile(const char *vertexShaderPath, const char *fragmentShaderPath);
void shader_use(shader *S);

#endif // SHADER_H
