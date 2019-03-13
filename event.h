#pragma once
#include "stdafx.h"

class Event {
	public:
		void update(SDL_Event &e);

		int mouseX, mouseY;
		bool mouse1, mouse2;
		bool mouse1held, mouse2held; 

		const Uint8 *keyboard_state_array;

		bool quit = false;//program loop flag
		bool inGame = false;//game loop flag
};