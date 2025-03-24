#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>

extern SDL_Renderer* renderer;
std::map<std::string, std::vector<SDL_Texture*>> animations;

void loadAnimation(std::string name, int startFrame, int endFrame) {
    std::vector<SDL_Texture*> frames;
    for (int i = startFrame; i <= endFrame; i++) {
        std::string filename = "Img/" + name + "_" + std::to_string(i) + ".png";  
        SDL_Surface* tempSurface = IMG_Load(filename.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
        frames.push_back(texture);
    }
    animations[name] = frames;
}

void loadAllAnimation() {
    loadAnimation("player/boy_up", 1, 2);
    loadAnimation("player/boy_down", 1, 2);
    loadAnimation("player/boy_left", 1, 2);
    loadAnimation("player/boy_right", 1, 2);
    loadAnimation("player/boy_attack_up", 1, 2);
    loadAnimation("player/boy_attack_down", 1, 2);
    loadAnimation("player/boy_attack_left", 1, 2);
    loadAnimation("player/boy_attack_right", 1, 2);
    loadAnimation("mushroom/mushroom_run", 0, 7);
}