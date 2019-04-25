#pragma once
#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#endif
#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif
#ifdef _WIN64
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif
#undef main

#include <dirent.h>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

#include "Sprite.h"
#include "object.h"
static Object object;
#include "Vector.h"
#include "background.h"
#include "physicsApplied.h"
#include "event.h"
static Event event;
#include "menu.h"
static Menu menu;
#include "Crate.h"
#include "tiles.h"
static Tiles tiles;
#include "Level.h"
#include "Player.h"
#include "loader.h"
static Loader loader;
#include "developerMode.h"
static developer Dper;

constexpr auto SCREEN_WIDTH = (1920 / 3) * 2; // accounting for scaling on personal device
constexpr auto SCREEN_HEIGHT = (1200 / 3) * 2;

//radius offscreen of physics updates for objects, e.g. if they are offscreen but within this many pixels, they will still do physics
constexpr auto physUpdateRange = 1000;

constexpr auto TILE_WIDTH = 32;
constexpr auto TILE_HEIGHT = 32;

//physics constants
constexpr auto grappleStrength = -40;
constexpr auto Gravity = 0.5;
