#pragma once
#include <vector>
#include <string> 
#include <iostream>
#include <map>
#include <SDL3/SDL.h>
#include "../../animation.h"
#include "../../camera.h"

extern SDL_Renderer* renderer;
extern std::map<std::string, std::vector<SDL_Texture*>> animations;
extern Camera camera;

class mushroom: public Enemy {
    public:
        mushroom(int x, int y, int speed, int hp, int dmg): Enemy(x, y, speed, hp, dmg) {}

        void render() override {
            std::cout << "rendering mushroom" << std::endl;

            int delayTime = 150;
            int frame = (SDL_GetTicks() / delayTime) % 8;
            SDL_FRect dstrect = {(float) x - camera.x, (float) y - camera.y, 64, 64};
            SDL_RenderTexture(renderer, animations["mushroom/mushroom_run"][frame], nullptr, &dstrect);
        }
};