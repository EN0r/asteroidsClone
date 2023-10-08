#pragma once
#include "player.h"
#include <vector>
class collisionH
{
public:
	std::vector<SDL_Rect> collisionComps;
	SDL_Rect thisObejctASN = {0,0,0,0};

	

	inline bool objectCollidesWith()
	{
		if (collisionComps.size() > 0)
		{
			for (int i = 0; i < collisionComps.size(); i++)
			{
				SDL_Rect object2 = collisionComps[i]; // i-1 because vectors start at 0
				if (thisObejctASN.x < object2.x + object2.w &&
					thisObejctASN.x + thisObejctASN.w > object2.x &&
					thisObejctASN.y < object2.y + object2.h &&
					thisObejctASN.y + thisObejctASN.h> object2.y)
					{
					return true;
					}
				return false;
			}
		}
	}

	inline void drawCollisionBoxes(SDL_Renderer* renderer, SDL_Color color = {0,255,0,255})
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (auto i : collisionComps)
		{
			SDL_RenderDrawRect(renderer, &i);
		}
	}


};
