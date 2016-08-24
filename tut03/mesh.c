#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"

static void mesh_init(mesh* model) {
	glGenVertexArrays(1, &(model->VAO));
	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->IBO));

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
	mesh *model = (mesh*)malloc(sizeof(model));

	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_init(model);
	mesh_loadToVao(model, vertices, indices);

	return model;
}

void mesh_draw(mesh* model) {
	glBindVertexArray(model->VAO);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}
