#include "stdafx.h"

void Menu::menuInit(SDL_Renderer* renderer) {
	mainMenu.load("Steampunk-Game/Assets/Images/Menus/menu.png", renderer);

	pauseMenu.load("Steampunk-Game/Assets/Images/Menus/pauseMenu.png", renderer);
}

void Menu::drawMainMenu(SDL_Renderer* renderer) {
    mainMenu.render(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Menu::drawPauseMenu(SDL_Renderer * renderer) {
	pauseMenu.render(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Menu::mainMenuButtons(int mouseX, int mouseY, bool mouse1, bool &quit, bool &inGame) {
	if (mouse1) {
		if (mouseY < SCREEN_HEIGHT / 2) inGame = true;
		else if (mouseY > SCREEN_HEIGHT / 2) quit = true;
	}
}

void Menu::pauseMenuButtons(int mouseX, int mouseY, bool mouse1, bool &quit) {
    if (mouse1) {
        pauseMenuOpen = false;
		if (mouseY >= SCREEN_HEIGHT / 2) {
            quit = true;
		}
	}
}


