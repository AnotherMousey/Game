#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "Entities/enemy_management.h"
#include "camera.h"
#include "player.h"

extern const int width;
extern const int height;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern Player player;
extern Camera camera;

const int map_width = 2000;
const int map_height = 2000;
const int tile = 40;
const int minimap_size = 200;
const int minimap_tile = minimap_size / tile;
const int minimap_width = map_width / tile;
const int minimap_height = map_height / tile;

enum TileType { GRASS, WATER };
TileType map[minimap_height][minimap_width];

extern SDL_Texture* grassTexture;
extern SDL_Texture* waterTexture;

void generateMap() {
    for (int y = 0; y < minimap_height; y++) {
        for (int x = 0; x < minimap_width; x++) {
            map[y][x] = (rand() % 5 == 0) ? WATER : GRASS;
        }
    }
}

void renderMap() {
    int startX = camera.x / tile;
    int startY = camera.y / tile;
    int endX = (camera.x + width) / tile;
    int endY = (camera.y + height) / tile;

    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
            if (x < 0 || y < 0 || x >= minimap_width || y >= minimap_height) continue;

            SDL_FRect srcRect = { 0, 0, tile, tile };
            SDL_FRect destRect = { (float) x * tile - camera.x, (float) y * tile - camera.y, tile, tile };

            SDL_Texture* texture = (map[y][x] == GRASS) ? grassTexture : waterTexture;
            SDL_RenderTexture(renderer, texture, &srcRect, &destRect);
        }
    }
}

void renderMinimap() {
    SDL_FRect minimapRect = {10, (float) height - minimap_size - 60, minimap_size, minimap_size };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 200);
    SDL_RenderFillRect(renderer, &minimapRect);

    for (int y = 0; y < minimap_height; y++) {
        for (int x = 0; x < minimap_width; x++) {
            SDL_FRect tileRect = { minimapRect.x + x * minimap_tile, minimapRect.y + y * minimap_tile,
                                  minimap_tile, minimap_tile };

            SDL_SetRenderDrawColor(renderer, (map[y][x] == GRASS) ? 34 : 0, (map[y][x] == GRASS) ? 139 : 0, 34, 255);
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }

    SDL_FRect playerRect = { (float) minimapRect.x + (player.getX() / tile) * minimap_tile,
        (float) minimapRect.y + (player.getY() / tile) * minimap_tile, 4, 4 };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);

    renderEnemiesOnMiniMap();
}