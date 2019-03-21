#include "stdafx.h"

void backGround::backgroundInit(std::string path, SDL_Renderer* renderer){
    std::ifstream data(path);
    while(data >> iPath >> s >> w >> h){
        Object::Layer la(s, w, h, "Steampunk-Game/Assets/Images/backgrounds/" + iPath, renderer);
        l.push_back(la);
    }
    data.close();
}

void backGround::drawBackground(SDL_Renderer* renderer, Object::Camera c){
    for(int i = 0; i < l.size(); i++){
        int amount = 0;
        SDL_Rect destination;
        destination.w = l[i].w;
        destination.h = l[i].h;
        destination.x = (l[i].scrollrate * c.x) - c.x;
        destination.y = (l[i].scrollrate * c.y) - c.y;
        while(destination.x < -1 * destination.w){
            destination.x += destination.w;
        }
        if(destination.w < SCREEN_WIDTH){
            amount = ceil(SCREEN_WIDTH / destination.w) + 1;
        } else {
            amount = 2;
        }
        for(int j = 0 ; j <= amount; j++){
            SDL_RenderCopy(renderer, l[i].image, nullptr, &destination);
            destination.x += destination.w;
        }
    }
}
