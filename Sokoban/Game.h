#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "EventHandler.h"
#include "Level.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	void Start();
private:
	void Input();
	void Loop();
	void Draw();
	bool Init();
	void Update();

	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event event;
	EventHandler* handler;
	bool _end = false;
	int FPS = 60;
	int lastFrame, frameCount,lastTime,timerFPS;

	Player player;
	Level level;

};

