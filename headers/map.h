#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <camera.h>
#include <player.h>

const int MAP_WIDTH = 4000;
const int MAP_HEIGHT = 4000;
const int TILE_SIZE = 40;
const int MINIMAP_SIZE = 200;
const int MINIMAP_TILE_SIZE = MINIMAP_SIZE / TILE_SIZE;
const int NUM_TILES_X = MAP_WIDTH / TILE_SIZE;
const int NUM_TILES_Y = MAP_HEIGHT / TILE_SIZE;

enum TileType { GRASS, WATER };
TileType map[NUM_TILES_Y][NUM_TILES_X];

extern const int width;
extern const int height;
extern SDL_Renderer* renderer;
extern Camera camera;
extern Player player;

void generateMap() {
    for (int y = 0; y < NUM_TILES_Y; y++) {
        for (int x = 0; x < NUM_TILES_X; x++) {
            map[y][x] = (rand() % 5 == 0) ? WATER : GRASS;
        }
    }
}

extern SDL_Texture* grassTexture;
extern SDL_Texture* waterTexture;

SDL_Texture* loadTexture(const char* path) {
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void renderMap() {
    int startX = camera.x / TILE_SIZE;
    int startY = camera.y / TILE_SIZE;
    int endX = (camera.x + width) / TILE_SIZE;
    int endY = (camera.y + height) / TILE_SIZE;

    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            if (x < 0 || y < 0 || x >= NUM_TILES_X || y >= NUM_TILES_Y) continue;

            SDL_Rect srcRect = { 0, 0, TILE_SIZE, TILE_SIZE };
            SDL_Rect destRect = { x * TILE_SIZE - camera.x, y * TILE_SIZE - camera.y, TILE_SIZE, TILE_SIZE };

            SDL_Texture* texture = (map[y][x] == GRASS) ? grassTexture : waterTexture;
            SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
        }
    }
}

void renderMinimap() {
    SDL_Rect minimapRect = {10, height - MINIMAP_SIZE - 310, MINIMAP_SIZE, MINIMAP_SIZE };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 200);
    SDL_RenderFillRect(renderer, &minimapRect);

    for (int y = 0; y < NUM_TILES_Y; y++) {
        for (int x = 0; x < NUM_TILES_X; x++) {
            SDL_Rect tileRect = { minimapRect.x + x * MINIMAP_TILE_SIZE, minimapRect.y + y * MINIMAP_TILE_SIZE,
                                  MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE };

            SDL_SetRenderDrawColor(renderer, (map[y][x] == GRASS) ? 34 : 0, (map[y][x] == GRASS) ? 139 : 0, 34, 255);
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }

    SDL_Rect playerRect = { minimapRect.x + (player.x / TILE_SIZE) * MINIMAP_TILE_SIZE,
                            minimapRect.y + (player.y / TILE_SIZE) * MINIMAP_TILE_SIZE, 4, 4 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}