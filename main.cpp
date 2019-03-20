#include "stdafx.h"

int main(int argc, char * args[]) {
    //for better hook control
	//SDL_Texture* texture = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow("SDL Testing things", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);// add in " | SDL_RENDERER_PRESENTVSYNC" after SDL_RENDERER_ACCELERATED for vsync
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Event e;
    
    std::vector<Object::tileHolder> tileVector;
    std::vector<Level> levels;
    
    loader.loadTiles(tileVector, "Steampunk-Game/tData", renderer);
    loader.loadLevels(levels, "Steampunk-Game/Levels", renderer);
    
    bool dMode = true;
    int initX = 0;
    int initY = 0;
    int clickstate = 0;
    bool held = false;
    
    int whichLevel = 0;
    
    
	Object::Camera camera;
    
	Object::Player player;
	player.hitbox.width = 50;
	player.hitbox.height = 50;
    
	tiles.mapInit(levels[whichLevel], tileVector);
    
    object.textureInit(renderer);
	menu.menuInit(renderer);
    
	while (!event.quit) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		event.update(e);
        
		menu.mainMenuButtons(event.mouseX, event.mouseY, event.mouse1, event.quit, event.inGame);
		menu.drawMainMenu(renderer);
        event.clear(e);
		while (event.inGame) {//game loop
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            
			event.update(e);
			//key presses
			SDL_PollEvent(&e);
			event.keyboard_state_array = SDL_GetKeyboardState(NULL);
			if (event.keyboard_state_array[SDL_SCANCODE_ESCAPE]) menu.pauseMenuOpen = true;
			while (menu.pauseMenuOpen && !event.quit) {
				event.update(e);
				menu.drawPauseMenu(renderer);
				menu.pauseMenuButtons(event.mouseX, event.mouseY, event.mouse1, event.quit, menu.pauseMenuOpen);

				SDL_RenderPresent(renderer);
			}
            if(!dMode){
                move.movePlayer(player, e, levels[whichLevel], camera, tiles.loadedLevel);
                move.moveHook(player);
            
                tiles.checkCollision(tiles.loadedLevel, player, tileVector);

                move.moveCamera(camera, player, levels[whichLevel]);
            } else {
                developer.moveCamera(camera);
                //developer.addTiles(tileVector, camera, renderer, initX, initY, clickstate, held, levels[whichLevel], event.mouse1, event.mouse1held, event.mouse1Released, event.mouseX, event.mouseY);
                SDL_Rect heldRect;
                if(event.mouse1 && clickstate == 0){
                    heldRect.x = event.mouseX + camera.x;
                    heldRect.y = event.mouseY + camera.y;
                    initX = heldRect.x;
                    initY = heldRect.y;
                    heldRect.w = 0;
                    heldRect.h = 0;
                    clickstate = 1;
                }
                if(event.mouse1held && heldRect.x != 0 && heldRect.y != 0 && clickstate == 1){
                    heldRect.x = initX - camera.x;
                    heldRect.y = initY - camera.y;
                    heldRect.w = event.mouseX - heldRect.x;
                    heldRect.h = event.mouseY - heldRect.y;
                    SDL_RenderDrawRect(renderer, &heldRect);
                }
                if(held && !event.mouse1held){
                    clickstate = 2;
                }
                held = event.mouse1held;
                if (event.mouse1Released && heldRect.x != 0 && heldRect.y != 0 && clickstate == 2) {
                    int xAmount = abs(round(heldRect.w / TILE_WIDTH));
                    int yAmount = abs(round(heldRect.h / TILE_HEIGHT));
                    int spX = round((heldRect.x + camera.x)/TILE_WIDTH) * TILE_WIDTH;
                    int spY = round((heldRect.y + camera.y)/TILE_HEIGHT) * TILE_HEIGHT;
                    int tx, ty;
                    int sx = (spX/TILE_WIDTH);
                    int fx = (spX/TILE_WIDTH);
                    int sy = (spY/TILE_HEIGHT);
                    int fy = (spY/TILE_HEIGHT);
                    if(heldRect.w > 0){
                        fx += xAmount;
                    } else {
                        sx -= xAmount;
                    }
                    if(heldRect.h > 0){
                        fy += yAmount;
                    } else {
                        sy -= yAmount;
                    }
                    for(int i = 0; i < xAmount; i++){
                        for(int j = 0; j < yAmount; j++){
                            if(heldRect.w > 0){
                                tx = (i * TILE_WIDTH) + spX;
                            } else {
                                tx = -1 * (i * TILE_WIDTH + TILE_WIDTH) + spX;
                            }
                            if(heldRect.h > 0){
                                ty = (j * TILE_HEIGHT) + spY;
                            } else {
                                ty = -1 * (j * TILE_HEIGHT + TILE_HEIGHT) + spY;
                            }
                            Object::Tile t(tx, ty, tileVector[0].friction);
                            t.texture = tileVector[0].single;
                            tiles.loadedLevel.push_back(t);
                        }
                    }
                    std::vector<std::vector<float>> grid;
                    std::string line;
                    std::ifstream mapFile(levels[whichLevel].path + "tiles.txt");
                    while(std::getline(mapFile, line)){
                        std::vector <float> row;
                        for(int j = 0; j < line.length(); j++){
                            if(!isspace(line[j])){
                                row.push_back((float) line[j] - 48);
                            }
                        }
                        if(row.size() != 0){
                            grid.push_back(row);
                        }
                    }
                    mapFile.close();
                    if(fy >= grid.size()){
                        std::vector<float> row;
                        for(int i = 0; i <= fy - grid.size() + 2; i++){
                            std::vector<float> row;
                            for(int j = 0; j < grid[0].size(); j++){
                                row.push_back(0);
                            }
                            grid.push_back(row);
                        }
                    }
                    if(fx >= grid[0].size()){
                        for(int i = 0; i < grid.size(); i++){
                            for(int j = 0; j <= fx - grid[0].size(); j++){
                                grid[i].push_back(0);
                            }
                        }
                    }
                    for(int i = sx; i < fx; i++){
                        for(int j = sy; j < fy; j++){
                            grid[j][i] = 1;
                        }
                    }
                    int correctindex = -1;
                    for(int i = (int) (grid.size() - 1); i >= 0; i--){
                        for(int j = 0; j < grid[i].size(); j++){
                            if(grid[i][j] != 0 && correctindex == -1){
                                correctindex = i;
                            }
                        }
                    }
                    for(int i = (int) (grid.size() - 1); i > correctindex; i--){
                        grid.pop_back();
                    }
                    int chopEnd = -1;
                    for(int i = 0; i < grid.size(); i++){
                        for(int j = 0; j < grid[i].size(); j++){
                            if(grid[i][j] != 0 && j > chopEnd){
                                chopEnd = j;
                            }
                        }
                    }
                    for(int i = 0; i < grid.size(); i++){
                        for(int j = (int) (grid[i].size() - 1); j > chopEnd ; j--){
                            grid[i].pop_back();
                        }
                    }
                    std::ofstream mFile(levels[whichLevel].path + "tiles.txt", std::ofstream::out | std::ofstream::trunc);
                    for(int i = 0; i < grid.size(); i++){
                        std::string l = "";
                        for(int j = 0; j < grid[i].size(); j++){
                            if(j > 0){
                                l += " ";
                            }
                            l += std::to_string((int) grid[i][j]);
                        }
                        if(i != grid.size() + 1){
                            l += "\n";
                        }
                        mFile << l;
                    }
                    mFile.close();
                    clickstate = 0;
                }
            }
            
            levels[whichLevel].background.drawBackground(renderer, camera);
            
            tiles.drawTiles(tiles.loadedLevel, camera, renderer, tileVector);
            
            object.drawHooks(levels[whichLevel].hookList, camera, player.selectedHook, renderer);
            
            if(!dMode){
                object.drawPlayer(player, camera, renderer);
            }

            if(player.hookState == 2) SDL_RenderDrawLine(renderer, player.x - camera.x, player.y - camera.y, player.target.x - camera.x, player.target.y - camera.y);
            if(player.hookState == 1 || player.hookState == 3) SDL_RenderDrawLine(renderer, player.x - camera.x, player.y - camera.y, player.grappleHead.x - camera.x, player.grappleHead.y - camera.y);
			SDL_RenderPresent(renderer);
		}
        SDL_RenderPresent(renderer);
        if(event.quit) break;
	}
	draw.free();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	return 0;
}
