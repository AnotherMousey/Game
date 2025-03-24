#pragma once
#include <cmath>
#include <vector>
#include <SDL3/SDL.h>
#include "../map.h"
#include "../player.h"
#include "enemies.h"
#include "Mini_monster/mushroom.h"

std::vector <Enemy*> enemies;
extern SDL_Renderer* renderer;
extern Player player;

void EnemyUpdate() {
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->move();
    }
}

void EnemySpawn() {
    static int lastSpawnTime = 0;
    const int spawnTime = 5000;
    int currentTime = SDL_GetTicks();
    if(currentTime > lastSpawnTime + spawnTime) {
        lastSpawnTime = currentTime;
    } else {
        return;
    }

    int minDistance = 400;
    int maxDistance = 800;

    int distance = minDistance + (rand() % (maxDistance - minDistance)); 

    float angle = (rand() % 360) * (M_PI / 180.0);

    int randX = player.getX() + distance * SDL_cos(angle);
    int randY = player.getY() + distance * SDL_sin(angle);

    if(randX < 0) randX = 0;
    if(randY < 0) randY = 0;
    if(randX >= 4000) randX = 3999;
    if(randY >= 4000) randY = 3999;

    enemies.push_back(new mushroom(randX, randY, 2, 50, 5));
}

void renderEnemies() {
    for (auto enemy : enemies) {
        enemy->render();
    }
}

void renderEnemiesOnMiniMap() {
    for(auto enemy: enemies) {
        SDL_FRect enemyRect = { 
            (float) 10 + (enemy->getX() / 40) * 5,
            (float) height - 200 - 310 + (enemy->getY() / 40) * 5, 
            4, 4 
        };
    
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &enemyRect);
    }
}