#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

extern const int width;
extern const int height;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize";
        return false;
    }
    
    window = SDL_CreateWindow("Vampire Survivors Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    return true;
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}