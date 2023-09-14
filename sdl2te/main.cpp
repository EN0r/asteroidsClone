#define _POSIX_SOURCE
#include <iostream>
#include <filesystem>
#include "SDL.h"
#include "wClass.h"
#include "imgRenderer.h"
#include "RayCasting.h"
#include "player.h"
#include "keyboard.h"

struct mousePosi
{
	int x;
	int y;
};

int main(int argc, char** argv)
{
	_sdlWindow* window = new _sdlWindow(800,600,100,100,"Hello World!", SDL_WINDOW_OPENGL);
	SDL_Event e;

	SDL_Surface* surf = NULL;
	SDL_Renderer* renderer = window->getRenderer(NULL,surf);
	Uint32 mousePosition = NULL;
	mousePosi cursorLocation = { 0,0 };
	rayCast r;
	vec2 pos1 = { 0 , 0 };
	geometry geoHandler;

	player plr(renderer, window->window, "C:/items/charImage.PNG");
	vec2 pos = { 100,100 };
	plr.setPosition(pos);
	plr.setSize(100, 100);
	bool drawDebugGeometry = true;

	keyboard keyBoard;
	const Uint8* state;
	while (true)
	{
		if (SDL_PollEvent(&e) == SDL_QUIT)
			break;


		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		mousePosition = SDL_GetMouseState(&cursorLocation.x, &cursorLocation.y);
		SDL_RenderClear(renderer);
		SDL_PumpEvents();
		
		state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W])
		{
			plr.addSDL_RectXY(0, -1);

		}		
		if (state[SDL_SCANCODE_S])
		{
			plr.addSDL_RectXY(0, 1);

		}		
		if (state[SDL_SCANCODE_A])
		{
			plr.addSDL_RectXY(-1, 0);

		}		
		if (state[SDL_SCANCODE_D])
		{
			plr.addSDL_RectXY(1, 0);

		}

		if (drawDebugGeometry)
		{
			
			
		}
		
		// game stuffs
		
		plr.renderPlayer(renderer,window->window);


		//end
		SDL_RenderPresent(renderer);


	}

	SDL_Quit();
	return 0;
}