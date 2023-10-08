#pragma once
#include "objectManager.h"
#include "asteroidManager.h"
#include <cstdlib>
#include <chrono>

class asteroid
{
private:
	vec2 position;
	vec2 thisSize_;
	int maxW = 100;
	int maxH = 100;
	const char* path = "C:/items/asteroid.png";
	bool initalised = false;
public:
	std::string wallTouched = "NULL";
	vec2 velocity = { 0,0 };
	int thisID = -1;
	object* obj = NULL; // image rendered onto this
	void update(SDL_Renderer* renderer, geometry g, collisionH* cHandler, int frameTime);
	
	inline bool collidesWith(SDL_Rect r1) // put plr pos here
	{
		if (obj->thisSize.x < r1.x + r1.w &&
			obj->thisSize.x + obj->thisSize.w > r1.x &&
			obj->thisSize.y < r1.y + r1.h &&
			obj->thisSize.y + obj->thisSize.h> r1.y)
		{
			return true;
		}
		return false;
	}

	asteroid(SDL_Renderer* renderer, SDL_Window* window, collisionH* h, int MAXX, int MAXY)
	{
		int xPos = rand() % MAXX;
		int yPos = rand() % MAXY;

		initalised = true;
		// init obj here
		this->position = {(float)xPos, (float)yPos};
		obj = new object(renderer, window, xPos, yPos, maxW, maxH, path);
		obj->update(renderer,h,thisID);
	}
	~asteroid()
	{
		delete obj;
		delete this;
	}
	inline void moveAsteroid(SDL_Renderer* renderer,collisionH* collisionHandler,int newposX, int newposY)
	{
		// when move i will need to update the value in collision handler
		collisionHandler->collisionComps[thisID-1] = { collisionHandler->collisionComps[thisID-1].x + newposX,collisionHandler->collisionComps[thisID-1].x + newposY ,  collisionHandler->collisionComps[thisID-1].w,collisionHandler->collisionComps[thisID-1].h};
		this->position = { position.x + newposX, position.y + newposY };
		this->obj->setPosition({this->position.x + (float)newposX,this->position.y + (float)newposY});
	}
	inline void setAsteroid(SDL_Renderer* renderer,collisionH* collisionHandler,int newposX, int newposY)
	{
		// when move i will need to update the value in collision handler
		collisionHandler->collisionComps[thisID-1] = { newposX,newposY ,  collisionHandler->collisionComps[thisID-1].w,collisionHandler->collisionComps[thisID-1].h};
		this->position = { (float)newposX, (float)newposY };
		this->obj->setPosition({(float)newposX,(float)newposY});
	}

	inline void pushAsteroid(SDL_Renderer* renderer,collisionH* handler,int sWidth, int sHeight,vec2 velocity_)
	{
		this->velocity = velocity_;
		moveAsteroid(renderer, handler, velocity.x, velocity.y);
	}
	inline vec2 getPosition()
	{
		return position;
	}
	inline SDL_Rect getObjColliderPos(collisionH* handler)
	{
		return handler->collisionComps[(this->thisID)-1];
	}

};

void asteroid::update(SDL_Renderer* renderer,geometry g, collisionH* cHandler, int frameTime) // store positions in ObjectHandler
{
	//std::cout << frameTime << std::endl;
	if (initalised == false)
		obj->update(renderer, cHandler,this->thisID);
	cHandler->collisionComps[thisID - 1] = this->obj->thisSize;
	obj->renderObject(renderer,cHandler);
}
