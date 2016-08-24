#include <stdio.h>
#include <GL/glew.h>
#include "window.h"

SDL_Window* window_create(const char *title, int w, int h) {
	/* Initialize SDL 
	First:
		SDL_Init(FLAG);
	then:
		if() ... else [Error handling];

	*/

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr,"Failure initializing SDL:\n%s\n", SDL_GetError()); // SDL_GetError -> retorna char*
		return NULL;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *window;

	/*
		SDL FLAGS:
			SDL_WINDOW_OPENGL, SDL_WINDOW_FULLSCREEN
	*/

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL) {
		fprintf(stderr, "Failure creating window:\n%s\n", SDL_GetError());
		return NULL;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Add this later!
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return window;
}

/*
void window_destroy() {
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
}
*/
