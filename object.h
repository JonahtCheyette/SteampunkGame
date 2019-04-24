#pragma once
#include "stdafx.h"

class backGround;

class Object {
public:
    void textureInit(SDL_Renderer* renderer);
    Sprite hook;
    Sprite single;
    //camera object
    struct Camera {
        int x, y;
        SDL_Rect camera;
        Camera();
    };

    struct Point {
        float x, y;
        float initX, initY;
        int moveDir;
        float limit1, limit2;
        float moveSpeed;
        bool moving;
        bool vertical;
        std::string type;
        Point();
        Point(float x, float y, std::string type);
        Point(float x, float y, std::string type, float limit1, float limit2, float moveSpeed, bool vertical);
    };
    
    void drawPoint(Point a, Camera b, SDL_Renderer* renderer);
    void drawHooks(std::vector<Object:: Point> a, Camera b, int selected, SDL_Renderer* renderer);
    
    struct Line {
        Point *a, *b;
        
        Line();
    };

    struct AABB {//Axis-Alligned Bounding Box
        int x, y;
        int width, height;
        
        AABB();
    };
    
    struct Tile {
        int kind;
        int x, y;
        int w, h;
        float f;
        bool clockWise;
        bool vertical;
        Sprite texture;
        Tile (int x, int y, float f, int kind);
    };
    
    struct tileHolder {
        int kind;
        int tileNum;
        float friction;
        std::string path;
        std::string Dpath;
        bool clockWise;
        bool vertical;
        
        //RELEASE THE HOUNDS
        //FOR REGULAR TILES
        Sprite topLeft;
        Sprite top;
        Sprite topStickOut;
        Sprite topRight;
        Sprite right;
        Sprite rightStickOut;
        Sprite bottomRight;
        Sprite bottom;
        Sprite bottomStickOut;
        Sprite bottomLeft;
        Sprite left;
        Sprite leftStickOut;
        Sprite center;
        Sprite single;
        Sprite wall;
        Sprite ceiling;
        
        //FOR TILES YOU CAN PASS THROUGH THE BOTTOM OF
        Sprite passThrough;
        Sprite passThroughLeft;
        Sprite passThroughRight;
        Sprite passThroughBoth;
        
        //FOR CONVEYORS/ TILES THAT MOVE YOU
        Sprite middle;
        Sprite end1;
        Sprite end2;
        
        tileHolder(int kind, int tileNum, float friction, std::string path, std::string Dpath, SDL_Renderer* renderer, bool clockWise = false, bool vertical = false);
    };
    
    struct Layer {
        float scrollrate;
        //I can't think of a name for this
        Sprite image;
        int w, h;
        Layer(float s, int w, int h, std::string path, SDL_Renderer* renderer);
    };
    
    struct Animation{
    public:
        Animation(std::string path, SDL_Renderer* renderer);
        Animation();
        void renderAnimation(Animation &a, SDL_Renderer* renderer, int x, int y, int w = 0, int h = 0);
    private:
        //frames per second
        int fps;
        //how many fames are between each new frame pf animation
        int frameGap;
        //how many frames of animation are there
        int frames;
        //empty spaces in the spritesheets to get rid of. ex: a 3*3 spritesheet with only 8 sprites, so this would be set to 1
        int getRidOf;
        //what frame the animation is on
        int currentFrame;
        //width, height of animation;
        int w, h;
        //the clip of the textures
        std::vector<SDL_Rect> clip;
        //current clip to render the image by
        SDL_Rect* currentClip;
        //the spritesheet to animate off of
        Sprite animation;
    };
    
    void moveCamera(Camera &a, int x, int y, int w, int h);
};
