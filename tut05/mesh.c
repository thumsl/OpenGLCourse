#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"

static void mesh_init(mesh* model) {
	glGenVertexArrays(1, &(model->VAO));

	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->IBO));

	glGenTextures(1, &(model->textureID));

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
	glBufferData(GL_ARRAY_BUFFER, VERTEX_COMPONENT_COUNT * model->vertexCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	// DEFINE ALL ATTRIBUTES OF THIS BUFFER
	// glVertexAttribPointer(ATTRIB_INDEX, COMPONENT COUNT, TYPE, NORMALIZED?, STRIDE (distance between each piece of data),
	//	offset);

	// POSITION
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_COMPONENT_COUNT * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_COMPONENT_COUNT * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	// glBindVertexArray(0);
	// DELETE BUFFERS?
}

static void mesh_loadTexture(mesh *model, const char *texturePath) {
	SDL_Surface *texture = IMG_Load(texturePath);

	if (texture == NULL) {
		fprintf(stderr, "Failed to load texture file.\n%s\n", IMG_GetError());
		return;
	}

	glBindTexture(GL_TEXTURE_2D, model->textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);

	SDL_FreeSurface(texture);
}

mesh* mesh_createFromArrays(GLfloat *vertices, GLuint *indices, unsigned int vertexCount, unsigned int indexCount, const char *texturePath) {
	mesh *model = (mesh*)malloc(sizeof(mesh));

	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_init(model);
	mesh_loadToVao(model, vertices, indices);
	if (texturePath != NULL)
		mesh_loadTexture(model, texturePath);

	return model;
}

void mesh_draw(mesh* model, shader *S, camera *C, mat4x4 projection) {
	mat4x4 MVP, view;
	mat4x4_look_at(view, C->eye, C->center, C->up);

	mat4x4_mul(MVP, model->matrices.transform, view);
	mat4x4_mul(MVP, projection, MVP);

	glUniformMatrix4fv(S->locations.MVP, 1, 0, (GLfloat*)MVP);
	glBindVertexArray(model->VAO);
	glBindTexture(GL_TEXTURE_2D, model->textureID);
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