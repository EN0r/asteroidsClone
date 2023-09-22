#define _POSIX_SOURCE
#include <iostream>
#include <filesystem>
#include "SDL.h"
#include "wClass.h"
#include "imgRenderer.h"
#include "RayCasting.h"
#include "player.h"
#include "keyboard.h"
#include "collisionHandler.h"
#include "asteroid.h"


// macros

struct mousePosi
{
	int x;
	int y;
};

int main(int argc, char** argv)
{
	int SCREENWIDTH = 800;
	int SCREENHEIGHT = 600;

	// inits
	_sdlWindow* window = new _sdlWindow(SCREENWIDTH,SCREENHEIGHT,100,100,"Hello World!", SDL_WINDOW_OPENGL);
	SDL_Event e;
	SDL_Surface* surf = NULL;
	SDL_Renderer* renderer = window->getRenderer(SDL_RENDERER_PRESENTVSYNC || SDL_RENDERER_ACCELERATED,surf);
	Uint32 mousePosition = NULL;
	mousePosi cursorLocation = { 0,0 };
	rayCast r;
	geometry geoHandler;
	collisionH* collH = new collisionH();

	//geohandler
	geoHandler.setRect(400,400,100,100);

	//making player
	player plr(renderer, window->window, "C:/items/charImage.PNG");
	plr.setSize(100, 100);
	vec2 pos = { (SCREENWIDTH/2)-50,(SCREENHEIGHT/2 )-50};
	plr.setPosition(pos);

	// other
	bool drawDebugGeometry = true;


	keyboard keyBoard;
	const Uint8* state;

	SDL_Color color = {255,0,0,255};
	//object o(renderer,window->window,400,400,100,100);

	SDL_Scancode lastKeyPress;

	bool playerColliding = false;

	float oldtime = 0.0f;
	float newtime = 0.0f;
	float deltaTime = 0.0f;
	float framecap = 1;
	int frameTime = 0;
	// asteroid a(renderer,window->window,SCREENWIDTH,SCREENHEIGHT);

	int timeToSpawn = 20;

	//Objectlist
	std::vector<asteroid*> asteroidsInGame;

	while (true)
	{
		frameTime++;
		Uint64 start = SDL_GetPerformanceCounter();

		deltaTime = oldtime - newtime;
		oldtime = newtime;
		//framecap
		//SDL_Delay(framecap - frametime);
		if (SDL_PollEvent(&e) == SDL_QUIT)
			break;
		
		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		mousePosition = SDL_GetMouseState(&cursorLocation.x, &cursorLocation.y);
		SDL_RenderClear(renderer);
		SDL_PumpEvents();
		
		// game stuff

		//geoHandler.drawFbox(renderer,color);

		// Asteroid code

		// spawning code complete

		timeToSpawn = timeToSpawn -1;
		if (timeToSpawn <= 0)
		{
			std::cout << "Spawning asteroid" << std::endl;
			asteroidsInGame.push_back(new asteroid(renderer, window->window, SCREENWIDTH, SCREENHEIGHT));
			// need to update all roids
			timeToSpawn = 200;
		}
		else {
			for (int i = 0; i < asteroidsInGame.size(); i++)
			{
				asteroidsInGame[i]->update(renderer, geoHandler, collH, frameTime);
			}
		}
		// Player Creator
		plr.renderPlayer(renderer,window->window,collH);
		
		// Need to make character movable and assign HP to each of asteroids tomorrow



		//end
		SDL_RenderPresent(renderer);

		state = SDL_GetKeyboardState(NULL);



		if (drawDebugGeometry)
		{
			
			
		}
		
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(16.666f - elapsedMS));
		

	}


	for (int i = 0; i < asteroidsInGame.size(); i++)
	{
		delete asteroidsInGame[i];
	}
	SDL_Quit();
	return 0;
}
