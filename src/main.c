#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include "../headers/init.h"
#include "../headers/map.h"
#include "../headers/player.h"
#include "../headers/camera.h"
#include "../headers/enemies.h"

const int width = 1920;
const int height = 1080;

SDL_Window *window;
SDL_Renderer *renderer;
Camera camera = Camera(width, height);
Player player;

SDL_Texture* grassTexture = nullptr;
SDL_Texture* waterTexture = nullptr;

void stopFlag(bool& running) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
    }
}

int main(int argc, char* argv[]) {
    if (!initSDL()) return -1;

    grassTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Img/Tiles/tile_6_0.bmp"));
    waterTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("Img/Tiles/tile_13_0.bmp"));

    generateMap();

    bool running = true;

    while (running) {
        stopFlag(running);

        player.move(SDL_GetKeyboardState(NULL));
        camera.reposition(player.x, player.y);


        if (rand() % 100 < 2) spawnEnemy();
        updateEnemies();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMap();
        renderEnemies();
        renderMinimap();
        player.renderHPBar();

        SDL_Rect playerRect = {player.x-camera.x, player.y-camera.y, 32, 32 };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup();
    return 0;
}

