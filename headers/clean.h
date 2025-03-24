#pragma once
#include <map>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "animation.h"
#include "map.h"
#include "player.h"
#include "camera.h"
#include "Entities/enemies.h"
#include "Entities/enemy_management.h"
#include "Interaction/Damage/Entities.h"
#include "Interaction/Damage/Player.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern std::map<std::string, std::vector<SDL_Texture*>> animations;
extern std::vector <Enemy*> enemies;

void cleanup() {
    for (auto& [name, textures] : animations) {
        for (auto& texture : textures) {
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
        textures.clear();
    }
    animations.clear();

    for (auto& enemy : enemies) {
        if (enemy) {
            delete enemy;
        }
    }
    enemies.clear();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}