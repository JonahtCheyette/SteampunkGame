#pragma once
#include "stdafx.h"

class Tiles {
public:
    void mapInit(Level level, std::vector<Object::tileHolder> t);
	void drawTiles(std::vector<std::vector<float>> tileGrid, Object::Camera camera, SDL_Renderer* renderer, std::vector<Object::tileHolder> t);

    void sortTiles(std::vector<std::vector<float>> &tileGrid, float tileNum);
    void showCorrectTiles(float n, SDL_Rect destination, SDL_Renderer* renderer, std::vector<Object::tileHolder> t);
    
    void checkCollision(std::vector<std::vector<float>> tileGrid, Object::Player &a, std::vector<Object::tileHolder> t);
    Object::Point checkLineCollision(std::vector<std::vector<float>> tileGrid, Object::Point a, Object:: Point b);
    
    int interceptsX[9];
    int interceptsY[9];
    float overallOverlap[9];
    
    std::vector<std::vector<float>> loadedLevel;
    float xPushed;
    float yPushed;

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
