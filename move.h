#pragma once
#include "stdafx.h"

class Move {
	public:
		void moveCamera(Object::Camera &a, Object::Player b, Level l);
        void movePlayer(Object::Player &a, SDL_Event& e, Level l, Object::Camera c, std::vector<Object::Tile> tileGrid);
		void moveHook(Object::Player &a);
        void grapple(Object:: Player &a, Object::Point b, std::vector<Object::Tile> tileGrid, Object::Camera c);
        void applyForce(Object:: Player &a, float forceX, float forceY);
        //for changing what hook the player is targeting
        void changeHooks(Object:: Player &a, std::vector<Object:: Point> b, int change, Object::Camera c);
};
