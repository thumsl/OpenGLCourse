#include "window.h"
#include <GL/glew.h>

int main() {

	SDL_Window* window = window_create("3D Game Engine", 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	SDL_GL_SwapWindow(window);
	SDL_Delay(2000);
	return 0;
}
