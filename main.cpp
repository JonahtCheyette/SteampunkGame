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
    
	Object::Camera camera;
    
	Object::Player player;
	player.hitbox.width = 50;
	player.hitbox.height = 50;
    
	tiles.mapInit(levels[0], tileVector);
    
    object.textureInit(renderer);
	menu.menuInit(renderer);
    
    int whichLevel = 0;
    
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
            
            move.movePlayer(player, e, levels[whichLevel], camera, tiles.loadedLevel);
            move.moveHook(player);
            
            tiles.checkCollision(tiles.loadedLevel, player, tileVector);

			move.moveCamera(camera, player, levels[whichLevel]);
            
            levels[whichLevel].background.drawBackground(renderer, camera, levels[whichLevel].height);
            
            tiles.drawTiles(tiles.loadedLevel, camera, renderer, tileVector);
            
            object.drawHooks(levels[whichLevel].hookList, camera, player.selectedHook, renderer);
			object.drawPlayer(player, camera, renderer);

			//SDL_RenderDrawLine(renderer, 0 - camera.x, 100 - camera.y, 3000 - camera.x, 400 - camera.y);
            
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
