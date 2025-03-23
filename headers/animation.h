#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>

extern SDL_Renderer* renderer;
std::map<std::string, std::vector<SDL_Texture*>> animations;

void loadAnimation(std::string name, int numFrames) {
    std::vector<SDL_Texture*> frames;
    for (int i = 1; i <= numFrames; i++) {
        std::string filename = "Img/player/" + name + "_" + std::to_string(i) + ".png";  
        SDL_Surface* tempSurface = IMG_Load(filename.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_DestroySurface(tempSurface);
        frames.push_back(texture);
    }
    animations[name] = frames;
}

void loadAllAnimation() {
    loadAnimation("boy_up", 2);
    loadAnimation("boy_down", 2);
    loadAnimation("boy_left", 2);
    loadAnimation("boy_right", 2);
    loadAnimation("boy_attack_up", 2);
    loadAnimation("boy_attack_down", 2);
    loadAnimation("boy_attack_left", 2);
    loadAnimation("boy_attack_right", 2);
}