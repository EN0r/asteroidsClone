#define _POSIX_SOURCE
#include <iostream>
#include <filesystem>
#include "SDL.h"
#include "wClass.h"
#include "imgRenderer.h"
#include "RayCasting.h"

struct mousePosi
{
	int x;
	int y;
};

int main(int argc, char** argv)
{
	_sdlWindow* window = new _sdlWindow(800,600,100,100,"Hello World!", SDL_WINDOW_OPENGL);
	SDL_Event e;
	SDL_Surface* surf;
	SDL_Renderer* renderer = window->getRenderer(NULL,surf);
	image* ImgTest= new image(renderer,window->window,surf,"C:/items/charImage.PNG");
	Uint32 mousePosition = NULL;
	mousePosi cursorLocation = { 0,0 };
	rayCast r;
	vec2 pos1 = { 0 , 0 };
	vec2 pos2 = { 100,100 };
	geometry geoHandler;


	bool drawDebugGeometry = false;

	vec2 oRpos = {
		oRpos.x = ImgTest->renderedPosition.x,
		oRpos.y = ImgTest->renderedPosition.y
	};

	ImgTest->setRenderedPosition(100, 100, 64, 64);
	
	while (true)
	{

		if (SDL_PollEvent(&e) == SDL_QUIT)
			break;


		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		mousePosition = SDL_GetMouseState(&cursorLocation.x, &cursorLocation.y);
		
		SDL_RenderClear(renderer);
		if (drawDebugGeometry)
		{
			pos1.x = cursorLocation.x;
			pos1.y = cursorLocation.y;
			geoHandler.drawLine(renderer,pos1, pos2);
			
		}
		
		// game stuffs

		ImgTest->setAngle(r.angleBetweenPos(pos1, oRpos));
		std::cout << r.angleBetweenPos(oRpos, pos1) << std::endl;
		ImgTest->createImage(renderer);


		//end
		SDL_RenderPresent(renderer);


	}

	SDL_Quit();
	return 0;
}