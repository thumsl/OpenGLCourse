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

	SDL_Event e;

	GLuint loc = glGetUniformLocation(S->program, "offset");

	float factor = 0.0f;

	while (running) {
		/* INPUT HANDLING */
		while (SDL_PollEvent(&e))
			if (e.type == SDL_WINDOWEVENT)
				if (e.window.event == SDL_WINDOWEVENT_CLOSE) 
					running = false;

		/* GAME LOGIC */
		factor += 0.01f;

		glUniform1f(loc, sinf(factor));
		
		/* RENDERING */
		glClear(GL_COLOR_BUFFER_BIT);
		mesh_draw(triangulo);
		SDL_GL_SwapWindow(window);
		SDL_Delay(1);
	}

	return 0;
}
