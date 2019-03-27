#pragma once
#include "stdafx.h"

class backGround;

class Object {
	
	public:
        void textureInit(SDL_Renderer* renderer);
        SDL_Texture* player;
        SDL_Texture* single;
		//camera object
		struct Camera {
			int x, y;
			SDL_Rect camera;

			Camera();
		};

		struct Point {
			float x, y;
            std::string type;
			Point();
            Point(float x, float y, std::string type);
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
            SDL_Texture* texture;
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
            SDL_Texture* topLeft;
            SDL_Texture* top;
            SDL_Texture* topStickOut;
            SDL_Texture* topRight;
            SDL_Texture* right;
            SDL_Texture* rightStickOut;
            SDL_Texture* bottomRight;
            SDL_Texture* bottom;
            SDL_Texture* bottomStickOut;
            SDL_Texture* bottomLeft;
            SDL_Texture* left;
            SDL_Texture* leftStickOut;
            SDL_Texture* center;
            SDL_Texture* single;
            SDL_Texture* wall;
            SDL_Texture* ceiling;
            
            //FOR TILES YOU CAN PASS THROUGH THE BOTTOM OF
            SDL_Texture* passThrough;
            SDL_Texture* passThroughLeft;
            SDL_Texture* passThroughRight;
            SDL_Texture* passThroughBoth;
            
            //FOR CONVEYORS/ TILES THAT MOVE YOU
            SDL_Texture* middle;
            SDL_Texture* end1;
            SDL_Texture* end2;
            
            tileHolder(int kind, int tileNum, float friction, std::string path, std::string Dpath, SDL_Renderer* renderer, bool clockWise = false, bool vertical = false);
        };
    
        struct Layer {
            float scrollrate;
            //I can't think of a name for this
            SDL_Texture* image;
            int w, h;
            Layer(float s, int w, int h, std::string path, SDL_Renderer* renderer);
        };
    
        void moveCamera(Camera &a, int x, int y, int w, int h);
};
