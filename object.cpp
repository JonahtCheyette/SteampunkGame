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
    this -> initX = x;
    this -> initY = y;
    this -> type = type;
    this -> moveDir = 1;
    moving = false;
}

Object:: Point:: Point(float x, float y, std::string type, float limit1, float limit2, float moveSpeed, bool vertical){
    this -> x = x;
    this -> y = y;
    this -> initX = x;
    this -> initY = y;
    this -> type = type;
    this -> limit1 = limit1;
    this -> limit2 = limit2;
    this -> moveSpeed = moveSpeed;
    this -> vertical = vertical;
    this -> moveDir = 1;
    moving = true;
}

void Object::drawPoint(Point a, Camera b, SDL_Renderer* renderer) {
	SDL_Rect destination;
	destination.x = a.x - 8 - b.x;
	destination.y = a.y - 8 - b.y;
	destination.w = 16;
	destination.h = 16;

	SDL_RenderCopy(renderer, hook, nullptr, &destination);
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
        SDL_RenderCopy(renderer, hook, nullptr, &destination);
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

Object::tileHolder::tileHolder(int kind, int tileNum, float friction, std::string path, std::string Dpath, SDL_Renderer* renderer, bool clockWise, bool vertical){
    this -> kind = kind;
    this -> tileNum = tileNum;
    this -> path = path;
    this -> Dpath = Dpath;
    this -> friction = friction;
    this -> clockWise = clockWise;
    this -> vertical = vertical;
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
    } else if(kind == 1){
        passThrough = draw.loadTexture(path + "passThrough.png", renderer);
        passThroughLeft = draw.loadTexture(path + "passThroughLeft.png", renderer);
        passThroughRight = draw.loadTexture(path + "passThroughRight.png", renderer);
        passThroughBoth = draw.loadTexture(path + "passThroughBoth.png", renderer);
    } else {
        middle = draw.loadTexture(path + "middle.png", renderer);
        end1 = draw.loadTexture(path + "end1.png", renderer);
        end2 = draw.loadTexture(path + "end2.png", renderer);
    }
}

Object::Layer::Layer(float s, int w, int h, std::string path, SDL_Renderer* renderer){
    this -> scrollrate = s;
    this -> image = draw.loadTexture(path, renderer);
    this -> w = w;
    this -> h = h;
}

Object::Animation::Animation(){}

Object::Animation::Animation(std::string path, SDL_Renderer* renderer){
    std::ifstream aFile(path + ".txt");
    aFile >> fps >> w >> h >> getRidOf;
    aFile.close();
    frameGap = floor(60/fps);
    currentFrame = 0;
    animation = draw.loadTextureWH(path + ".png", renderer, sW, sH);
    SDL_Rect clipper;
    for(int i = 0; i < floor(sH/h); i++){
        for(int j = 0; j < floor(sW/w); j++){
            clipper.x = j * w;
            clipper.y = i * h;
            clipper.w = w;
            clipper.h = h;
            clip.push_back(clipper);
        }
    }
    for(int i = 0; i < getRidOf; i++){
        clip.pop_back();
    }
}

void Object:: textureInit(SDL_Renderer* renderer){
    hook = draw.loadTexture("Steampunk-Game/Assets/Images/levelBasics/HookPlaceholder.png", renderer);
    single = draw.loadTexture("Steampunk-Game/Assets/Images/tileTextures/girders/single.png", renderer);
}

void Object:: moveCamera(Camera &a, int x, int y, int w, int h){
    a.x = (x) - SCREEN_WIDTH / 2;
    a.y = (y) - SCREEN_HEIGHT / 2;
    if(a.x + SCREEN_WIDTH > w) a.x = w - SCREEN_WIDTH;
    if (a.x < 0) a.x = 0;
    if(a.y + SCREEN_HEIGHT > h) a.y = h - SCREEN_HEIGHT;
    if(a.y < 0) a.y = 0;
}

void Object::renderAnimation(Animation &a, SDL_Renderer* renderer, int x, int y, int w, int h){
    a.currentClip = &a.clip[a.currentFrame / a.frameGap];
    if(w == 0 || h == 0){
        draw.render(a.animation, renderer, x, y, a.w, a.h, a.currentClip);
    } else {
        draw.render(a.animation, renderer, x, y, w, h, a.currentClip);
    }
    a.currentFrame++;
    if(a.currentFrame / a.frameGap >= a.clip.size()){
        a.currentFrame = 0;
    }
}

Object::Animation Object::animationInit(std::string path, SDL_Renderer *renderer){
    Animation a(path, renderer);
    return a;
}
