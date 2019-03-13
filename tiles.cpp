#include "stdafx.h"

void Tiles::sortTiles(std::vector<std::vector<float>> &tileGrid, float tileNum){
    if(tileNum > 0){
        for (int y = 0; y < tileGrid.size(); y++){
            for(int x = 0; x < tileGrid[0].size(); x++){
                if(tileGrid[x][y] == tileNum){
                    above = false;
                    below = false;
                    toTheRight = false;
                    toTheLeft = false;
                    if(x == 0){
                        toTheLeft = true;
                    } else {
                        if(tileGrid[x - 1][y] < tileNum + 1 && tileGrid[x - 1][y] >= tileNum){
                            toTheLeft = true;
                        }
                    }
                    if(x == tileGrid.size() - 1){
                        toTheRight = true;
                    } else {
                        if(tileGrid[x + 1][y] < tileNum + 1 && tileGrid[x + 1][y] >= tileNum){
                            toTheRight = true;
                        }
                    }
                    if(y == 0){
                        above = true;
                    } else {
                        if(tileGrid[x][y - 1] < tileNum + 1 && tileGrid[x][y - 1] >= tileNum){
                            above = true;
                        }
                    }
                    if(y == tileGrid[0].size() - 1){
                        below = true;
                    } else {
                        if(tileGrid[x][y + 1] < tileNum + 1 && tileGrid[x][y + 1] >= tileNum){
                            below = true;
                        }
                    }
                    if(above){
                        if(below){
                            if(toTheRight){
                                if(toTheLeft){
                                    //center
                                    tileGrid[x][y] += 0.9;
                                } else {
                                    //left
                                    tileGrid[x][y] += 0.8;
                                }
                            } else {
                                if(toTheLeft){
                                    //right
                                    tileGrid[x][y] += 0.4;
                                } else {
                                    //wall
                                    tileGrid[x][y] += 0.12;
                                }
                            }
                        } else {
                            if(toTheRight){
                                if(toTheLeft){
                                    //bottom
                                    tileGrid[x][y] += 0.6;
                                } else {
                                    //bottomleft
                                    tileGrid[x][y] += 0.7;
                                }
                            } else {
                                if(toTheLeft){
                                    //bottomright
                                    tileGrid[x][y] += 0.5;
                                } else {
                                    //bottomstickout
                                    tileGrid[x][y] += 0.16;
                                }
                            }
                        }
                    } else if (below) {
                        if(toTheRight){
                            if(toTheLeft){
                                //top
                                tileGrid[x][y] += 0.2;
                            } else {
                                //topleft
                                tileGrid[x][y] += 0.1;
                            }
                        } else {
                            if(toTheLeft){
                                //topright
                                tileGrid[x][y] += 0.3;
                            } else {
                                //topstickout
                                tileGrid[x][y] += 0.14;
                            }
                        }
                    } else if (toTheLeft) {
                        if(toTheRight){
                            //ceiling
                            tileGrid[x][y] += 0.11;
                        } else {
                            //rightstickout
                            tileGrid[x][y] += 0.15;
                        }
                    } else if (toTheRight){
                        //leftstickout
                        tileGrid[x][y] += 0.13;
                    } else {
                        //single
                        tileGrid[x][y] += 0.17;
                    }
                    if(tileGrid[x][y] == tileNum){
                        std::cout<< "tile at (" <<x<<", "<<y<<") was not processed correctly"<<std::endl;
                        std::cout<< "above: " << above << std::endl;
                        std::cout<< "below: " << below << std::endl;
                        std::cout<< "toTheRight: " << toTheRight << std::endl;
                        std::cout<< "toTheLeft: " << toTheLeft << "\n" << std::endl;
                    }
                }
            }
        }
    }
}

void Tiles::mapInit(Level level, std::vector<Object::tileHolder> t) {
    for (int i = 0; i < level.tileGrid[0].size(); i++) {
        std::vector<float> collumn;
        for (int a = 0; a < level.tileGrid.size(); a++) {
            collumn.push_back(0);
        }
        loadedLevel.push_back(collumn);
    }
	for (int i = 0; i < level.tileGrid.size(); i++) {
		for (int a = 0; a < level.tileGrid[i].size(); a++) {
			loadedLevel[a][i] = level.tileGrid[i][a];
		}
	}
    for(int i = 0; i < t.size(); i++){
        sortTiles(loadedLevel, t[i].tileNum);
    }
}

void Tiles::showCorrectTiles(float n, SDL_Rect destination, SDL_Renderer* renderer, std::vector<Object::tileHolder> t){
    for(int i = 0 ; i < t.size(); i++){
        if(t[i].kind == 0){
            if(n == (float) (t[i].tileNum + 0.1)){
                SDL_RenderCopy(renderer, t[i].topLeft, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.2)){
                SDL_RenderCopy(renderer, t[i].top, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.3)){
                SDL_RenderCopy(renderer, t[i].topRight, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.4)){
                SDL_RenderCopy(renderer, t[i].right, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.5)){
                SDL_RenderCopy(renderer, t[i].bottomRight, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.6)){
                SDL_RenderCopy(renderer, t[i].bottom, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.7)){
                SDL_RenderCopy(renderer, t[i].bottomLeft, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.8)){
                SDL_RenderCopy(renderer, t[i].left, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.9)){
                SDL_RenderCopy(renderer, t[i].center, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.11)){
                SDL_RenderCopy(renderer, t[i].ceiling, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.12)){
                SDL_RenderCopy(renderer, t[i].wall, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.13)){
                SDL_RenderCopy(renderer, t[i].leftStickOut, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.14)){
                SDL_RenderCopy(renderer, t[i].topStickOut, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.15)){
                SDL_RenderCopy(renderer, t[i].rightStickOut, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.16)){
                SDL_RenderCopy(renderer, t[i].bottomStickOut, nullptr, &destination);
            } else if(n == (float) (t[i].tileNum + 0.17)){
                SDL_RenderCopy(renderer, t[i].single, nullptr, &destination);
            }
        }
    }
}

void Tiles::drawTiles(std::vector<std::vector<float>> tileGrid, Object::Camera camera, SDL_Renderer* renderer, std::vector<Object::tileHolder> t) {
	SDL_Rect destination;
	destination.w = TILE_WIDTH;
	destination.h = TILE_HEIGHT;
	for (int y = 0; y < tileGrid.size(); y++) {
		for (int x = 0; x < tileGrid[0].size(); x++) {
			if (tileGrid[x][y] != 0 && x * TILE_WIDTH >= camera.x - TILE_WIDTH && x * TILE_WIDTH < camera.x + SCREEN_WIDTH) {
				destination.x = x * TILE_WIDTH - camera.x;
                destination.y = y * TILE_HEIGHT - camera.y;
                if(t[0].kind == 1){
                    destination.y -= TILE_HEIGHT/2;
                }
                for(int i = 0; i < t.size(); i++){
                    if(tileGrid[x][y] >= t[i].tileNum && tileGrid[x][y] < (t[i].tileNum + 1)){
                        showCorrectTiles(tileGrid[x][y], destination, renderer, t);
                    }
                }
			}
		}
	}
}

void Tiles::checkCollision(std::vector<std::vector<float>> tileGrid, Object::Player &a, std::vector<Object::tileHolder> t) {
    yPushed = 0;
    xPushed = 0;
    float colOverlap = 0;
    float xOverlap;
    float yOverlap;
    int correctIndex;
    for(int i = 0; i < 9; i++){
        overallOverlap[i] = 0;
        interceptsX[i] = 0;
        interceptsY[i] = 0;
    }
    for (int i = 0; i < tileGrid[0].size(); i++) {
        for (int e = 0; e < tileGrid.size(); e++) {
            if (tileGrid[i][e] != 0) {
                lEdge = i * TILE_WIDTH;
                rEdge = i * TILE_WIDTH + TILE_WIDTH;
                tEdge = e * TILE_HEIGHT - 0;
                bEdge = e * TILE_HEIGHT + TILE_HEIGHT - 0;
                if (a.x + a.hitbox.width / 2 >lEdge && a.x - a.hitbox.width / 2 < rEdge && a.y + a.hitbox.height / 2 > tEdge && a.y - a.hitbox.height / 2 < bEdge) {
                    if(a.x + a.hitbox.width / 2 < rEdge){
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
                                interceptsX[j] = interceptsX[j - 1];
                                interceptsY[j] = interceptsY[j - 1];
                            } else if (j == correctIndex) {
                                overallOverlap[j] = colOverlap;
                                interceptsX[j] = i;
                                interceptsY[j] = e;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < 9; i ++){
        if(tileGrid[interceptsX[i]][interceptsY[i]] != 0){
            lEdge = interceptsX[i] * TILE_WIDTH;
            rEdge = interceptsX[i] * TILE_WIDTH + TILE_WIDTH;
            tEdge = interceptsY[i] * TILE_HEIGHT - 0;
            bEdge = interceptsY[i] * TILE_HEIGHT + TILE_HEIGHT - 0;
            if (a.x + a.hitbox.width / 2 > lEdge && a.x - a.hitbox.width / 2 < rEdge && a.y + a.hitbox.height / 2 > tEdge && a.y - a.hitbox.height / 2 < bEdge) {
                int which;
                for(int i = 0; i < t.size(); i++){
                    if(floor(tileGrid[interceptsX[i]][interceptsY[i]]) == t[i].tileNum){
                        which = i;
                    }
                }
                a.friction = t[which].friction;
                if(t[which].kind == 0){
                    if ((a.y + a.hitbox.height / 2) <= (tEdge + a.velY)) {
                        a.y = tEdge - a.hitbox.height / 2;
                        if(a.velY >= 0){
                            a.velY = 0;
                            a.airborne = false;
                        }
                    } else if ((a.y - a.hitbox.height / 2) >= (bEdge + a.velY)){
                        a.y = bEdge + a.hitbox.height / 2;
                        a.velY = 0;
                    } else if ((a.x - a.hitbox.width / 2) >= (rEdge + a.velX)){
                        a.x = rEdge + a.hitbox.width / 2;
                        a.velX = 0;
                    } else {
                        a.x = lEdge - a.hitbox.width / 2;
                        a.velX = 0;
                    }
                } else {
                    if ((a.y + a.hitbox.height / 2) <= (tEdge + a.velY)) {
                        a.y = tEdge - a.hitbox.height / 2;
                        if(a.velY >= 0){
                            a.velY = 0;
                            a.airborne = false;
                        }
                    }
                }
            }
        }
    }
}

//for the grapple collisions
Object::Point Tiles::checkLineCollision(std::vector<std::vector<float>> tileGrid, Object:: Point a, Object:: Point b) {
    //slope and intercept
    m = (a.y - b.y)/(a.x - b.x);
    intercept = a.y - (m * a.x);
    distance = 100000;
    lineCollided = false;
    for(int x = 0; x < 32; x++){
        for(int y = 0; y < 24; y++){
            if(tileGrid[x][y] != 0){
                //edges and where the line x/y will be at when given those edges
                //y = mx + b
                //x = y - b /m
                lEdge = x * TILE_WIDTH;
                rEdge = x * TILE_WIDTH + TILE_WIDTH;
                tEdge = y * TILE_HEIGHT;
                bEdge = y * TILE_HEIGHT + TILE_HEIGHT;
                if(a.x < b.x){
                    if(rEdge < a.x){
                        break;
                    }
                    if(lEdge > b.x){
                        break;
                    }
                } else {
                    if(rEdge < b.x){
                        break;
                    }
                    if(lEdge > a.x){
                        break;
                    }
                }
                if(a.y < b.y){
                    if(tEdge < a.y){
                        break;
                    }
                    if(bEdge > b.y){
                        break;
                    }
                } else {
                    if(tEdge < b.y){
                        break;
                    }
                    if(bEdge > a.y){
                        break;
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
                        distance = sqrt(pow(a.x - lineCollision.x,2) + pow(a.y - lineCollision.y, 2));
                    }
                }
            }
        }
    }
    if(lineCollided){
        return lineCollision;
    }
    lineCollided = false;
    return b;
}
