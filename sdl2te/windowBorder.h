#pragma once
#include "asteroid.h"
#define GET_VARIABLE_NAME(Variable) (#Variable)
namespace tools
{

	inline bool AABB(SDL_Rect obj, SDL_Rect r1) // bounding box collision use for gui ect
	{
		if (obj.x < r1.x + r1.w &&
			obj.x + obj.w > r1.x &&
			obj.y < r1.y + r1.h &&
			obj.y + obj.h> r1.y)
		{
			return true;
		}
		return false;
	}
}

class windowBorder
{
private:
	// create borders
	std::vector<SDL_Rect> borders;
	// init index for border control
	int i = 0;
public:
	windowBorder(int screenWidth = 800, int screenHeight = 600, int borderColliderSize = 10) // Constructor sets window height
	{
		SDL_Rect w1 = { 0,0,screenWidth,borderColliderSize }; // draws top 0,0 collider border
		SDL_Rect w2 = { (screenWidth- borderColliderSize),0,borderColliderSize,screenHeight }; // draws right side collider border
		SDL_Rect w3 = { 0,(screenHeight- borderColliderSize),screenWidth,borderColliderSize }; // creates bottom border
		SDL_Rect w4 = { 0,0,borderColliderSize,(screenHeight) }; // creates left side collision border
		borders.insert(borders.end(), { w1,w2,w3,w4 });
	}
	inline bool borderCheck(SDL_Rect r, std::string& wallID)
	{
		for (int i = 0; i<borders.size(); i++)
		{
			if (i == 0)
				wallID = "w1";
			if (i == 1)
				wallID = "w2";
			if (i == 2)
				wallID = "w3";
			if (i == 3)
				wallID = "w4";
			if (tools::AABB(r, borders[i]))
				return true;
		}
		return false;
	}
	inline void visualizeWindowBorder(SDL_Renderer* renderer, SDL_Color color = { 0,255,0,255})
	{
		for (SDL_Rect var : borders)
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawRect(renderer, &var);
		}
	}
};

