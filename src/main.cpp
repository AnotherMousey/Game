#include<SDL3/SDL.h>
#include<SDL3/SDL_main.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3_image/SDL_image.h>
#include <iostream>  
#include "../headers/init.h"
#include "../headers/map.h"
#include "../headers/player.h"
#include "../headers/camera.h"
#include "../headers/Entities/enemy_management.h"
#include "../headers/Interaction/Damage/Entities.h"
#include "../headers/animation.h"
#include "../headers/Interaction/Damage/Player.h"

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
        if (e.type == SDL_EVENT_QUIT) {
            running = false;
        }
    }
}

int main(int argc, char* argv[]) {
    if (!initSDL()) return -1;

    SDL_Surface* grassSurface = IMG_Load("Img/Tiles/tile_6_0.bmp");
    SDL_Surface* waterSurface = IMG_Load("Img/Tiles/tile_13_0.bmp");
    if (!grassSurface || !waterSurface) {
        printf("Failed to load images: %s\n", SDL_GetError());
        return -1;
    }
    
    grassTexture = SDL_CreateTextureFromSurface(renderer, grassSurface);
    waterTexture = SDL_CreateTextureFromSurface(renderer, waterSurface);
    SDL_DestroySurface(grassSurface);
    SDL_DestroySurface(waterSurface);

    generateMap();

    loadAllAnimation();

    bool running = true;

    while (running) {
        stopFlag(running);

        SDL_PumpEvents();
        player.move(SDL_GetKeyboardState(NULL));
        camera.reposition(player.getX(), player.getY());

        EnemyUpdate();
        checkEnemyCollision();
        if (rand() % 100 < 2) EnemySpawn();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMap();
        renderEnemies();
        renderMinimap();
        playerAnimationAndAttack();
        player.renderHPBar();

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup();
    return 0;
}
