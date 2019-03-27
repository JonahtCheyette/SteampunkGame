#include "stdafx.h"

int main(int argc, char * args[]) {
    //for better hook control
	//SDL_Texture* texture = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow("SDL Testing things", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);// add in " | SDL_RENDERER_PRESENTVSYNC" after SDL_RENDERER_ACCELERATED for vsync
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Event e;
    SDL_Color black = {1,0,0};
    TTF_Font* Sans = TTF_OpenFont("Steampunk-Game/Assets/Fonts/comic.ttf", 28);
    if(Sans == NULL){
        std::cout<<"j";
    }
    
    int whichLevel = 0;
    
    Player player(renderer, draw);
    
    std::vector<Object::tileHolder> tileVector;
    std::vector<Level> levels;
    
    loader.loadTiles(tileVector, "Steampunk-Game/tData/", renderer);
    loader.loadLevels(levels, "Steampunk-Game/Levels", renderer, draw);
    
    bool dMode = true;
    bool dSwitch = false;
    Dper.init(draw, black, Sans, renderer);
    player.x = levels[whichLevel].spawn.x;
    player.y = levels[whichLevel].spawn.y;
    
    std::string type = "drag";
    
	Object::Camera camera;
    
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
		while (event.inGame) {//game loop
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            
			//key presses
            event.update(e);
			event.keyboard_state_array = SDL_GetKeyboardState(NULL);
			if (event.keyboard_state_array[SDL_SCANCODE_ESCAPE]) menu.pauseMenuOpen = true;
            if (event.keyboard_state_array[SDL_SCANCODE_Z] && !dSwitch){
                dMode = !dMode;
                dSwitch = true;
            }
            if(!event.keyboard_state_array[SDL_SCANCODE_Z]){
                dSwitch = false;
            }
			while (menu.pauseMenuOpen && !event.quit) {
				menu.drawPauseMenu(renderer);
				menu.pauseMenuButtons(event.mouseX, event.mouseY, event.mouse1, event.quit, menu.pauseMenuOpen);

				SDL_RenderPresent(renderer);
			}
            if(!dMode){
                player.move(e, levels[whichLevel], camera, tiles.loadedLevel, whichLevel, (int) (levels.size()));
                player.moveHook(levels[whichLevel].hookList);
            
                tiles.checkCollision(tiles.loadedLevel, player);

                object.moveCamera(camera, player.x, player.y, levels[whichLevel].width, levels[whichLevel].height);
            } else {
                Dper.moveCamera(camera, event);
                if(type == "drag"){
                    Dper.editLevel(camera, tileVector, levels[whichLevel], renderer, event, tiles.loadedLevel);
                } else {
                    Dper.editAssets(camera, event, levels[whichLevel], renderer);
                }
                Dper.createSwitch(event, black, Sans, renderer);
                Dper.typeSwitch(event, type, black, Sans, renderer, draw);
                Dper.switchTile(event, tileVector, type, black, Sans, renderer);
            }
            
            levels[whichLevel].background.drawBackground(renderer, camera, levels[whichLevel].overlap);
            
            object.drawHooks(levels[whichLevel].hookList, camera, player.selectedHook, renderer);
            
            if(!dMode){
                player.draw(camera, renderer);
            }
            
            tiles.drawTiles(tiles.loadedLevel, camera, renderer, tileVector);
            
            levels[whichLevel].renderEnd(camera, renderer);
            
            if(dMode) {
                Dper.showEditing(draw, type, black, Sans, tileVector, renderer);
                Dper.renderDRect(renderer, type, event, levels[whichLevel]);
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
    TTF_Quit();
	SDL_Quit();
	return 0;
}
