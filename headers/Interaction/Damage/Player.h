#include <SDL3/SDL.h>
#include <vector>
#include "../../player.h"
#include "../../Entities/enemies.h"
#include "../../Entities/enemy_management.h"

extern std::vector <Enemy> enemies;
extern SDL_Renderer* renderer;
extern Player player;

void checkPlayerAttackRange() {
    for(int i = 0; i < enemies.size(); i++) {
        int playerX = player.getX();
        int playerY = player.getY();
        int enemyX = enemies[i].getX();
        int enemyY = enemies[i].getY();

        int distance = sqrt((playerX - enemyX)*(playerX - enemyX) + (playerY - enemyY)*(playerY - enemyY));

        if(distance < player.getAttackRange()) {
            enemies[i].decreaseHP(player.getDMG());
            if(enemies[i].isDead()) {
                enemies.erase(enemies.begin() + i);
            }
        }
    }
}