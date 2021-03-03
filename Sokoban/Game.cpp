#include "Game.h"
#include <iostream>
#include <string>

using namespace std;
Game::Game()
{
}

Game::~Game()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Start()
{
    _end = Init();
    handler = EventHandler::Instance();
    while (_end) {
        Loop();
    }
}

void Game::Input()
{
    if (handler->KeyDown(SDLK_ESCAPE)) {
        _end = false;
    }
    if (handler->KeyDown(SDLK_a)) {
        if(level.Move(0))
        player.Move(0);
    }
    
    if (handler->KeyDown(SDLK_w)) {
        if (level.Move(1))
        player.Move(1);
    }
    if (handler->KeyDown(SDLK_d)) {
        if (level.Move(2))
        player.Move(2);
    }
    if (handler->KeyDown(SDLK_s)) {
        if (level.Move(3))
        player.Move(3);
    }
   
}

void Game::Loop()
{
    Uint64 start = SDL_GetPerformanceCounter();
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) _end = false;
        handler->Handle(&event);
    }
    Input();
    Update();
    Draw();
   
    Uint64 end = SDL_GetPerformanceCounter();
    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
}

void Game::Draw()
{
    SDL_RenderClear(render);

    level.Draw(render);
    player.Draw(render);

    SDL_RenderPresent(render);
}

void Game::Update()
{
    
}


bool Game::Init()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("An SDL2 window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1920,1080,SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return false;
    }
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL) {
        std::cout << "Could not create render: " << SDL_GetError() << '\n';
        return false;
    }

    if (!level.LoadLevel(render,"levels/1.txt","texture/tilemap.png")) {
        std::cout << "Count not load a level: level.txt\n";
        return false;
    }
    if (!player.Init(render, "texture/player.png")) {
        std::cout << " Count not to init a player \n";
        return false;
    }
    player.setPos(level.getplayerPos());

	return true;
}

