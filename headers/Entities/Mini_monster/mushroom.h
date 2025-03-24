#pragma once
#include <vector>
#include <string> 
#include <iostream>
#include <map>
#include <SDL3/SDL.h>
#include "../../animation.h"
#include "../../camera.h"

extern SDL_Renderer* renderer;
extern const int entitySize;
extern std::map<std::string, std::vector<SDL_Texture*>> animations;
extern Camera camera;

class mushroom: public Enemy {
    public:
        mushroom(int x, int y, int speed, int hp, int dmg): Enemy(x, y, speed, hp, dmg) {}

        void render() override {
            int delayTime = 150;
            int frame = (SDL_GetTicks() / delayTime) % 8;
            SDL_FRect dstrect = {(float) x - camera.x, (float) y - camera.y, (float) entitySize*2, (float) entitySize*2};
            int dx = x - player.getX();
            if(dx >= 0) {
                SDL_RenderTexture(renderer, animations["mushroom/mushroom_run"][frame], nullptr, &dstrect);
            } else {
                SDL_RenderTextureRotated(renderer, animations["mushroom/mushroom_run"][frame], nullptr, &dstrect, 0, nullptr, SDL_FLIP_HORIZONTAL);
            }
        }
};