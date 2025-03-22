#pragma once
#include<SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3_image/SDL_image.h>
#include <iostream>

extern const int width;
extern const int height;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern TTF_Font* hpfont;

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialise SDL_ttf: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Vampire Survivors Clone", width, height, SDL_WINDOW_HIDDEN);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowResizable(window, true);
    SDL_ShowWindow(window);

    renderer = SDL_CreateRenderer(window, nullptr); 
    if (!renderer) {
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }

    return true;
}

void cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}