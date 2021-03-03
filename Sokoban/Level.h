#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <fstream>
#include "Vector.h"

class Level
{
public:
	~Level();
	Level();
	bool LoadLevel(SDL_Renderer* render, std::string filePath,std::string tileMapPath);
	void Draw(SDL_Renderer* render);
	vec2i getplayerPos() { return playerPos; }
	int getTile(int x, int y) { return map[y][x]; }
	bool Move(int direction);

private:
	int **map;
	int w, h;
	SDL_Texture* tilemap;
	SDL_Rect sourceRect{ 0,0,128,128 };
	SDL_Rect destRect{ 0,0,128,128 };
	vec2i playerPos;
};

