#include "stdafx.h"

SDL_Texture* Draw::loadTexture(std::string path, SDL_Renderer* renderer) {
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::cout << "Img didn't load at " + path;
    }
	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

void Draw::free() {
	if (Texture != nullptr)
	{
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
		textureWidth = 0;
		textureHeight = 0;
	}
}

void Draw::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip) {
	//set rendering space
	SDL_Rect renderQuad = { x, y, textureWidth, textureHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, Texture, clip, &renderQuad, angle, center, flip);
}
