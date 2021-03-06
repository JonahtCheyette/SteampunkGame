#include "stdafx.h"

int main(int argc, char * args[]) {
    //for better hook control
	//SDL_Texture* texture = nullptr;
	SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow("STEAMPUNK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);// add in " | SDL_RENDERER_PRESENTVSYNC" after SDL_RENDERER_ACCELERATED for vsync
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Event e;
    SDL_Color black = {0,0,0};
    TTF_Font* Sans = TTF_OpenFont("Steampunk-Game/Assets/Fonts/comic.ttf", 28);
    
    int whichLevel = 0;
    
    Player player(renderer);
    
    std::vector<Object::tileHolder> tileVector;
    std::vector<Level> levels;
    
    loader.loadTiles(tileVector, "Steampunk-Game/tData/", renderer);
    loader.loadLevels(levels, "Steampunk-Game/Levels", renderer);
    
    bool dMode = false;
    bool dSwitch = false;
    Dper.init(black, Sans, renderer);
    player.pos.set(levels[whichLevel].spawn.x, levels[whichLevel].spawn.y);
    
    std::string type = "drag";
    
	Object::Camera camera;

    Tiles::mapInit(levels[whichLevel].tileGrid, tileVector);
    
    object.textureInit(renderer);
	menu.menuInit(renderer);
    
	while (!event.quit) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		event.update(e);
        
		menu.mainMenuButtons(event.mouseX, event.mouseY, event.mouse1, event.quit, event.inGame);
		menu.drawMainMenu(renderer);
		while (event.inGame && !event.quit) {//game loop
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            
			//key presses
            event.update(e);
			event.keyboard_state_array = SDL_GetKeyboardState(NULL);
			if (event.keyboard_state_array[SDL_SCANCODE_ESCAPE]) menu.pauseMenuOpen = true;
            if (event.keyboard_state_array[SDL_SCANCODE_Z] && !dSwitch){
                dMode = !dMode;
                Dper.reset(levels[whichLevel]);
                Dper.init(black, Sans, renderer);
                dSwitch = true;
            }
            if(!event.keyboard_state_array[SDL_SCANCODE_Z]){
                dSwitch = false;
            }
			while (menu.pauseMenuOpen && !event.quit) {
                event.update(e);
				menu.pauseMenuButtons(event.mouseX, event.mouseY, event.mouse1Released, event.quit);
                
                menu.drawPauseMenu(renderer);
                
				SDL_RenderPresent(renderer);
			}
            if(!dMode){
                player.move(e, levels[whichLevel], camera, Tiles::getLoadedLevel(), whichLevel, (int) (levels.size()));
                
                player.moveHook(levels[whichLevel].hookList);
                
                Tiles::checkCollision(Tiles::getLoadedLevel(), player);
                
                levels[whichLevel].update(player, camera);
                
                camera.move(player.pos.x, player.pos.y, levels[whichLevel].width, levels[whichLevel].height);
            } else {
                Dper.moveCamera(camera, event);
                if(type == "drag"){
                    Dper.editLevel(camera, tileVector, levels[whichLevel], renderer, event, Tiles::getLoadedLevel());
                } else {
                    Dper.editAssets(camera, event, levels[whichLevel], renderer, black, Sans);
                }
                Dper.createSwitch(event, black, Sans, renderer);
                Dper.typeSwitch(event, type, black, Sans, renderer);
                Dper.switchTile(event, tileVector, type, black, Sans, renderer);
                Dper.changeHookMoveSpeed(event, levels[whichLevel].hookList, black, Sans, renderer, levels[whichLevel].path);
            }
            
            levels[whichLevel].background.drawBackground(renderer, camera, levels[whichLevel].overlap);
            
            object.drawHooks(levels[whichLevel].hookList, camera, player.selectedHook, renderer);
            levels[whichLevel].draw(renderer, camera);
            if(!dMode){
                player.draw(camera, renderer);
            }
            
            Tiles::drawTiles(Tiles::getLoadedLevel(), camera, renderer, tileVector);
            
            levels[whichLevel].renderEnd(camera, renderer);
            
            if(dMode) {
                Dper.showEditing(type, black, Sans, tileVector, renderer);
                Dper.renderDRect(renderer, type, event, levels[whichLevel], camera);
            }
            
            if(player.hookState == 2) SDL_RenderDrawLine(renderer, player.pos.x - camera.x, player.pos.y - camera.y, player.target.x - camera.x, player.target.y - camera.y);
            if(player.hookState == 1 || player.hookState == 3) SDL_RenderDrawLine(renderer, player.pos.x - camera.x, player.pos.y - camera.y, player.grappleHead.x - camera.x, player.grappleHead.y - camera.y);
            if(!menu.pauseMenuOpen){
                SDL_RenderPresent(renderer);
            }
		}
        SDL_RenderPresent(renderer);
        if(event.quit) break;
	}
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
