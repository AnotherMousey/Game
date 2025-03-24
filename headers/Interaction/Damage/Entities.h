#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "../../player.h"
#include "../../Entities/enemies.h"
#include "../../Entities/enemy_management.h"

extern std::vector <Enemy*> enemies;
extern SDL_Renderer* renderer;
extern Player player;

void checkEnemyCollision() {
    for (int i = 0; i < enemies.size(); i++) {
        SDL_FRect playerRect = { (float) player.getX(), (float) player.getY(), 32, 32 };
        SDL_FRect enemyRect = { (float) enemies[i]->getX(), (float) enemies[i]->getY(), 32, 32 };

        if (SDL_HasRectIntersectionFloat(&playerRect, &enemyRect)) {
            int currentTime = SDL_GetTicks();
            if (currentTime - enemies[i]->getLastDamageTime() > 1000) {
                player.decreaseHP(enemies[i]->getDMG());
                enemies[i]->setLastDamageTime(currentTime);
            }
        }
    }
}