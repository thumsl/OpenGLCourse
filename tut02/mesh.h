#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

typedef struct mesh {
	// GLuint --> OpenGL's unsigned int
	GLuint VAO;	// VERTEX ARRAY OBJECT	<M-F2>
	GLuint VBO;	// VERTEX BUFFER OBJECT
	GLuint IBO;	// INDEX BUFFER OBJECT
	unsigned int vertexCount;
	unsigned int indexCount;
} mesh;

static void mesh_init(mesh*);
static void mesh_loadToVao(mesh* model, GLfloat *vertices, GLuint *indices);

mesh* mesh_createFromArrays(GLfloat *vertices, GLuint *indices, unsigned int vertexCount, unsigned int indexCount);
mesh* mesh_createFromFile();

void mesh_draw(mesh* model);

#endif // MESH_H
