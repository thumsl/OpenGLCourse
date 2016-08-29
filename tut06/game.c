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

	glClearColor(0.50f, 0.2f, 0.8f, 1.0f);

	shader *S = shader_createFromFile("GLSL/shader.vert", "GLSL/shader.frag");

	if (S == NULL)
		return 1;

	shader_use(S);

	player *mainCharacter = player_create(0.1f);

	GLfloat vertices[] = {
		-1.0, -1.0, 0.0, 1.0, 1.0,
		 0.0,  1.0, 0.0, 0.5, 0.0,
		 1.0, -1.0, 0.0, 0.0, 1.0
	};

	GLuint indices[] = {
		2, 1, 0
	};

	mesh* triangulo = mesh_createFromArrays(vertices, indices, 3, 3, "test2.png");
	mesh_scale(triangulo, 0.5f, 0.5f, 0.5f);
	mesh_rotate(triangulo, false, true, false, 0);
	mesh_updateTransformationMatrix(triangulo);

	mat4x4 projection;
	mat4x4_perspective(projection, PI/2, (float)WIDTH/(float)HEIGHT, 0.0f, 100.0f);

	camera *C = camera_create(NULL, NULL, NULL);
	SDL_Event e;

	float factor = 0.0f, horizontalAngle = 0.0f, verticalAngle = 0.0f;
	int mouseX, mouseY;

	SDL_WarpMouseInWindow(window, WIDTH/2, HEIGHT/2);
	SDL_GetMouseState(&mouseX, &mouseY);

	while (running) {
		/* INPUT HANDLING */
		while (SDL_PollEvent(&e)) {

			if (e.type == SDL_WINDOWEVENT)
				if (e.window.event == SDL_WINDOWEVENT_CLOSE) 
					running = false;

			if (e.type == SDL_KEYDOWN)
				switch(e.key.keysym.sym) {
					case SDLK_q:
						running = false;
						break;
					case SDLK_w:
						mainCharacter->movement.forward = true;
						break;
					case SDLK_s:
						mainCharacter->movement.backward = true;
						break;
					case SDLK_a:
						mainCharacter->movement.left = true;
						break;
					case SDLK_d:
						mainCharacter->movement.right = true;
						break;
				}

			if (e.type == SDL_KEYUP)
				switch(e.key.keysym.sym) {
					case SDLK_w:
						mainCharacter->movement.forward = false;
						break;
					case SDLK_s:
						mainCharacter->movement.backward = false;
						break;
					case SDLK_a:
						mainCharacter->movement.left = false;
						break;
					case SDLK_d:
						mainCharacter->movement.right = false;
						break;
				}
		}

		/*
			** FOR THIS TUTORIAL WINDOW.C WAS UPDATE **
			Mouse look:
				Lock the mouse at the center of the screen;
				Grab how much the cursor moved with SDL_GetMouseState(&x, &y);
				Compute the angle relative to that
				Send it to camera_mouseLook();
				Reset the angle, reposition the cursor at the center of the screen
		*/

		/* GAME LOGIC */
		SDL_GetMouseState(&mouseX, &mouseY);

		float deltaX = WIDTH/2 - mouseX;
		float deltaY = HEIGHT/2 - mouseY;

		if (deltaX != 0 || deltaY != 0) {
			horizontalAngle += deltaX * MOUSE_SENSITIVITY; // ADD SENSITIVY LATER
			verticalAngle += deltaY * MOUSE_SENSITIVITY;

			if (verticalAngle > PI/2.0f)
				verticalAngle = PI/2.0f;
			else if (verticalAngle < -PI/2.0f)
				verticalAngle = -PI/2.0f;
			
			camera_lookAround(C, horizontalAngle, verticalAngle);

			SDL_WarpMouseInWindow(window, WIDTH/2, HEIGHT/2);
		}


		/* FPS MOVEMENT */
		camera_move(C, mainCharacter);

		/* RENDERING */
		glClear(GL_COLOR_BUFFER_BIT);
		mesh_draw(triangulo, S, C, projection);
		SDL_GL_SwapWindow(window);
		SDL_Delay(1);
	}

	return 0;
}
