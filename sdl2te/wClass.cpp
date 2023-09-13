#include "wClass.h"
_sdlWindow::_sdlWindow(int w, int h, int posx, int posy, const char* windowName,Uint32 flags)
{
	this->window = SDL_CreateWindow(windowName,posx,posy,w,h,flags);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
	}
}