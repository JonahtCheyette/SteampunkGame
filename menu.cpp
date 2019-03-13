#include "stdafx.h"

void Menu::menuInit(SDL_Renderer* renderer) {
	mainMenuDest.x = 0;
	mainMenuDest.y = 0;
	mainMenuDest.w = SCREEN_WIDTH;
	mainMenuDest.h = SCREEN_HEIGHT;

	mainMenu = draw.loadTexture("Steampunk-Game/Assets/Images/Menus/menu.png", renderer);

	pauseMenuDest.x = SCREEN_WIDTH / 5;
	pauseMenuDest.y = SCREEN_HEIGHT / 5;
	pauseMenuDest.w = SCREEN_WIDTH / 5 * 3;
	pauseMenuDest.h = SCREEN_HEIGHT / 5 * 3;

	pauseMenu = draw.loadTexture("Steampunk-Game/Assets/Images/Menus/pauseMenu.png", renderer);
}

void Menu::drawMainMenu(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, mainMenu, nullptr, &mainMenuDest);
}

void Menu::drawPauseMenu(SDL_Renderer * renderer) {
	SDL_RenderCopy(renderer, pauseMenu, nullptr, &pauseMenuDest);
}

void Menu::mainMenuButtons(int mouseX, int mouseY, bool mouse1, bool &quit, bool &inGame) {
	if (mouse1) {
		if (mouseY < SCREEN_HEIGHT / 2) inGame = true;
		else if (mouseY > SCREEN_HEIGHT / 2) quit = true;
	}
}

void Menu::pauseMenuButtons(int mouseX, int mouseY, bool mouse1, bool &quit, bool &pauseMenuOpen) {
	if (mouse1) {
		if (mouseY < SCREEN_HEIGHT / 2) pauseMenuOpen = false;
		else if (mouseY > SCREEN_HEIGHT / 2) {
			pauseMenuOpen = false;
		}
	}
}
