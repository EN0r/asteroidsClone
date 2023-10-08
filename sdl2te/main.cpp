#define _POSIX_SOURCE
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_sdl.h"
#include "vendor/imgui/imgui_impl_sdlrenderer.h"
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <string>
#include "SDL.h"
#include "wClass.h"
#include "imgRenderer.h"
#include "RayCasting.h"
#include "player.h"
#include "keyboard.h"
#include "collisionHandler.h"
#include "asteroid.h"
#include "windowBorder.h"

#define GET_VARIABLE_NAME(Variable) (#Variable)
#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

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
	SDL_Rect mouseRect = { 0,0,50,50 };
	rayCast r;
	geometry geoHandler;
	collisionH* collH = new collisionH();
	// setup window border control
	windowBorder winBorder(SCREENWIDTH, SCREENHEIGHT, 50);
	//geohandler
	//geoHandler.setRect(400,400,100,100);

	//making player
	player plr(renderer, window->window, "C:/items/charImage.PNG");
	plr.setSize(100, 100);
	vec2 pos = { (SCREENWIDTH/2)-50,(SCREENHEIGHT/2 )-50};
	plr.setPosition(pos);

	// other
	bool drawDebugGeometry = true;
	bool showUI = true;

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
	int aVelocityX = 5;
	int aVelocityY = 5;
	vec2 velocity = { aVelocityX,aVelocityY };
	bool ON = true;
	bool spawnAsteroidsM1 = true;
	// asteroid a(renderer,window->window,SCREENWIDTH,SCREENHEIGHT);

	static int defaultSpawnTime = 200;
	int timeToSpawn = 200;
	int defaultMoveTime = 3;
	int timeToMove = 3; // move every 3 frames
	//Objectlist
	std::vector<asteroid*> asteroidsInGame;
	//std::cout << GET_VARIABLE_NAME(geoHandler) << std::endl;
	//imgui stuff
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	std::string winlBuffer;
	bool mBdown = false;
	ImGui_ImplSDL2_InitForSDLRenderer(window->window, renderer);
	ImGui_ImplSDLRenderer_Init(renderer);
	while (ON)
	{
		frameTime++;
		Uint64 start = SDL_GetPerformanceCounter();

		deltaTime = oldtime - newtime;
		oldtime = newtime;
		//framecap
		//SDL_Delay(framecap - frametime);
		if (SDL_PollEvent(&e))
		{
			//std::cout << e.type << std::endl;
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				break;
			}
			if (e.type == 1025)
			{
				mBdown = true; 
			}
			if (e.type == 1026)
			{
				mBdown = false;
			}
		}

		ImGui_ImplSDL2_ProcessEvent(&e);

		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		mousePosition = SDL_GetMouseState(&cursorLocation.x, &cursorLocation.y);
		mouseRect.x = cursorLocation.x;
		mouseRect.y = cursorLocation.y;

		SDL_RenderClear(renderer);

		// game stuff

		//geoHandler.drawFbox(renderer,color);

		// Asteroid code

		// spawning code complete
		timeToMove = timeToMove - 1;
		if (spawnAsteroidsM1)
		{
			if (timeToSpawn <= 0)
			{
				//std::cout << "Spawning asteroid" << std::endl;
				asteroidsInGame.push_back(new asteroid(renderer, window->window,collH, SCREENWIDTH, SCREENHEIGHT));
				// need to update all roids
				timeToSpawn = defaultSpawnTime;
			}
			else {
				for (int i = 0; i < asteroidsInGame.size(); i++)
				{
					asteroidsInGame[i]->update(renderer, geoHandler, collH, frameTime);
					//std::cout << collH->collisionComps.size() << std::endl;
					//collH->drawCollisionBoxes(renderer);
					//std::cout << asteroidsInGame[i] << " ID->" << asteroidsInGame[i]->thisID << std::endl;
					if (asteroidsInGame.size() >= 25)
						asteroidsInGame.clear();
				}
			}
		}
		// Test code below
		/*
		
		if (frameTime == 1)
		{
			asteroidsInGame.push_back(new asteroid(renderer, window->window, collH, SCREENWIDTH, SCREENHEIGHT));
		}
		if (winBorder.borderCheck(asteroidsInGame[0]->obj->getRect(),winlBuffer))
		{
			if (winlBuffer == "w1")
			{
				asteroidsInGame[0]->setAsteroid(renderer, collH, asteroidsInGame[0]->obj->getRect().x, asteroidsInGame[0]->obj->getRect().y + (velocity.y*2));
				//std::cout << winlBuffer << std::endl;
			}

			if (winlBuffer == "w3")
			{
				asteroidsInGame[0]->setAsteroid(renderer, collH, asteroidsInGame[0]->obj->getRect().x, asteroidsInGame[0]->obj->getRect().y -(velocity.y*2));
				std::cout << -velocity.y << std::endl;

			}
		}
		*/
		// Test code End
		timeToSpawn = timeToSpawn - 1;
		// draw windowBorders
		winBorder.visualizeWindowBorder(renderer);
		for (auto var : asteroidsInGame) // completely remaking this game jesus its horrific
		{
			//std::cout << winBorder.borderCheck(mouseRect, winlBuffer) << std::endl;
			//vec2 velocity = { aVelocityX,aVelocityY }; inefficient why is this being initalized in a loop
			// make it if its near wall bounce
			//std::cout << var->getObjColliderPos(collH).x << "," << var->getObjColliderPos(collH).y << std::endl;
			if (mBdown)
			{
				if(tools::AABB(mouseRect, var->obj->getRect()))
				{
					var->setAsteroid(renderer, collH, mouseRect.x, mouseRect.y);
				}
			}

			if (tools::AABB(mouseRect, var->obj->getRect()))
			{

			}
			// set asteroid velocity 
			// when object collides velocity gets set to 0
			//or the object velocity inverses to a random point.
			if (winBorder.borderCheck(var->obj->getRect(), winlBuffer))
			{
				/*
				w1 draws top 0,0 collider border
				w2 draws right side collider border
				w3 creates bottom border
				w4 creates left side collision border
				*/

				// should use switch : case:
				if(winlBuffer == "w1")
				{
					var->setAsteroid(renderer,collH, var->obj->getRect().x,var->obj->getRect().y + var->velocity.y);
					var->velocity.y = -var->velocity.y;
					var->wallTouched = "w1";
				}
				if(winlBuffer == "w2")
				{
					var->setAsteroid(renderer,collH,var->obj->getRect().x +-var->velocity.x, var->obj->getRect().y);
					var->wallTouched = "w2";
					var->velocity.y = -var->velocity.x;
				}
				if(winlBuffer == "w3")
				{
					
					var->setAsteroid(renderer,collH,var->obj->getRect().x, var->velocity.y + -var->velocity.y);
					std::cout << "w3" << std::endl;
					var->wallTouched = "w3";
				}
				if(winlBuffer == "w4")
				{
					var->setAsteroid(renderer,collH,var->obj->getRect().x + var->velocity.x, var->obj->getRect().y);
					var->wallTouched = "w4";
				}
			}
			else {

				//var->moveAsteroid(renderer, collH, 0, -velocity.y);
				if (winBorder.borderCheck(var->obj->getRect(), winlBuffer) == false)
				{
					var->pushAsteroid(renderer,collH,NULL,NULL,vec2{5,0});
					//std::cout << winBorder.borderCheck(var->obj->getRect(), winlBuffer) << std::endl;
				}
				else { 
					var->pushAsteroid(renderer, collH, NULL, NULL, vec2{ -var->velocity.x,-velocity.y });
				}
				
			}
			
			collH->drawCollisionBoxes(renderer);
				
			if (var->collidesWith(plr.getSDL_Rect()))
			{
				//std::cout << "colliding" << std::endl;
			}
		}
		
		if (showUI)
		{
			ImGui_ImplSDLRenderer_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Begin("Debug");
				ImGui::SetWindowSize("Debug", { 500,300 });
				std::string fT = "FrameTime: "+std::to_string(frameTime);
				ImGui::Text(fT.c_str());
				std::string totalasteroids = std::to_string(asteroidsInGame.size());
				ImGui::Text(totalasteroids.c_str());
				ImGui::Text("Entities");
				std::vector<std::string> items;
				std::vector<std::string> strings;
				int currentItemI= 0;
				bool is_selected = false;
				bool Selecting = false;
				if (ImGui::BeginListBox("##items", { 120,100 }))
				{
					for (auto i : asteroidsInGame)
					{
						strings.push_back(std::to_string(i->thisID));
					}
					for (auto i = 0; i < strings.size(); i++)
					{	
						is_selected = (currentItemI == i);
						if (ImGui::Selectable(strings[i].c_str(), &is_selected))
							currentItemI = i;
						if (is_selected)
						{
							Selecting = true;
							//ImGui::SetItemDefaultFocus();
						}

					}
					ImGui::EndListBox();

					ImGui::SliderInt("Spawn Time", &defaultSpawnTime, 0, 200);
					ImGui::SliderInt("VelocityX", &aVelocityX, 1, 20);
					ImGui::SliderInt("VelocityY", &aVelocityY, 1, 20);

					if (Selecting)
					{
						std::string s = std::to_string(currentItemI);
						ImGui::Text(s.c_str());

					}
					if (is_selected)
					{
					}

					ImGui::End();
				}
			}
		}
		// Need to make character movable and assign HP to each of asteroids tomorrow
		vec2 mPos = { cursorLocation.x,cursorLocation.y };
		int angleRotation = r.anglefromPosition(pos, mPos);
		plr.angle = angleRotation;
		
		// Player Creator
		plr.renderPlayer(renderer,window->window,collH);

		//end

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);

		state = SDL_GetKeyboardState(NULL);



		if (drawDebugGeometry)
		{
			collH->drawCollisionBoxes(renderer);
			
		}
		
		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(16.666f - elapsedMS));
		
	}
	asteroidsInGame.clear();

	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_Quit();
	return 0;
}
