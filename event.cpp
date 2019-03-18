#include "stdafx.h"

void Event::update(SDL_Event &e) {
	SDL_GetMouseState(&mouseX, &mouseY);
	mouse1 = false;
	mouse2 = false;
    mouse1Released = false;
    mouse2Released = false;
	while (SDL_PollEvent(&e) != 0) {
		//quiting the program
		switch (e.type) {
		case SDL_QUIT:
			inGame = false;
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_PumpEvents();
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				mouse1 = true;
				mouse1held = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse2 = true;
				mouse2held = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_PumpEvents();
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				mouse1held = false;
                mouse1Released = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse2held = false;
                mouse2Released = true;
				break;
			}
			break;
		}
	}
}

void Event::clear(SDL_Event &e){
    mouse1 = false;
    mouse2 = false;
    mouse1Released = false;
    mouse2Released = false;
    mouse1held = false;
    mouse2held = false;
    mouseX = 0;
    mouseY = 0;
}
