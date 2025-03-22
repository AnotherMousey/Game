#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "camera.h"
#include <iostream>

extern const int width;
extern const int height;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern Camera camera;

const int MAP_WIDTH = 4000;
const int MAP_HEIGHT = 4000;
const int TILE_SIZE = 40;
const int MINIMAP_SIZE = 200;
const int MINIMAP_TILE_SIZE = MINIMAP_SIZE / TILE_SIZE;
const int NUM_TILES_X = MAP_WIDTH / TILE_SIZE;
const int NUM_TILES_Y = MAP_HEIGHT / TILE_SIZE;

enum TileType { GRASS, WATER };
TileType map[NUM_TILES_Y][NUM_TILES_X];

extern SDL_Texture* grassTexture;
extern SDL_Texture* waterTexture;

void generateMap() {
    for (int y = 0; y < NUM_TILES_Y; y++) {
        for (int x = 0; x < NUM_TILES_X; x++) {
            map[y][x] = (rand() % 5 == 0) ? WATER : GRASS;
        }
    }
}

void renderMap() {
    int startX = camera.x / TILE_SIZE;
    int startY = camera.y / TILE_SIZE;
    int endX = (camera.x + width) / TILE_SIZE;
    int endY = (camera.y + height) / TILE_SIZE;

    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            if (x < 0 || y < 0 || x >= NUM_TILES_X || y >= NUM_TILES_Y) continue;

            SDL_FRect srcRect = { 0, 0, TILE_SIZE, TILE_SIZE };
            SDL_FRect destRect = { (float) x * TILE_SIZE - camera.x, (float) y * TILE_SIZE - camera.y, TILE_SIZE, TILE_SIZE };

            SDL_Texture* texture = (map[y][x] == GRASS) ? grassTexture : waterTexture;
            SDL_RenderTexture(renderer, texture, &srcRect, &destRect);
        }
    }
}

void renderMinimap() {
    SDL_FRect minimapRect = {10, (float) height - MINIMAP_SIZE - 310, MINIMAP_SIZE, MINIMAP_SIZE };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 200);
    SDL_RenderFillRect(renderer, &minimapRect);

    for (int y = 0; y < NUM_TILES_Y; y++) {
        for (int x = 0; x < NUM_TILES_X; x++) {
            SDL_FRect tileRect = { minimapRect.x + x * MINIMAP_TILE_SIZE, minimapRect.y + y * MINIMAP_TILE_SIZE,
                                  MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE };

            SDL_SetRenderDrawColor(renderer, (map[y][x] == GRASS) ? 34 : 0, (map[y][x] == GRASS) ? 139 : 0, 34, 255);
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}