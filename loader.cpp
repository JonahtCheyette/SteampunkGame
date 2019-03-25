#include "stdafx.h"

void Loader::loadTiles(std::vector<Object::tileHolder> &t, std::string path, SDL_Renderer* renderer){
    dr = opendir(path.c_str());
    if(dr == NULL){
        std::cout<<"could not open directory"<<std::endl;
    } else {
        while((de = readdir(dr)) != NULL){
            fName = de -> d_name;
            if(fName != "." && fName != ".." && fName != ".DS_Store"){
                std::ifstream data("Steampunk-Game/tData/" + fName);
                while(data >> a >> b >> c >> iPath){
                    Object::tileHolder tile(a, b, c,"Steampunk-Game/Assets/Images/tileTextures/" + iPath + "/", iPath, renderer);
                    t.push_back(tile);
                }
            }
        }
    }
    closedir(dr);
}

void Loader::loadLevels(std::vector<Level> &l, std::string path, SDL_Renderer* renderer, Draw draw){
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
