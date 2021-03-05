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

void Player::Draw(SDL_Renderer* render)
{
	sourceRect.x = (direction-1) * 128;
	distRect.x = 1920/2-sourceRect.w/2 ;
	distRect.y = 1080/2-sourceRect.h/2;
	SDL_RenderCopy(render, PlayerTexture, &sourceRect, &distRect);
	distRect.x = (1920/2-3.0/2*sourceRect.w);
	SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
	SDL_RenderDrawRect(render, &distRect);
}

void Player::Move(int direction)
{
	switch (direction) {
	case 0: playerPos.x--; break;
	case 1:playerPos.y--; break;
	case 2: playerPos.x++; break;
	case 3:playerPos.y++; break;
	}
	direction = direction;
}
