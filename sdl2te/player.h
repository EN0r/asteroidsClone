#pragma once
#include "imgRenderer.h"
#include "RayCasting.h"
class player
{
private:
	int w, h;
	const char* texPath;
	SDL_Rect playerSZP = { 0,0,0,0 };
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
	}

	bool renderPlayer(SDL_Renderer* renderer, SDL_Window* window)
	{
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