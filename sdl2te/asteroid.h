#pragma once
#include "objectManager.h"
#include "asteroidManager.h"
#include <cstdlib>

class asteroid
{
private:
	object* obj = NULL; // image rendered onto this
	vec2 position;
	vec2 thisSize_;
	int maxW = 100;
	int maxH = 100;
	const char* path = "C:/items/asteroid.png";
	bool initalised = false;
public:
	void update(SDL_Renderer* renderer, geometry g, collisionH* cHandler, int frameTime);
	asteroid(SDL_Renderer* renderer, SDL_Window* window,int MAXX, int MAXY)
	{
		int xPos = rand() % MAXX;
		int yPos = rand() % MAXY;
		
		initalised = true;
		// init obj here
		obj = new object(renderer, window, xPos, yPos, maxW, maxH, path);
	}
	~asteroid()
	{
		delete obj;
		delete this;
	}
};

void asteroid::update(SDL_Renderer* renderer,geometry g, collisionH* cHandler, int frameTime) // store positions in ObjectHandler
{
	//std::cout << frameTime << std::endl;
	if (initalised == false)
		obj->update(renderer, g, cHandler);
	obj->renderObject(renderer,cHandler);
}
