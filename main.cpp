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
    
    Player player(renderer, draw);
    
    std::vector<Object::tileHolder> tileVector;
    std::vector<Level> levels;
    
    loader.loadTiles(tileVector, "Steampunk-Game/tData", renderer);
    loader.loadLevels(levels, "Steampunk-Game/Levels", renderer);
    
    bool dMode = true;
    if(dMode){
        Dper.clickstate = 0;
        Dper.x = 0;
        Dper.y = 0;
        Dper.w = 0;
        Dper.h = 0;
        Dper.held = false;
        Dper.moveSpeed = 5;
        Dper.create = true;
        Dper.clicked1 = false;
        Dper.clicked2 = false;
        Dper.clicked3 = false;
        Dper.clicked4 = false;
        Dper.whichTile = 0;
    }
    std::string type = "drag";
    
    int whichLevel = 0;
    
    
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
			while (menu.pauseMenuOpen && !event.quit) {
				menu.drawPauseMenu(renderer);
				menu.pauseMenuButtons(event.mouseX, event.mouseY, event.mouse1, event.quit, menu.pauseMenuOpen);

				SDL_RenderPresent(renderer);
			}
            if(!dMode){
                player.move(e, levels[whichLevel], camera, tiles.loadedLevel);
                player.moveHook();
            
                tiles.checkCollision(tiles.loadedLevel, player, tileVector);

                object.moveCamera(camera, player.x, player.y, levels[whichLevel].width, levels[whichLevel].width);
            } else {
                Dper.moveCamera(camera, event);
                if(type == "drag"){
                    Dper.editLevel(camera, tileVector, levels[whichLevel], renderer, event, tiles.loadedLevel);
                } else {
                    Dper.editAssets(camera, event, levels[whichLevel]);
                }
                Dper.createSwitch(event);
                Dper.typeSwitch(event, type);
                Dper.switchTile(event, tileVector);
            }
            
            levels[whichLevel].background.drawBackground(renderer, camera);
            
            object.drawHooks(levels[whichLevel].hookList, camera, player.selectedHook, renderer);
            
            if(!dMode){
                player.draw(camera, renderer);
            }

            tiles.drawTiles(tiles.loadedLevel, camera, renderer, tileVector);
            
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
