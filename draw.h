#pragma once
#include "stdafx.h"

class Draw {
	public:
		SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
		void free();

		void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	private:
		SDL_Texture* Texture;
		
		int textureWidth;
		int textureHeight;
};