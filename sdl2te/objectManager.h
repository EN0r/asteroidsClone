#pragma once
#include "player.h"
class object
{
private:
	const char* filepath;
	bool canCollide = true;
	SDL_Color color = { 255,0,0,255 };
public:
	bool renderasImage = true;
	bool collisionDetected = false;
	SDL_Rect thisSize = { 0,0,0,0 };
	image* objIMG = NULL;
	double angle = 0.0f;

	object(SDL_Renderer* renderer, SDL_Window* window, int x = 0, int y = 0, int w = 0, int h = 0, const char* path = "C:/items/error.png", SDL_Color col = {255,0,0,255}) // if no color picked then it defaults as red
	{
		thisSize = { x,y,w,h };
		if (path != NULL)
		{
			filepath = path;
		}

		this->filepath = path;
		objIMG = new image(renderer, window,filepath);
	}

	~object()
	{
		delete this->objIMG;
		delete this;
	}
	inline void setPosition(vec2 pos)
	{
		this->thisSize.x = pos.x;
		this->thisSize.y = pos.y;
	}

	inline void setSize(int w, int h)
	{
		this->thisSize.w = w;
		this->thisSize.h = h;
	}

	inline void addSDL_RectXY(int x, int y)
	{
		this->thisSize.x = this->thisSize.x + x;
		this->thisSize.y = this->thisSize.y + y;
	}

	bool renderObject(SDL_Renderer* renderer, collisionH* collhandler)
	{
		if (this->collisionDetected == true)
		{
			collhandler->thisObejctASN = this->thisSize;
		}
		if (sizeof(thisSize) > 0)
		{
			objIMG->renderedPosition = this->thisSize;
			objIMG->createImage(renderer, angle);
			return true;
		}
		std::cout << "Could not create player image size or position not set!" << std::endl;
		return false;
	}

	inline void update(SDL_Renderer* renderer, geometry h,collisionH *collhandle) 
	{
		if (this->canCollide)
		{
			collhandle->collisionComps.push_back(this->thisSize);
			if (collhandle->objectCollidesWith())
			{
				std::cout << "Colliding!!" << std::endl;
				collisionDetected = true;
			}
			else { collisionDetected = false; }
		}
		if (renderasImage)
		{
			this->renderObject(renderer,collhandle);
		}
		else
		{
			h.drawFbox(renderer, this->color);
		}
	}

};