#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}



bool Level::LoadLevel(SDL_Renderer *render ,std::string filepath,std::string tileMapPath)
{
    if (tilemap) {
        SDL_DestroyTexture(tilemap);
    }
    if (map) {
        for (int i = 0; i < w; i++)
            delete map[i];
        delete map;
    }
    finishCount = 0;
    currentfinishCount = 0;
    w = h = 0;
    SDL_Surface* temp = IMG_Load(tileMapPath.c_str());
    tilemap = SDL_CreateTextureFromSurface(render, temp);
    SDL_FreeSurface(temp);
    if (!tilemap) return false;
    std::ifstream file;
    file.open(filepath);
    if(!file) return false;
    file >> w >> h;
    map = new int*[w];
    for (int i = 0; i < w; i++)
        map[i] = new int[h];
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++) {
            file >> map[i][j];
            if (map[i][j] == 1000) {
                playerPos.x = j;
                playerPos.y = i;
                map[i][j] = map[i][j - 1];
            }
            if (map[i][j] == 3) {
                finishCount++;
            }
        }
    file.close();
    return true;
}

void Level::Draw(SDL_Renderer* render,float scale,int startX,int startY)
{
    destRect.w = 128 * scale;
    destRect.h = 128 * scale;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            destRect.x = destRect.w * i+startX;
            destRect.y = destRect.h * j+startY;
            sourceRect.x = 128 * map[i][j];
            SDL_RenderCopy(render, tilemap, &sourceRect, &destRect);
        }
     
    }


}

bool Level::Move(int direction)
{  
    int moveX, moveY;
    switch (direction){
    case 0: moveX = -1; moveY = 0; break;
    case 1: moveX = 0; moveY = -1; break;
    case 2:moveX = 1; moveY = 0;  break;
    case 3: moveX = 0; moveY = 1; break;
    }
    switch (map[playerPos.x + moveX][playerPos.y + moveY]) {
    case 1: case 3: break;
    case 2: 
        if (map[playerPos.x + 2 * moveX][playerPos.y + 2 * moveY] == 1) 
            swap(map[playerPos.x + 2 * moveX][playerPos.y + 2 * moveY],
                map[playerPos.x + moveX][playerPos.y + moveY]);
        else if (map[playerPos.x + 2 * moveX][playerPos.y + 2 * moveY] == 3) {
            map[playerPos.x + 2 * moveX][playerPos.y + 2 * moveY] = 4;
            map[playerPos.x + moveX][playerPos.y + moveY] = 1;
            currentfinishCount++;
        }
        else return 0;
        break;  
    default:return 0; break;
    }
    
    playerPos.x += moveX;
    playerPos.y += moveY;
    return 1;
}
