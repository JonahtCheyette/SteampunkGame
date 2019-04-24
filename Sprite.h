#pragma once
#include "stdafx.h"

class Sprite {
public:
    void load(std::string path, SDL_Renderer* renderer, int scaleBy = 1);
    void free();

    void loadText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* renderer);
    
    void render(SDL_Renderer* renderer, int x, int y, int cx = 0, int cy = 0, int width = -1, int height = -1, SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
    int getWidth();
    int getHeight();
    
private:
    SDL_Texture* Texture;
		
    int w;
    int h;
};
