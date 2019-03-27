#pragma once
#include "stdafx.h"

class Draw {
public:
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    void free();

    SDL_Texture* loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, int &w, int &h, SDL_Renderer* renderer);
    
    void render(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
private:
    SDL_Texture* Texture;
		
    int textureWidth;
    int textureHeight;
};
