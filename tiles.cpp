#include "stdafx.h"

void Tiles::mapInit(Level level, std::vector<Object::tileHolder> t) {
    for(int i = 0; i < t.size(); i++){
        if(t[i].tileNum > 0){
            for (int y = 0; y < level.tileGrid.size(); y++){
                for(int x = 0; x < level.tileGrid[y].size(); x++){
                    if(level.tileGrid[y][x] == t[i].tileNum){
                        Object::Tile tile(x * TILE_WIDTH, y * TILE_HEIGHT, t[i].friction);
                        above = false;
                        below = false;
                        toTheRight = false;
                        toTheLeft = false;
                        if(y == 0){
                            above = true;
                        } else {
                            if(level.tileGrid[y - 1][x] < t[i].tileNum + 1 && level.tileGrid[y - 1][x] >= t[i].tileNum){
                                above = true;
                            }
                        }
                        if(y == level.tileGrid.size() - 1){
                            below = true;
                        } else {
                            if(level.tileGrid[y + 1][x] < t[i].tileNum + 1 && level.tileGrid[y + 1][x] >= t[i].tileNum){
                                below = true;
                            }
                        }
                        if(x == 0){
                            toTheLeft = true;
                        } else {
                            if(level.tileGrid[y][x - 1] < t[i].tileNum + 1 && level.tileGrid[y][x - 1] >= t[i].tileNum){
                                toTheLeft = true;
                            }
                        }
                        if(x == level.tileGrid[0].size() - 1){
                            toTheRight = true;
                        } else {
                            if(level.tileGrid[y][x + 1] < t[i].tileNum + 1 && level.tileGrid[y][x + 1] >= t[i].tileNum){
                                toTheRight = true;
                            }
                        }
                        if(above){
                            if(below){
                                if(toTheRight){
                                    if(toTheLeft){
                                        //center
                                        tile.texture = t[i].center;
                                    } else {
                                        //left
                                        tile.texture = t[i].left;
                                    }
                                } else {
                                    if(toTheLeft){
                                        //right
                                        tile.texture = t[i].right;
                                    } else {
                                        //wall
                                        tile.texture = t[i].wall;
                                    }
                                }
                            } else {
                                if(toTheRight){
                                    if(toTheLeft){
                                        //bottom
                                        tile.texture = t[i].bottom;
                                    } else {
                                        //bottomleft
                                        tile.texture = t[i].bottomLeft;
                                    }
                                } else {
                                    if(toTheLeft){
                                        //bottomright
                                        tile.texture = t[i].bottomRight;
                                    } else {
                                        //bottomstickout
                                        tile.texture = t[i].bottomStickOut;
                                    }
                                }
                            }
                        } else if (below) {
                            if(toTheRight){
                                if(toTheLeft){
                                    //top
                                    tile.texture = t[i].top;
                                } else {
                                    //topleft
                                    tile.texture = t[i].topLeft;
                                }
                            } else {
                                if(toTheLeft){
                                    //topright
                                    tile.texture = t[i].topRight;
                                } else {
                                    //topstickout
                                    tile.texture = t[i].topStickOut;
                                }
                            }
                        } else if (toTheLeft) {
                            if(toTheRight){
                                //ceiling
                                tile.texture = t[i].ceiling;
                            } else {
                                //rightstickout
                                tile.texture = t[i].rightStickOut;
                            }
                        } else if (toTheRight){
                            //leftstickout
                            tile.texture = t[i].leftStickOut;
                        } else {
                            //single
                            tile.texture = t[i].single;
                        }
                        loadedLevel.push_back(tile);
                    }
                }
            }
        }
    }
}

void Tiles::drawTiles(std::vector<Object::Tile> tileGrid, Object::Camera camera, SDL_Renderer* renderer, std::vector<Object::tileHolder> t) {
	SDL_Rect destination;
	destination.w = TILE_WIDTH;
	destination.h = TILE_HEIGHT;
	for (int i = 0; i < tileGrid.size(); i++) {
        if (tileGrid[i].y + tileGrid[i].h > camera.y && tileGrid[i].y < camera.y + SCREEN_HEIGHT && tileGrid[i].x + tileGrid[i].w > camera.x && tileGrid[i].x < camera.x + SCREEN_WIDTH){
            SDL_Rect destination;
            destination.x = tileGrid[i].x - camera.x;
            destination.y = tileGrid[i].y - camera.y;
            destination.w = tileGrid[i].w;
            destination.h = tileGrid[i].h;
            SDL_RenderCopy(renderer, tileGrid[i].texture, nullptr, &destination);
        }
	}
}

void Tiles::checkCollision(std::vector<Object::Tile> tileGrid, Object::Player &a, std::vector<Object::tileHolder> t) {
    colOverlap = 0;
    xOverlap = 0;
    yOverlap = 0;
    correctIndex = 0;
    for(int i = 0; i < 9; i++){
        overallOverlap[i] = 0;
        intercepts[i] = 0;
    }
    
    for (int i = 0; i < tileGrid.size(); i++) {
        lEdge = tileGrid[i].x;
        rEdge = lEdge + tileGrid[i].w;
        tEdge = tileGrid[i].y;
        bEdge = tEdge + tileGrid[i].h;
        if (a.x + a.hitbox.width / 2 > lEdge && a.x - a.hitbox.width / 2 < rEdge && a.y + a.hitbox.height / 2 > tEdge && a.y - a.hitbox.height / 2 < bEdge) {
            if(a.x + a.hitbox.width / 2 <= rEdge){
                xOverlap = (a.x + a.hitbox.width / 2) - lEdge;
            } else {
                xOverlap = (a.x - a.hitbox.width / 2) - rEdge;
            }
            if(a.y + a.hitbox.height / 2 <= bEdge){
                yOverlap = (a.y + a.hitbox.height/2) - tEdge;
            } else {
                yOverlap = (a.y - a.hitbox.height / 2) - bEdge;
            }
            if(abs(yOverlap) > TILE_HEIGHT){
                yOverlap = TILE_HEIGHT;
            }
            if(abs(xOverlap) > TILE_WIDTH){
                xOverlap = TILE_WIDTH;
            }
            //multiply xoverlap and y overlap, then absolute value function it
            colOverlap = abs(xOverlap * yOverlap);
            if(colOverlap > 0){
                for(int j = 0; j < 9; j++){
                    if(colOverlap > overallOverlap[j]){
                        correctIndex = j;
                        break;
                    }
                }
                for(int j = 8; j >= correctIndex; j--){
                    if(j > correctIndex){
                        overallOverlap[j] = overallOverlap[j-1];
                        intercepts[j] = intercepts[j - 1];
                    } else if (j == correctIndex) {
                        overallOverlap[j] = colOverlap;
                        intercepts[j] = i;
                    }
                }
            }
        }
    }
    for(int i = 0; i < 9; i ++){
        if(overallOverlap[i] > 0){
            lEdge = tileGrid[intercepts[i]].x;
            rEdge = lEdge + tileGrid[intercepts[i]].w;
            tEdge = tileGrid[intercepts[i]].y;
            bEdge = tEdge + tileGrid[intercepts[i]].h;
            if (a.x + a.hitbox.width / 2 > lEdge && a.x - a.hitbox.width / 2 < rEdge && a.y +  a.hitbox.height / 2 > tEdge && a.y - a.hitbox.height / 2 < bEdge) {
                a.friction = tileGrid[intercepts[i]].f;
                if ((a.y + a.hitbox.height / 2) <= (tEdge + a.velY)) {
                    a.y = tEdge - a.hitbox.height / 2;
                    if(a.velY >= 0){
                        a.velY = 0;
                        a.airborne = false;
                    }
                } else if ((a.y - a.hitbox.height / 2) >= (bEdge + a.velY)){
                    a.y = bEdge + a.hitbox.height / 2;
                    a.velY = 0;
                } else if ((a.x - a.hitbox.width / 2) >= (rEdge + a.velX - 0.01)){
                    a.x = rEdge + a.hitbox.width / 2;
                    a.velX = 0;
                } else {
                    a.x = lEdge - a.hitbox.width / 2;
                    a.velX = 0;
                }
            }
        }
    }
}

//for the grapple collisions
Object::Point Tiles::checkLineCollision(std::vector<Object::Tile> tileGrid, Object:: Point a, Object:: Point b) {
    //slope and intercept
    m = (a.y - b.y)/(a.x - b.x);
    intercept = a.y - (m * a.x);
    distance = 100000;
    lineCollided = false;
    for(int i = 0; i < tileGrid.size(); i++){
        //edges and where the line x/y will be at when given those edges
        //y = mx + b
        //x = y - b /m
        lEdge = tileGrid[i].x;
        rEdge = lEdge + tileGrid[i].w;
        tEdge = tileGrid[i].y;
        bEdge = tEdge + tileGrid[i].h;
        if(a.x < b.x){
            if(rEdge < a.x){
                continue;
            }
            if(lEdge > b.x){
                continue;
            }
        } else {
            if(rEdge < b.x){
                continue;
            }
            if(lEdge > a.x){
                continue;
            }
        }
        if(a.y < b.y){
            if(tEdge < a.y){
                continue;
            }
            if(bEdge > b.y){
                continue;
            }
        } else {
            if(tEdge < b.y){
                continue;
            }
            if(bEdge > a.y){
                continue;
            }
        }
        lEdgeLine = (lEdge * m) + intercept;
        rEdgeLine = (rEdge * m) + intercept;
        tEdgeLine = (tEdge - intercept) / m;
        bEdgeLine = (bEdge - intercept) / m;
        if(lEdgeLine <= bEdge && lEdgeLine >= tEdge){
            lineCollided = true;
            if(distance > sqrt(pow(a.x - lEdge,2) + pow(a.y - lEdgeLine, 2))){
                lineCollision.y = lEdgeLine;
                lineCollision.x = lEdge;
                distance = sqrt(pow(a.x - lineCollision.x,2) + pow(a.y - lineCollision.y, 2));
            }
        }
        if(rEdgeLine <= bEdge && rEdgeLine >= tEdge){
            lineCollided = true;
            if(distance > sqrt(pow(a.x - rEdge,2) + pow(a.y - rEdgeLine, 2))){
                lineCollision.y = rEdgeLine;
                lineCollision.x = rEdge;
                distance = sqrt(pow(a.x - lineCollision.x,2) + pow(a.y - lineCollision.y, 2));
            }
        }
        if(tEdgeLine <= rEdge && tEdgeLine >= lEdge){
            lineCollided = true;
            if(distance > sqrt(pow(a.y - tEdge,2) + pow(a.x - tEdgeLine, 2))){
                lineCollision.y = tEdge;
                lineCollision.x = tEdgeLine;
                distance = sqrt(pow(a.x - lineCollision.x,2) + pow(a.y - lineCollision.y, 2));
            }
        }
        if(bEdgeLine <= rEdge && bEdgeLine >= lEdge){
            lineCollided = true;
            if(distance > sqrt(pow(a.y - bEdge,2) + pow(a.x - bEdgeLine, 2))){
                lineCollision.y = bEdge;
                lineCollision.x = bEdgeLine;
                distance = sqrt(pow(a.x - lineCollision.x,2) + pow(a.y - lineCollision.y,2));
            }
        }
    }
    if(lineCollided){
        return lineCollision;
    }
    lineCollided = false;
    return b;
}
