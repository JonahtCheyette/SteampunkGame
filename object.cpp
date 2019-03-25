#include "stdafx.h"

Object::Camera::Camera() {
	x = 0;
	y = 0;
	camera = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
}

Object::Point::Point() {
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
    type = "N/A";
}

Object:: Point:: Point(float x, float y, std::string type){
    this -> x = x;
    this -> y = y;
    this -> type = type;
}

void Object::drawPoint(Point a, Camera b, SDL_Renderer* renderer) {
	SDL_Rect destination;
	destination.x = a.x - 8 - b.x;
	destination.y = a.y - 8 - b.y;
	destination.w = 16;
	destination.h = 16;

	SDL_RenderCopy(renderer, player, nullptr, &destination);
}

//FOR DRAWING HOOKS ONLY
void Object::drawHooks(std::vector<Object:: Point> a, Camera b, int selected, SDL_Renderer* renderer) {
    SDL_Rect destination;
    for(int i = 0; i < a.size(); i++){
        if(i == selected){
            destination.x = a[i].x - 16 - b.x;
            destination.y = a[i].y - 16 - b.y;
            destination.w = 32;
            destination.h = 32;
            SDL_RenderCopy(renderer, single, nullptr, &destination);
        }
        destination.x = a[i].x - 8 - b.x;
        destination.y = a[i].y - 8 - b.y;
        destination.w = 16;
        destination.h = 16;
        SDL_RenderCopy(renderer, player, nullptr, &destination);
    }
}

Object::Line::Line() {
	a = nullptr;
	b = nullptr;
}

Object::AABB::AABB() {
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
	width = 0;
	height = 0;
}

Object::Tile::Tile(int x, int y, float f, int kind){
    this -> kind = kind;
    this -> x = x;
    this -> y = y;
    this -> w = TILE_WIDTH;
    this -> h = TILE_HEIGHT;
    this -> f = f;
}

Object::tileHolder::tileHolder(int kind, float tileNum, float friction, std::string path, std::string Dpath, SDL_Renderer* renderer){
    this -> kind = kind;
    this -> tileNum = tileNum;
    this -> path = path;
    this -> Dpath = Dpath;
    this -> friction = friction;
    if(kind == 0){
        topLeft = draw.loadTexture(path + "topLeft.png", renderer);
        top = draw.loadTexture(path + "top.png", renderer);
        topStickOut = draw.loadTexture(path + "topStickOut.png", renderer);
        topRight = draw.loadTexture(path + "topRight.png", renderer);
        right = draw.loadTexture(path + "right.png", renderer);
        rightStickOut = draw.loadTexture(path + "rightStickOut.png", renderer);
        bottomRight = draw.loadTexture(path + "bottomRight.png", renderer);
        bottom = draw.loadTexture(path + "bottom.png", renderer);
        bottomStickOut  = draw.loadTexture(path + "bottomStickOut.png", renderer);
        bottomLeft = draw.loadTexture(path + "bottomLeft.png", renderer);
        left = draw.loadTexture(path + "left.png", renderer);
        leftStickOut  = draw.loadTexture(path + "leftStickOut.png", renderer);
        center = draw.loadTexture(path + "center.png", renderer);
        single = draw.loadTexture(path + "single.png", renderer);
        wall = draw.loadTexture(path + "wall.png", renderer);
        ceiling = draw.loadTexture(path + "ceiling.png", renderer);
    } else {
        passThrough = draw.loadTexture(path + "passThrough.png", renderer);
        passThroughLeft = draw.loadTexture(path + "passThroughLeft.png", renderer);
        passThroughRight = draw.loadTexture(path + "passThroughRight.png", renderer);
        passThroughBoth = draw.loadTexture(path + "passThroughBoth.png", renderer);
    }
}

Object::Layer::Layer(float s, int w, int h, std::string path, SDL_Renderer* renderer){
    this -> scrollrate = s;
    this -> image = draw.loadTexture(path, renderer);
    this -> w = w;
    this -> h = h;
}

void Object:: textureInit(SDL_Renderer* renderer){
    player = draw.loadTexture("Steampunk-Game/Assets/Images/Characters/Square.png", renderer);
    single = draw.loadTexture("Steampunk-Game/Assets/Images/tileTextures/test1/single.png", renderer);
}

void Object:: moveCamera(Camera &a, int x, int y, int w, int h){
    a.x = (x) - SCREEN_WIDTH / 2;
    a.y = (y) - SCREEN_HEIGHT / 2;
    if(a.x + SCREEN_WIDTH > w) a.x = w - SCREEN_WIDTH;
    if (a.x < 0) a.x = 0;
    if(a.y < 0) a.y = 0;
    if(a.y + SCREEN_HEIGHT > h) a.y = h -SCREEN_HEIGHT;
}
