#pragma once
#include "stdafx.h"

class Event {
	public:
		void update(SDL_Event &e);
        void clear(SDL_Event &e);

		int mouseX, mouseY;
		bool mouse1, mouse2;
		bool mouse1held, mouse2held;
        bool mouse1Released, mouse2Released;

		const Uint8 *keyboard_state_array;

		bool quit = false;//program loop flag
		bool inGame = false;//game loop flag
};
