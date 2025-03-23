#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../../Entities/enemies.h"
#include "../../Entities/enemy_management.h"
#include "../../animation.h"
#include "../../camera.h"
#include "../../player.h"

extern SDL_Renderer* renderer;
extern Camera camera;
extern Player player;
extern std::vector <Enemy> enemies;
extern std::map<std::string, std::vector<SDL_Texture*>> animations;

void playerAnimationAndAttack() {
    static int lastFrameTime = 0;
    static int frame = 0;
    int dmgState = 0;

    int currentTime = SDL_GetTicks();
    static std::string name;

    if(currentTime < lastFrameTime + player.getAttackHaste()) {
        name = "boy_" + player.getState();
        if(currentTime < lastFrameTime + player.getAttackHaste()/2) {
            frame = 0;
        } else {
            frame = 1;
        }
    } else if(currentTime >= lastFrameTime + player.getAttackHaste() + player.getAttackSpeed()) {
        lastFrameTime = currentTime;
        for(int i = 0; i < enemies.size(); i++) {
            if(enemies[i].isDamaged()) enemies[i].switchDamaged();
        }
    } else {
        name = "boy_attack_" + player.getState();
        if(currentTime < lastFrameTime + player.getAttackHaste() + player.getAttackSpeed()/3) {
            frame = 0;
        } else if(currentTime < lastFrameTime + player.getAttackHaste() + 2 * player.getAttackSpeed()/3) {
            frame = 1;
        } else {
            frame = 0;
        }
    }

    SDL_FRect dstRect = {(float) player.getX() - camera.x, (float) player.getY() - camera.y, 32, 32};
    SDL_RenderTexture(renderer, animations[name][frame], nullptr, &dstRect);

    if(name == "boy_attack_" + player.getState() && frame == 1) {
        for(int i = 0; i < enemies.size(); i++) {
            if(enemies[i].isDamaged()) continue;
            float dx = enemies[i].getX() - player.getX();
            float dy = enemies[i].getY() - player.getY();
            float distance = sqrt(dx * dx + dy * dy);

            if (distance < player.getAttackRange()*2) {
                enemies[i].decreaseHP(player.getDMG());
                enemies[i].switchDamaged();
                if(enemies[i].isDead()) {
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }
}