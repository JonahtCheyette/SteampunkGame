#pragma once
#include "stdafx.h"

class developer {
public:
    void moveCamera(Object::Camera &camera, Event event);
    void showEditing(Draw draw, std::string type, SDL_Color color, TTF_Font* font, std::vector<Object::tileHolder> tileVector, SDL_Renderer* renderer);
    void editLevel(Object::Camera camera, std::vector<Object::tileHolder> tileVector, Level level, SDL_Renderer* renderer, Event event, std::vector<Object::Tile> &tileGrid);
    void editAssets(Object::Camera c,Event e, Level &l, SDL_Renderer* renderer, SDL_Color color, TTF_Font* font);
    void createSwitch(Event e, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
    void typeSwitch(Event e, std::string &type, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer, Draw draw);
    void switchTile(Event e, std::vector<Object::tileHolder> tileVector, std::string type, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
    void changeHookMoveSpeed(Event e, std::vector<Object::Point> &hooks, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer, std::string path);
    void init(Draw draw, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);
    void renderDRect(SDL_Renderer* renderer, std::string type, Event e, Level l, Object::Camera c);
    
    //rect for the tile editing rectangle
    SDL_Rect heldRect;
    //to hold the rects size and position for actually editing the file
    int x, y;
    int w, h;
    //safety feature to make sure everything that involves the steps of click, hold release works as planned
    int clickstate;
    bool held;
    //bools to make key presses activate on press, not eveyframe they are held down
    bool clicked1,clicked2,clicked3,clicked4, clicked5, clicked6;
    //camera move speed
    int moveSpeed;
    //what kind of ile is being put down by index in tileVector
    int whichTile;
    //for writing what mode you're in to the topleft corner
    SDL_Texture* typeTexture;
    SDL_Texture* createTexture;
    SDL_Texture* whichTexture;
    //for writing what a hook's movement speed is
    SDL_Texture* moveSpeedTexture;
    //ints to hold how large the above textures are so nothing gets awkwardly compressed
    int typeW, typeH;
    int createW, createH;
    int whichW, whichH;
    int msW, msH;
    //for rendering the above textures
    SDL_Rect destination;
    //creation or destruction
    bool create;
    //whether or not editing (0, 2, 3)hooks or (1) spawn/endpoints
    int whichAsset;
    //either editing spawn or level finish points (see editAssets funtion)
    bool spawn;
    //what hook you are targeting
    int whichHook;
    //whether yur editig limit1 or 2 of the hook
    int whichLimit;
};
