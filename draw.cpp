#include "stdafx.h"

SDL_Texture* Draw::loadTexture(std::string path, SDL_Renderer* renderer) {
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        std::cout << "Img didn't load at " + path << std::endl;
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

SDL_Texture* Draw::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, int &w, int &h, SDL_Renderer* renderer){
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    //Create texture from surface pixels
    SDL_Texture* mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( mTexture == NULL )
    {
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }
    
    w = textSurface -> w;
    h = textSurface -> h;
    
    //Get rid of old surface
    SDL_FreeSurface( textSurface );
    
    //Return success
    return mTexture;
}

void Draw::render(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip) {
	//set rendering space
	SDL_Rect renderQuad = {x, y, w, h};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, Texture, clip, &renderQuad, angle, center, flip);
}
