#include <stdio.h>
#include "window.h"

SDL_Window* window_create(const char *title, int w, int h) {
	/* Initialize SDL 
		First:
			SDL_Init(FLAG);
		then:
			if() ... else [Error handling];
	*/

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr,"Error: SDL intialization failed.\n%s\n", SDL_GetError()); // SDL_GetError -> retorna char*
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

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);

	if (window == NULL) {
		fprintf(stderr, "Error: window creation failed.\n%s\n", SDL_GetError());
		return NULL;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	/* TUT06 */
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(window, SDL_TRUE);
	SDL_WarpMouseInWindow(window, 0, 0);

	return window;
}

/*
void window_destroy() {
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
}
*/

void window_warpMouseTo() {}