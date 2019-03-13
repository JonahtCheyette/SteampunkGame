#pragma once
#include "stdafx.h"

class Menu {
public:
	void menuInit(SDL_Renderer* renderer);

	void drawMainMenu(SDL_Renderer* renderer);
	void drawPauseMenu(SDL_Renderer* renderer);

	void mainMenuButtons(int mouseX, int mouseY, bool mouse1, bool &quit, bool &inGame);
	void pauseMenuButtons(int mouseX, int mouseY, bool mouse1, bool &quit, bool &pauseMenuOpen);

	SDL_Texture* mainMenu;
	SDL_Texture* pauseMenu;

	SDL_Rect mainMenuDest;
	SDL_Rect pauseMenuDest;

	bool pauseMenuOpen;
};
