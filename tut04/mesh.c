#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"

static void mesh_init(mesh* model) {
	glGenVertexArrays(1, &(model->VAO));
	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->IBO));

	mat4x4_identity(model->matrices.rotate);
	mat4x4_identity(model->matrices.translate);
	mat4x4_identity(model->matrices.scale);
}

static void mesh_loadToVao(mesh *model, GLfloat *vertices, GLuint *indices) {
	/*!
		* GENEARATE VAO
		* GENERATE BUFFERS
		* BIND THE VAO
		* BIND EACH BUFFER
			* SEND DATA FOR THE CURRENTLY BOUND BUFFER
		* DEFINE PARAMETERS OF EACH ATTRIBUTE
		* UNBIND VAO

		Data is sent via glBufferData, VBO is a pointer to that data.
		With glVertexAttribPointer() you set which part of that data
			relates to each attribute (position, normal, color, etc.)
	*/

	glBindVertexArray(model->VAO);
	
	// glBindBuffer(BUFFER_TYPE, REFERENCE TO BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	// glBufferData(BUFFER_TYPE, SIZE (in bytes) of DATA to be sent, pointer to data, static draw);
	glBufferData(GL_ARRAY_BUFFER, 3 * model->vertexCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// DEFINE ALL ATTRIBUTES OF THIS BUFFER
	// glVertexAttribPointer(ATTRIB_INDEX, COMPONENT COUNT, TYPE, NORMALIZED?, STRIDE (distance between each piece of data),
	//	offset);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// glBindVertexArray(0);
	// DELETE BUFFERS?
}

mesh* mesh_createFromArrays(GLfloat *vertices, GLuint *indices, unsigned int vertexCount, unsigned int indexCount) {
	mesh *model = (mesh*)malloc(sizeof(mesh));

	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_init(model);
	mesh_loadToVao(model, vertices, indices);

	return model;
}

void mesh_draw(mesh* model, shader *S, camera *C, mat4x4 projection) {
	mat4x4 MVP, view;
	mat4x4_look_at(view, C->eye, C->center, C->up);

	mat4x4_mul(MVP, model->matrices.transform, view);
	mat4x4_mul(MVP, projection, MVP);

	glUniformMatrix4fv(S->locations.MVP, 1, 0, (GLfloat*)MVP);
	glBindVertexArray(model->VAO);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}

void mesh_updateTransformationMatrix(mesh *model) {
    mat4x4_mul(model->matrices.transform, model->matrices.rotate, model->matrices.scale);
    mat4x4_mul(model->matrices.transform, model->matrices.translate, model->matrices.transform);
}

void mesh_rotate(mesh *model, bool x, bool y, bool z, float angle) {
	// It's better to use quaterninons when dealing with rotation
	mat4x4_rotate(model->matrices.rotate, model->matrices.rotate, x, y, z, angle);
}

void mesh_resetRotation(mesh *model) {
	mat4x4_identity(model->matrices.rotate);
}

void mesh_translate(mesh *model, float x, float y, float z) {
	mat4x4_translate(model->matrices.translate, x, y, z);
}

void mesh_resetTranslation(mesh *model) {
	mat4x4_identity(model->matrices.translate);
}

void mesh_scale(mesh *model, float x, float y, float z) {
	mat4x4_scale_aniso(model->matrices.scale, model->matrices.scale, x, y, z);
}

void mesh_resetScaling(mesh *model) {
	mat4x4_identity(model->matrices.scale);
}