#include "stdafx.h"

Object::Camera::Camera(){
    x = 0;
    y = 0;
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

Object::Point::Point() {
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
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
    hook.render(renderer, a.x, a.y, b.x, b.y);
}

//FOR DRAWING HOOKS ONLY
void Object::drawHooks(std::vector<Object:: Point> a, Camera b, int selected, SDL_Renderer* renderer) {
    for(int i = 0; i < a.size(); i++){
        if(i == selected){
            single.render(renderer, a[i].x, a[i].y, b.x, b.y, 32, 32);
        }
        hook.render(renderer, a[i].x, a[i].y, b.x, b.y);
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
        topLeft.load(path + "topLeft.png", renderer);
        top.load(path + "top.png", renderer);
        topStickOut.load(path + "topStickOut.png", renderer);
        topRight.load(path + "topRight.png", renderer);
        right.load(path + "right.png", renderer);
        rightStickOut.load(path + "rightStickOut.png", renderer);
        bottomRight.load(path + "bottomRight.png", renderer);
        bottom.load(path + "bottom.png", renderer);
        bottomStickOut.load(path + "bottomStickOut.png", renderer);
        bottomLeft.load(path + "bottomLeft.png", renderer);
        left.load(path + "left.png", renderer);
        leftStickOut.load(path + "leftStickOut.png", renderer);
        center.load(path + "center.png", renderer);
        single.load(path + "single.png", renderer);
        wall.load(path + "wall.png", renderer);
        ceiling.load(path + "ceiling.png", renderer);
    } else if(kind == 1){
        passThrough.load(path + "passThrough.png", renderer);
        passThroughLeft.load(path + "passThroughLeft.png", renderer);
        passThroughRight.load(path + "passThroughRight.png", renderer);
        passThroughBoth.load(path + "passThroughBoth.png", renderer);
    } else {
        middle.load(path + "middle.png", renderer);
        end1.load(path + "end1.png", renderer);
        end2.load(path + "end2.png", renderer);
    }
}

Object::Layer::Layer(float s, int w, int h, std::string path, SDL_Renderer* renderer){
    this -> scrollrate = s;
    this -> image.load(path, renderer);
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
    animation.load(path + ".png", renderer);
    SDL_Rect clipper;
    for(int i = 0; i < floor(animation.getHeight()/h); i++){
        for(int j = 0; j < floor(animation.getWidth()/w); j++){
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
    hook.load("Steampunk-Game/Assets/Images/levelBasics/HookPlaceholder.png", renderer, 1);
    single.load("Steampunk-Game/Assets/Images/tileTextures/girders/single.png", renderer, 1);
}

void Object::Camera:: move(int x, int y, int w, int h){
    this -> x = (x) - SCREEN_WIDTH / 2;
    this -> y = (y) - SCREEN_HEIGHT / 2;
    if(x + SCREEN_WIDTH > w) x = w - SCREEN_WIDTH;
    if (x < 0) x = 0;
    if(y + SCREEN_HEIGHT > h) y = h - SCREEN_HEIGHT;
    if(y < 0) y = 0;
}

void Object::Animation::renderAnimation(Animation &a, SDL_Renderer* renderer, int x, int y, int w, int h){
    a.currentClip = &a.clip[a.currentFrame / a.frameGap];
    if(w == 0 || h == 0){
        a.animation.render(renderer, x + (a.animation.getWidth() / 2), y + (a.animation.getHeight() / 2), 0, 0, a.animation.getWidth(), a.animation.getHeight(), a.currentClip);
    } else {
        a.animation.render(renderer, x + (w/2), y + (h/2), 0, 0, w, h, a.currentClip);
    }
    a.currentFrame++;
    if(a.currentFrame / a.frameGap >= a.clip.size()){
        a.currentFrame = 0;
    }
}
