#include "stdafx.h"

void backGround::backgroundInit(std::string path, SDL_Renderer* renderer){
    std::ifstream data(path);
    while(data >> iPath >> s >> w >> h){
        Object::Layer la(s, w, h, "Steampunk-Game/Assets/Images/backgrounds/" + iPath, renderer);
        l.push_back(la);
    }
    data.close();
}

void backGround::drawBackground(SDL_Renderer* renderer, Object::Camera c, int h){
    for(int i = 0; i < l.size(); i++){
        destination.w = l[i].w;
        destination.h = l[i].h;
        destination.x = (l[i].scrollrate * c.x) - c.x;
        destination.y = (l[i].scrollrate * c.y) - c.y + h;
        while(destination.x < -destination.w){
            destination.x += destination.w;
        }
        start = destination.x;
        if(destination.w < SCREEN_WIDTH){
            xAmount = ceil(SCREEN_WIDTH / destination.w) + 2;
        } else {
            xAmount = 2;
        }
        if(destination.x > -1 * (SCREEN_WIDTH - floor(SCREEN_WIDTH / destination.w) * destination.w)){
            xAmount --;
        }
        if(destination.h < SCREEN_HEIGHT){
            yAmount = ceil(SCREEN_HEIGHT / destination.h) + 2;
        } else {
            yAmount = 2;
        }
        if(destination.y > -1 * (SCREEN_HEIGHT - floor(SCREEN_HEIGHT / destination.h) * destination.h)){
            yAmount --;
        }
        for(int j = 0 ; j <= yAmount; j++){
            for(int k = 0 ; k <= xAmount; k++){
                l[i].image.render(renderer, destination.x + destination.w / 2, destination.y + destination.h / 2, 0, 0, destination.w, destination.h);
                destination.x += destination.w;
            }
            destination.x = start;
            destination.y += destination.h;
        }
    }
}
