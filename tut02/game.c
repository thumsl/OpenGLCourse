#include "engine.h"
#include <stdbool.h>

int main() {
	bool running = true;

	SDL_Window* window = window_create("3D Game Engine", 800, 600);
	
	if (window == NULL)
		return 1;

	if (!initOpenGL())
		return 1;

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
	while (running) {
		/* INPUT HANDLING */
		while (SDL_PollEvent(&e))
			if (e.type == SDL_WINDOWEVENT)
				if (e.window.event == SDL_WINDOWEVENT_CLOSE) 
					running = false;

		/* GAME LOGIC */
		
		
		/* RENDERING */
		glClear(GL_COLOR_BUFFER_BIT);
		mesh_draw(triangulo);
		SDL_GL_SwapWindow(window);
	}

	return 0;
}
