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
extern const int entitySize;
extern std::vector <Enemy*> enemies;
extern std::map<std::string, std::vector<SDL_Texture*>> animations;

void playerAnimationAndAttack() {
    static int lastFrameTime = 0;
    static int frame = 0;
    int dmgState = 0;

    int currentTime = SDL_GetTicks();
    static std::string name;

    if(currentTime < lastFrameTime + player.getAttackHaste()) {
        name = "player/boy_" + player.getState();
        if(currentTime < lastFrameTime + player.getAttackHaste()/2) {
            frame = 0;
        } else {
            frame = 1;
        }
    } else if(currentTime >= lastFrameTime + player.getAttackHaste() + player.getAttackSpeed()) {
        lastFrameTime = currentTime;
        for(int i = 0; i < enemies.size(); i++) {
            if(enemies[i]->isDamaged()) enemies[i]->switchDamaged();
        }
    } else {
        name = "player/boy_attack_" + player.getState();
        if(currentTime < lastFrameTime + player.getAttackHaste() + player.getAttackSpeed()/3) {
            frame = 0;
        } else if(currentTime < lastFrameTime + player.getAttackHaste() + 2 * player.getAttackSpeed()/3) {
            frame = 1;
        } else {
            frame = 0;
        }
    }

    float pwidth = entitySize, pheight = entitySize;
    float posx = player.getX() - camera.x, posy = player.getY() - camera.y;

    if(name == "player/boy_attack_" + player.getState()) {
        if(player.getState() == "left" || player.getState() == "right") {
            pwidth = pwidth*2;
            pheight = pheight;
            if(player.getState() == "left") {
                posx -= entitySize;
            }
        } else {
            pwidth = pwidth;
            pheight = pheight*2;
            if(player.getState() == "up") {
                posy -= entitySize;
            }
        }
    }

    SDL_FRect dstRect = {posx, posy, pwidth, pheight};
    SDL_RenderTexture(renderer, animations[name][frame], nullptr, &dstRect);

    if(name == "player/boy_attack_" + player.getState() && frame == 1) {
        for(int i = 0; i < enemies.size(); i++) {
            if(enemies[i]->isDamaged()) continue;
            float dx = enemies[i]->getX() - player.getX();
            float dy = enemies[i]->getY() - player.getY();
            
            bool check = false;
            if(player.getState() == "left") {
                if(dx < 0 && dx > -entitySize - player.getAttackRange() && dy < entitySize && dy > -entitySize) {
                    check = true;
                }
                
            } else if(player.getState() == "right") {
                if(dx > 0 && dx < entitySize + player.getAttackRange() && dy < entitySize && dy > -entitySize) {
                    check = true;
                }
            } else if(player.getState() == "up") {
                if(dy < 0 && dy > -entitySize - player.getAttackRange() && dx < entitySize && dx > -entitySize) {
                    check = true;
                }
            } else {
                if(dy > 0 && dy < entitySize + player.getAttackRange() && dx < entitySize && dx > -entitySize) {
                    check = true;
                }
            }

            if (check) {
                enemies[i]->decreaseHP(player.getDMG());
                enemies[i]->switchDamaged();
                if(enemies[i]->isDead()) {
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }
}