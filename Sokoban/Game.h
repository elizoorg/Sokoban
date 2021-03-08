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
	bool LevelInit();
	void Scores();

	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event event;
	EventHandler* handler;
	bool _end = false;
	int FPS = 60;
	int lastFrame, frameCount,lastTime,timerFPS;

	vector <string> levels;
	int currentlevel = 0;

	TTF_Font* font;
	SDL_Color fontColor{ 255,255,255 };
	SDL_Rect fontRect{ 0,0,64,128 };
	SDL_Rect rulesRect{ 1520,0,64,128 };
	float scale = 1;
	int nx, ny, mx, my;
	bool pressed;
	
	bool writeScore = 0;

	int steps = 0;
	int levelstep = 0;

	int startX=0, startY=0;

	Player player;
	Level level;

};

