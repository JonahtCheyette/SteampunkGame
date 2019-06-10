#pragma once
#include "stdafx.h"

class Tiles {
public:
    static void mapInit(std::vector< std::vector <int> > tileGrid, std::vector<Object::tileHolder> t);
    static void drawTiles(std::vector<Object::Tile> tileGrid, Object::Camera camera, SDL_Renderer* renderer, std::vector<Object::tileHolder> t);
    static void checkCollision(std::vector<Object::Tile> tileGrid, physicsApplied &a);
    static Vector checkLineCollision(std::vector<Object::Tile> tileGrid, Vector a, Object:: Point b);
    static std::vector<Object::Tile> getLoadedLevel();
    static bool getLineCollided();
    //for developermode because returning a raference gave me more errors
    static void spliceFromLoadedLevel(int index);
    static void addToLoadedLevel(Object::Tile t);

private:
    static std::vector<Object::Tile> loadedLevel;
    static int intercepts[9];
    static float overallOverlap[9];
    static float colOverlap;
    static float xOverlap;
    static float yOverlap;
    static int correctIndex;
   
    static bool lineCollided;
    static float distance;
    static float m;
    static float intercept;
    static int lEdge;
    static int rEdge;
    static int tEdge;
    static int bEdge;
    static int lEdgeLine;
    static int rEdgeLine;
    static int tEdgeLine;
    static int bEdgeLine;
    static Vector lineCollision;
    
    static bool above;
    static bool below;
    static bool toTheRight;
    static bool toTheLeft;
};
