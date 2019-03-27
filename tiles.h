#pragma once
#include "stdafx.h"

class Tiles {
public:
    void mapInit(Level level, std::vector<Object::tileHolder> t);
    void drawTiles(std::vector<Object::Tile> tileGrid, Object::Camera camera, SDL_Renderer* renderer, std::vector<Object::tileHolder> t);
    
    void checkCollision(std::vector<Object::Tile> tileGrid, Player &a);
    Object::Point checkLineCollision(std::vector<Object::Tile> tileGrid, Object::Point a, Object:: Point b);
    
    int intercepts[9];
    float overallOverlap[9];
    
    std::vector<Object::Tile> loadedLevel;
    float colOverlap;
    float xOverlap;
    float yOverlap;
    int correctIndex;

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
   
    bool lineCollided;
    float distance;
    float m;
    float intercept;
    int lEdge;
    int rEdge;
    int tEdge;
    int bEdge;
    int lEdgeLine;
    int rEdgeLine;
    int tEdgeLine;
    int bEdgeLine;
    Object:: Point lineCollision;
    
    bool above;
    bool below;
    bool toTheRight;
    bool toTheLeft;
};
