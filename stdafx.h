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

#include "object.h"
static Object object;
#include "background.h"
#include "Level.h"
#include "event.h"
static Event event;
#include "menu.h"
static Menu menu;
#include "move.h"
static Move move;
#include "draw.h"
static Draw draw;
#include "tiles.h"
static Tiles tiles;
#include "loader.h"
static Loader loader;

constexpr auto SCREEN_WIDTH = (1920 / 3) * 2; // accounting for scaling on personal device
constexpr auto SCREEN_HEIGHT = (1080 / 3) * 2;

constexpr auto TILE_WIDTH = 32;
constexpr auto TILE_HEIGHT = 32;

//constexpr auto overlap = 24 * TILE_HEIGHT - LEVEL_HEIGHT;

//tile types
constexpr auto topLeft = 1;
constexpr auto top = 2;
constexpr auto topRight = 3;
constexpr auto right = 4;
constexpr auto bottomRight = 5;
constexpr auto bottom = 6;
constexpr auto bottomLeft = 7;
constexpr auto left = 8;
constexpr auto center = 9;

//physics constants
constexpr auto grappleStrength = -40;
constexpr auto Gravity = 0.5;
