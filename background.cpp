#include "stdafx.h"

void backGround::backgroundInit(std::string path, SDL_Renderer* renderer){
    std::ifstream data(path);
    while(data >> iPath >> s >> w >> h){
        Object::Layer la(s, w, h, "Steampunk-Game/Assets/Images/backgrounds/" + iPath, renderer);
        l.push_back(la);
    }
}

void backGround::drawBackground(SDL_Renderer* renderer, Object::Camera c, int height){
    for(int i = 0; i < l.size(); i++){
        SDL_Rect destination;
        destination.w = l[i].w;
        destination.h = l[i].h;
        destination.x = -1 * l[i].scrollrate * c.x;
        destination.y = (-1 * l[i].scrollrate * c.y) + (height - SCREEN_HEIGHT);
        while(destination.x < -1 * destination.w){
            destination.x += destination.w;
        }
        int amount = ceil(SCREEN_WIDTH / destination.w) + 1;
        for(int j = 0 ; j <= amount; j++){
            SDL_RenderCopy(renderer, l[i].image, nullptr, &destination);
            destination.x += destination.w;
        }
    }
}
