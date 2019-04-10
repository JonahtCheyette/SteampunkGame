#include "stdafx.h"

void Loader::loadTiles(std::vector<Object::tileHolder> &t, std::string path, SDL_Renderer* renderer){
    std::ifstream rFile(path + "regular.txt");
    while(rFile >> tileNum >> a >> iPath){
        Object::tileHolder tile(0, tileNum, a, "Steampunk-Game/Assets/Images/tileTextures/" + iPath + "/", iPath, renderer);
        t.push_back(tile);
    }
    rFile.close();
    std::ifstream pFile(path + "passThrough.txt");
    while(pFile >> tileNum >> a >> iPath){
        Object::tileHolder tile(1, tileNum, a, "Steampunk-Game/Assets/Images/tileTextures/" + iPath + "/", iPath, renderer);
        t.push_back(tile);
    }
    pFile.close();
    std::ifstream mFile(path + "moveStuff.txt");
    while(mFile >> tileNum >> a >> iPath >> bo >> bi){
        Object::tileHolder tile(2, tileNum, a, "Steampunk-Game/Assets/Images/tileTextures/" + iPath + "/", iPath, renderer, bo, bi);
        t.push_back(tile);
    }
    mFile.close();
}

void Loader::loadLevels(std::vector<Level> &l, std::string path, SDL_Renderer* renderer){
    dr = opendir(path.c_str());
    if(dr == NULL){
        std::cout<<"could not open directory"<<std::endl;
    } else {
        while((de = readdir(dr)) != NULL){
            fName = de -> d_name;
            if(fName != "." && fName != ".." && fName != ".DS_Store"){
                l.push_back(Level::levelInit(path + "/" + fName + "/", renderer, draw));
            }
        }
    }
}
