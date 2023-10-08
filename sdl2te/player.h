#pragma once
#include "imgRenderer.h"
#include "RayCasting.h"
#include "collisionHandler.h"
class player
{
private:
	int w, h;
	const char* texPath;
	SDL_Rect playerSZP = { 0,0,0,0 };
	SDL_Rect collisionBox = { 0,0,0,0 };
	bool collision = true;
public:
	player(SDL_Renderer* renderer, SDL_Window* window, const char* path);
	~player();
	double angle = 0.0f;
	float movementSpeed = 10.0f;
	image* plrIMG = NULL;

	void setPosition(vec2 pos)
	{
		this->playerSZP.x = pos.x;
		this->playerSZP.y = pos.y;
		if (collision)
		{
			this->collisionBox.x = pos.x;
			this->collisionBox.y = pos.y;
		}
	}
	vec2 getPosition()
	{
		vec2 pos = { playerSZP.x,playerSZP.y };
		return pos;
	}

	SDL_Rect getSDL_Rect(){return playerSZP;}
	void addSDL_RectXY(int x,int y)
	{
		this->playerSZP.x = this->playerSZP.x + x;
		this->playerSZP.y = this->playerSZP.y + y;
	}
	void setSize(int w1, int h1)
	{
		this->w = w1;
		this->h = h1;
		this->playerSZP.w = w1;
		this->playerSZP.h= h1;
		if (collision)
		{
			this->collisionBox.w = w1;
			this->collisionBox.h = h1;
		}
	}

	bool renderPlayer(SDL_Renderer* renderer, SDL_Window* window, collisionH* c)
	{

		if (this->collision == true)
		{
			c->thisObejctASN = this->collisionBox;
		}
		if (sizeof(playerSZP) > 0)
		{
			plrIMG->renderedPosition = this->playerSZP;
			plrIMG->createImage(renderer, angle);
			return true;
		}
		std::cout << "Could not create player image size or position not set!" << std::endl;
		return false;
	}
};

player::player(SDL_Renderer* renderer, SDL_Window* window, const char* path)
{
	this->texPath = path;
	plrIMG = new image(renderer, window, texPath);
}

player::~player() // cleanup
{
	delete this->plrIMG;
	delete this;
}