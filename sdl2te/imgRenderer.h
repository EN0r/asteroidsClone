#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "RayCasting.h"

class image
{
private:
	SDL_Window* window = NULL;
	SDL_Surface* surf = NULL;
	SDL_Texture* tex = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	double angle = 0.0f;
public:
	void setAngle(double angle1) { this->angle = angle; }
	SDL_Rect renderedPosition;
	void setRenderedPosition(float x, float y, float w, float h) // bit obsolete code tbf
	{
		renderedPosition.x = x;
		renderedPosition.y = y;
		renderedPosition.w = w;
		renderedPosition.h = h;
	}

	void flipImage(SDL_RendererFlip flipIMG){this->flip = flipIMG;}

	image(SDL_Renderer* render, SDL_Window* wnd, const char* filePath)
	{
		this->surf = IMG_Load(filePath);
		this->tex = SDL_CreateTextureFromSurface(render, this->surf);
		printf(SDL_GetError());
		this->window = wnd;
	}
	~image()
	{
		delete this->surf;
		delete this->window;
	}

	void createImage(SDL_Renderer* renderer,double angle)
	{
		SDL_RenderCopyEx(renderer,this->tex,NULL,&this->renderedPosition,angle,NULL,flip);
	}

};


class geometry
{
private:



public:

	void drawLine(SDL_Renderer* renderer, vec2 pos1, vec2 pos2)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawLineF(renderer,pos1.x, pos1.y, pos2.x, pos2.y);
	}

};

