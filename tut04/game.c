#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "engine.h"

int main() {
	bool running = true;

	SDL_Window* window = window_create("3D Game Engine", 800, 600);
	
	if (window == NULL)
		return 1;

	if (!initOpenGL())
		return 1;

	shader *S = shader_createFromFile("GLSL/shader.vert", "GLSL/shader.frag");

	if (S == NULL)
		return 1;

	shader_use(S);

	GLfloat vertices[] = {
		-1.0, -1.0, 0.0,
		 0.0,  1.0, 0.0,
		 1.0, -1.0, 0.0
	};

	GLuint indices[] = {
		2, 1, 0
	};

	mesh* triangulo = mesh_createFromArrays(vertices, indices, 3, 3);
	mesh_scale(triangulo, 0.5f, 0.5f, 0.5f);
	mesh_rotate(triangulo, false, true, false, 0);
	mesh_updateTransformationMatrix(triangulo);

	mat4x4 projection;
	mat4x4_perspective(projection, PI/2, (float)WIDTH/(float)HEIGHT, 0.0f, 100.0f);

	camera *C = camera_create(NULL, NULL, NULL);
	SDL_Event e;

	float factor = 0.0f;

	while (running) {
		/* INPUT HANDLING */
		while (SDL_PollEvent(&e))
			if (e.type == SDL_WINDOWEVENT)
				if (e.window.event == SDL_WINDOWEVENT_CLOSE) 
					running = false;

		/* GAME LOGIC */
		factor += 0.1f;
		C->center[0] = PI*sinf(factor);

		/* RENDERING */
		glClear(GL_COLOR_BUFFER_BIT);
		mesh_draw(triangulo, S, C, projection);
		SDL_GL_SwapWindow(window);
		SDL_Delay(1);
	}

	return 0;
}
