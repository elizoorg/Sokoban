#include "Game.h"
#include <iostream>
#include <string>


struct play {
    char Name[20]="Player";
    int score;
}player_score, player1;

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
    if (writeScore) {
        Scores();
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
        levelstep++;
    }
    
    if (handler->KeyDown(SDLK_w)) {
        if (level.Move(1))
        player.Move(1);
        levelstep++;
    }
  
    if (handler->KeyDown(SDLK_d)) {
        if (level.Move(2))
        player.Move(2);
        levelstep++;
    }
   
    if (handler->KeyDown(SDLK_s)) {
        if (level.Move(3))
        player.Move(3);
        levelstep++;
    }
   
    if (handler->KeyDown(SDLK_r)) {
        if (!level.LoadLevel(render, levels[currentlevel], "texture/tilemap.png")) {
            std::cout << "Count not load a level: " << levels[currentlevel] << endl;   
        }
        player.setPos(level.getplayerPos());
        levelstep = 0;
   }

   

}

void Game::Loop()
{
    lastFrame = SDL_GetTicks();
    if (lastFrame >= (lastTime + 1000) ){
        lastTime=lastFrame;
        FPS=frameCount;
        frameCount=0;
    }

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) _end = false;
        if (event.type == SDL_MOUSEWHEEL) {
            scale += (float)event.wheel.y / 20;
            if (scale > 1) scale -= (float)2 / 20;
            if (scale < 0.5) scale += (float)2 / 20;
        }
        
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            nx = event.button.x;
            ny = event.button.y;
            pressed = true;
        }
        if (event.type == SDL_MOUSEMOTION) {
            mx = event.motion.x;
            my = event.motion.y;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            pressed = false;
        }
        handler->Handle(&event);
    }

    Input();

    Update();

    Draw();
  

}

void Game::Draw()
{
    SDL_RenderClear(render);
   
    level.Draw(render,scale,startX,startY);
    player.Draw(render,scale, startX, startY);
    frameCount++;

    char buf[30];
    sprintf(buf, "%d / %d", levelstep,steps);
    SDL_Surface* text;
    text = TTF_RenderUTF8_Solid(font, buf, fontColor);
    SDL_Texture* temp = SDL_CreateTextureFromSurface(render, text);
    fontRect.w = text->w;
    fontRect.h = text->h;
    SDL_RenderCopy(render, temp, 0, &fontRect);
    SDL_DestroyTexture(temp);
    SDL_FreeSurface(text);
 
    sprintf(buf, "%s","WASD - move");

    text = TTF_RenderUTF8_Solid(font, buf, fontColor);
    temp = SDL_CreateTextureFromSurface(render, text);
    rulesRect.y = 0;
    rulesRect.w = text->w;
    rulesRect.h = text->h;
    SDL_RenderCopy(render, temp, 0, &rulesRect);
    SDL_DestroyTexture(temp);
    SDL_FreeSurface(text);

    sprintf(buf, "%s","Scroll - zoom");
    text = TTF_RenderUTF8_Solid(font, buf, fontColor);
    temp = SDL_CreateTextureFromSurface(render, text);
    rulesRect.y = 64;
    rulesRect.w = text->w;
    rulesRect.h = text->h;
    SDL_RenderCopy(render, temp, 0, &rulesRect);
    SDL_DestroyTexture(temp);
    SDL_FreeSurface(text);

    sprintf(buf, "Left mouse - move map ");
    text = TTF_RenderUTF8_Solid(font, buf, fontColor);
    temp = SDL_CreateTextureFromSurface(render, text);
    rulesRect.y = 128;
    rulesRect.w = text->w;
    rulesRect.h = text->h;
    SDL_RenderCopy(render, temp, 0, &rulesRect);
    SDL_DestroyTexture(temp);
    SDL_FreeSurface(text);



    timerFPS = SDL_GetTicks()-lastFrame;
    if (timerFPS < (1000 / 15))
        SDL_Delay(1000 / 15-timerFPS);

    SDL_RenderPresent(render);
}

void Game::Update()
{
    if (level.win()) {
        if (currentlevel == levels.size() - 1) {
            steps += levelstep;
            _end = false;
            writeScore = true;
            player1.score = steps;
        }
        else {
            currentlevel++;
            if (!level.LoadLevel(render, levels[currentlevel], "texture/tilemap.png")) {
                std::cout << "Count not load a level: " << levels[currentlevel] << endl;
            }
            player.setPos(level.getplayerPos());
            steps += levelstep;
            levelstep = 0;
        }
    }
    if (pressed) {
        startX += (int)(mx - nx) / 16;
        startY += (int)(my - ny) / 16;
    }
}

bool Game::LevelInit()
{
    ifstream buf; 
    string s;
    buf.open("levels/levels.txt");
    while (buf >> s) {
        levels.push_back(s);
    }
    buf.close();
    return levels.size();
}

void Game::Scores()
{


    SDL_Event event;
    bool done = false;
    char symbol;
    int i = 0;
    char buff[25] = {};
    TTF_Font* font;
    int mouseX, mouseY;
    bool lButton=false;
    SDL_Color color_fon{ 255,128,64 };
    SDL_Rect r{ 100,200,0,0 };
    font = TTF_OpenFont("CharisSILR.ttf", 48);
    SDL_Surface* text_surface;
    SDL_Surface* name_surface = NULL;
    SDL_Texture* text;
    SDL_Texture* name;

    SDL_Rect button{ 450,532,384,64 };


    SDL_RenderClear(render);
  
 
 
    player1.score = steps;
    sprintf(buff, "%d", player1.score);

    while (!done) {
        while (SDL_PollEvent(&event))
            switch (event.type) {
            case SDL_QUIT: done = true; break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    lButton = true;
                    SDL_GetMouseState(&mouseX, &mouseY);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    lButton = false;
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym != SDLK_BACKSPACE) {
                    symbol = (char)event.key.keysym.sym;
                    player1.Name[i++] = symbol;
                    if (i > 10) i--;

                }
                if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (i > 0)
                        player1.Name[--i] = '\0';
                    if (i == 0) player1.Name[0] = ' ';


                }
                break;
            }
        if (lButton) {
            if (mouseX > 450 && mouseX < 934) {
                if (mouseY > 532 && mouseY < 596) {
                    mouseX = mouseY = 0;
                    done = true;
                }
            }
        }
        SDL_SetRenderDrawColor(render, 230, 230, 255, 0);
        SDL_RenderClear(render);
        
        r.y = 150;
        text_surface = TTF_RenderUTF8_Solid(font, "Your Score is: ", color_fon);
        r.w = text_surface->w;
        r.x = 640 - r.w / 2;
        r.h = text_surface->h;
        text = SDL_CreateTextureFromSurface(render, text_surface);
        SDL_FreeSurface(text_surface);
        SDL_RenderCopy(render, text, NULL, &r);
        SDL_DestroyTexture(text);
        text_surface = TTF_RenderUTF8_Solid(font, buff, color_fon);
        r.y = 250;
        r.w = text_surface->w;
        r.x = 640 - r.w / 2;
        r.h = text_surface->h;
        text = SDL_CreateTextureFromSurface(render, text_surface);
        SDL_FreeSurface(text_surface);
        SDL_RenderCopy(render, text, NULL, &r);
        SDL_DestroyTexture(text);
        name_surface = TTF_RenderUTF8_Solid(font, player1.Name, color_fon);
        r.y = 350;
        r.w = name_surface->w;
        r.x = 640 - r.w / 2;
        r.h = name_surface->h;

        name = SDL_CreateTextureFromSurface(render, name_surface);
        SDL_FreeSurface(name_surface);
        SDL_SetRenderDrawColor(render, 153, 153, 255, 0);
        SDL_RenderFillRect(render, &button);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
        SDL_RenderCopy(render, name, NULL, &r);
        SDL_DestroyTexture(text);
        SDL_DestroyTexture(text);
        SDL_DestroyTexture(name);
        SDL_RenderPresent(render);
    }


    int c = 0;
    bool flag = 1;
    FILE* file1;
    if ((file1 = fopen("scores", "rb")) == NULL)
    {
        if ((file1 = fopen("scores", "wb")) == NULL)
        {
            perror("Error create file");
            return;
        }
        return;
    }
    FILE* file2;
    if ((file2 = fopen("score1", "wb")) == NULL)
    {
        perror("Error create file");
        return;
    }
    while (flag && c < 9) 
    {
        flag = fread(&player_score, sizeof(player_score), 1, file1);
        if (flag)
        {
            if (player_score.score < player1.score)
                fwrite(&player_score, sizeof(player_score), 1, file2);
            else
            {
                if (player1.score)
                {
                    fwrite(&player1, sizeof(player1), 1, file2);
                    fwrite(&player_score, sizeof(player_score), 1, file2);
                    player1.score = 0;
                }
                else
                    fwrite(&player_score, sizeof(player_score), 1, file2);
           
            }
        }
        else
        {
            if (player1.score)
            {
                fwrite(&player1, sizeof(player1), 1, file2);
                player1.score = 0;
            }
        }
        c++;
    }
    fclose(file2);
    fclose(file1);
    remove("scores");
    rename("score1", "scores");

    char buf[25] = {};
    bool quit;
    bool end = false;
    if (!(file1 = fopen("scores", "rb")))
    {
        text_surface = TTF_RenderUTF8_Solid(font, "Error to open a file!", color_fon);
        r.w = text_surface->w;
        r.h = text_surface->h;
        text = SDL_CreateTextureFromSurface(render, text_surface);
        SDL_RenderCopy(render, text, NULL, &r);
        SDL_RenderPresent(render);
        SDL_Delay(2000);
        return;
    }
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 153, 153, 255, 0);
    SDL_Rect rr = { 0, 0, 1280,720 };
    SDL_Rect rr1 = { 20,20, 1240, 680 };
    SDL_RenderFillRect(render, &rr);
    SDL_SetRenderDrawColor(render, 230, 230, 255, 0);
    SDL_RenderFillRect(render, &rr1);
    r.y = 104;
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

    if (file1)
    {
        rewind(file1);
        while (fread(&player_score, sizeof(player_score), 1, file1))
        {
            r.x = 369;
            if (strlen(player_score.Name))
                sprintf(buf, "%s", player_score.Name);
            else sprintf(buf, "%s", "Unknown");
            text_surface = TTF_RenderUTF8_Solid(font, buf, color_fon);
            r.w = text_surface->w;
            r.h = text_surface->h;
            text = SDL_CreateTextureFromSurface(render, text_surface);
            SDL_FreeSurface(text_surface);
            SDL_RenderCopy(render, text, NULL, &r);
            r.x = 839;
          
            sprintf(buf, "%d", player_score.score);
            text_surface = TTF_RenderUTF8_Solid(font, buf, color_fon);
            r.w = text_surface->w;
            r.h = text_surface->h;
            text = SDL_CreateTextureFromSurface(render, text_surface);
            SDL_FreeSurface(text_surface);
            SDL_RenderCopy(render, text, NULL, &r);
            r.y += 50;
            SDL_DestroyTexture(text);
        }
        fclose(file1);

    }
    TTF_CloseFont(font);
    SDL_RenderPresent(render);
    SDL_Delay(3000);
}


bool Game::Init()
{
    SDL_Init(SDL_INIT_VIDEO);


    TTF_Init();
    window = SDL_CreateWindow("Sokoban",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,SDL_WINDOW_SHOWN );
    if (window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return false;
    }
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL) {
        std::cout << "Could not create render: " << SDL_GetError() << '\n';
        return false;
    }

    font = TTF_OpenFont("CharisSILR.ttf",32);
    if (!font) {
        std::cout << "Could not load font : CharisSILR.ttf\n";
        return false;
    }

    LevelInit();

    if (!level.LoadLevel(render,levels[currentlevel],"texture/tilemap.png")) {
        std::cout << "Count not load a level: " << levels[currentlevel] << endl;
        return false;
    }
    if (!player.Init(render, "texture/player.png")) {
        std::cout << " Count not to init a player \n";
        return false;
    }
    player.setPos(level.getplayerPos());

	return true;
}

