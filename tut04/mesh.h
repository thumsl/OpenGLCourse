#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <stdbool.h>
#include "camera.h"
#include "linmath.h"
#include "shader.h"

typedef struct transformationMatrices {
	mat4x4 rotate;
	mat4x4 translate;
	mat4x4 scale;
	mat4x4 transform;
} meshTransformationMatrices;

typedef struct mesh {
	// GLuint --> OpenGL's unsigned int
	GLuint VAO;	// VERTEX ARRAY OBJECT	<M-F2>
	GLuint VBO;	// VERTEX BUFFER OBJECT
	GLuint IBO;	// INDEX BUFFER OBJECT
	unsigned int vertexCount;
	unsigned int indexCount;
	meshTransformationMatrices matrices;
} mesh;

static void mesh_init(mesh*);
static void mesh_loadToVao(mesh* model, GLfloat *vertices, GLuint *indices);

mesh* mesh_createFromArrays(GLfloat *vertices, GLuint *indices, unsigned int vertexCount, unsigned int indexCount);
mesh* mesh_createFromFile();

void mesh_rotate(mesh *model, bool x, bool y, bool z, float angle);
void mesh_resetRotation(mesh *model);
void mesh_translate(mesh *model, float x, float y, float z);
void mesh_resetTranslation(mesh *model);
void mesh_scale(mesh *model, float x, float y, float z);
void mesh_resetScaling(mesh *model);

void mesh_updateTransformationMatrix(mesh *model);
void mesh_draw(mesh* model, shader *S, camera *C, mat4x4 projection); // rather send only the model to a draw function

#endif // MESH_H
