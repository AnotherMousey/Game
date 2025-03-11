#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <player.h>
#include <camera.h>

extern SDL_Renderer* renderer;
extern Camera camera;
extern Player player;

struct Enemy {
    int x, y;
    int speed = 2;
};

std::vector<Enemy> enemies;

void spawnEnemy() {
    int spawnDistance = 400;
    int randX = player.x + ((rand() % 2 == 0 ? -1 : 1) * spawnDistance);
    int randY = player.y + ((rand() % 2 == 0 ? -1 : 1) * spawnDistance);
    enemies.push_back({ randX, randY });
}

void updateEnemies() {
    for (auto& enemy : enemies) {
        int dx = player.x - enemy.x;
        int dy = player.y - enemy.y;
        float length = SDL_sqrt(dx * dx + dy * dy);
        if (length > 0) {
            enemy.x += dx / length * enemy.speed;
            enemy.y += dy / length * enemy.speed;
        }
    }
}

void renderEnemies() {
    for (auto& enemy : enemies) {
        SDL_Rect rect = { enemy.x - camera.x, enemy.y - camera.y, 32, 32 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}
