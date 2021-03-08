#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Init(SDL_Renderer* render, std::string filepath)
{
	SDL_Surface* temp = IMG_Load(filepath.c_str());
	PlayerTexture = SDL_CreateTextureFromSurface(render,temp);
	SDL_FreeSurface(temp);
	if (!PlayerTexture) return false;
	return true;
}

void Player::Draw(SDL_Renderer* render,float scale, int startX, int startY)
{
	distRect.w = distRect.h = 128 * scale;
	sourceRect.x = (direction) * 128;
	distRect.x = (playerPos.x)*128*scale+startX;
	distRect.y = (playerPos.y)*128*scale+startY;
	SDL_RenderCopy(render, PlayerTexture, &sourceRect, &distRect);
	SDL_RenderDrawRect(render, &distRect);
}

void Player::Move(int dir)
{
	switch (dir) {
	case 0: playerPos.x--; break;
	case 1:playerPos.y--; break;
	case 2: playerPos.x++; break;
	case 3:playerPos.y++; break;
	}
    direction = dir;
}
