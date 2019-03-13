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

		struct Player {
			AABB hitbox;
			float x, y;
			float velX, velY;
			float accelX, accelY;
            float mass;

			float maxXSpeed;
            float maxYSpeed;
			float acceleration;
            float friction;
            float distance;
            float pDistance;
            float gX;
            float gY;
            float grappleSpeed;
            int selectedHook;
            
			bool airborne;
            bool grappling;
            int hookState;
            bool changedHook;
            
            Object::Point target;
            Object::Point grappleHead;

			Player();
		};
    
        struct tileHolder {
            int kind;
            float tileNum;
            float friction;
            std::string path;
            
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
            
            tileHolder(int kind, float tileNum, float friction, std::string path, SDL_Renderer* renderer);
        };
    
        struct Layer {
            float scrollrate;
            //I can't think of a name for this
            SDL_Texture* image;
            int w, h;
            Layer(float s, int w, int h, std::string path, SDL_Renderer* renderer);
        };
    
		void drawPlayer(Player a, Camera b, SDL_Renderer* renderer);
};
