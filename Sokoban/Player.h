#pragma once
#include <SDL.h>
#include "Vector.h"
#include <SDL_image.h>
class Player
{
public:
	Player();
	~Player();
	bool Init(SDL_Renderer* render,std::string filepath);
	void setPos(vec2i pos) { playerPos = pos; }
	void Draw(SDL_Renderer* render, float scale, int startX, int startY);
	void Move(int dir);

private:
	SDL_Texture* PlayerTexture;
	vec2i playerPos;
	int direction=3;
	SDL_Rect sourceRect{ 0,0,128,128 };
	SDL_Rect distRect{ 0,0,128,128 };
};

