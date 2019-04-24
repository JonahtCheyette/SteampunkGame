#pragma once
#include "stdafx.h"

class Tiles {
public:
    void mapInit(std::vector< std::vector <int> > tileGrid, std::vector<Object::tileHolder> t);
    void drawTiles(std::vector<Object::Tile> tileGrid, Object::Camera camera, SDL_Renderer* renderer, std::vector<Object::tileHolder> t);
    void checkCollision(std::vector<Object::Tile> tileGrid, physicsApplied &a);
    Object::Point checkLineCollision(std::vector<Object::Tile> tileGrid, Object::Point a, Object:: Point b);
    std::vector<Object::Tile> loadedLevel;

private:
    int intercepts[9];
    float overallOverlap[9];
    float colOverlap;
    float xOverlap;
    float yOverlap;
    int correctIndex;
   
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
