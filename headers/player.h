#pragma once
#include <iostream>
#include <SDL2/SDL.h>

extern const int width;
extern const int height;

struct Player {
    int x = width/2, y = height/2;
    int speed = 4;

    void reset() {
        x = width/2;
        y = height/2;
    }

    void increaseSpeed(int amount) {
        speed += amount; 
    }

    void move(const Uint8* keystate) {
        int dx = 0, dy = 0;
    
        if (keystate[SDL_SCANCODE_W]) dy -= speed;
        if (keystate[SDL_SCANCODE_S]) dy += speed;
        if (keystate[SDL_SCANCODE_A]) dx -= speed;
        if (keystate[SDL_SCANCODE_D]) dx += speed;

        // Normalize diagonal movement to prevent faster diagonal speed
        if (dx != 0 && dy != 0) {
            dx = (dx / abs(dx)) * (speed / 1.414);
            dy = (dy / abs(dy)) * (speed / 1.414);
        }

        x += dx;
        y += dy;

        if(x < 0) x = 0;
        if(y < 0) y = 0;
        if(x >= 4000) x = 3999;
        if(y >= 4000) y = 3999;
    }
};