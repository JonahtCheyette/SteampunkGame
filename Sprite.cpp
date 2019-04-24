#include "stdafx.h"

void Sprite::load(std::string path, SDL_Renderer* renderer, int scaleBy) {
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::cout << "Img didn't load at " + path << std::endl;
    }
    w = loadedSurface -> w;
    h = loadedSurface -> h;
    
    w *= scaleBy;
    h *= scaleBy;
    
    //Create texture from surface pixels
    Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    
    if(Texture == NULL) {
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }
    
    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
}

void Sprite::free() {
	if (Texture != nullptr) {
		SDL_DestroyTexture(Texture);
		Texture = nullptr;
		w = 0;
		h = 0;
	}
}

void Sprite::loadText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* renderer){
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if(textSurface == NULL) {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    //Create texture from surface pixels
    Texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if(Texture == NULL) {
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }
    
    w = textSurface -> w;
    h = textSurface -> h;
    
    //Get rid of old surface
    SDL_FreeSurface( textSurface );
}

void Sprite::render(SDL_Renderer* renderer, int x, int y, int cx, int cy, int width, int height, SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip) {
	//set rendering space
    SDL_Rect renderQuad;
    if(width == -1 && height == -1){
        renderQuad = {x - cx - (w/2), y - cy - (h/2), w, h};
    } else {
        renderQuad = {x - cx - (width/2), y - cy - (height/2), width, height};
    }
    
	//Render to screen
	SDL_RenderCopyEx(renderer, Texture, clip, &renderQuad, angle, center, flip);
}

int Sprite::getWidth(){
    return w;
}

int Sprite::getHeight(){
    return h;
}
