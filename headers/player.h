#pragma once
#include <iostream>
#include <SDL3/SDL.h>

extern const int width;
extern const int height;
extern SDL_Renderer* renderer;

struct Player {
    int x = width/2, y = height/2;
    int speed = 20;
    static const int maxhp = 100;
    int hp = 100;

    const int HP_BAR_WIDTH = 300;
    const int HP_BAR_HEIGHT = 30;
    const int HP_BAR_X = 80;      
    const int HP_BAR_Y = 20; 

    void reset() {
        x = width/2;
        y = height/2;
        hp = maxhp;
    }

    void increaseSpeed(int amount) {
        speed += amount; 
    }

    void move(const bool* keystate) {
        int dx = 0, dy = 0;
    
        if (keystate[SDL_SCANCODE_W]) dy -= speed;
        if (keystate[SDL_SCANCODE_S]) dy += speed;
        if (keystate[SDL_SCANCODE_A]) dx -= speed;
        if (keystate[SDL_SCANCODE_D]) dx += speed;

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

    
void renderHPBar() {
    float hpPercent = (float) hp / maxhp;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect h1 = { 20, HP_BAR_Y, 8, 24 };   // Left line of H
    SDL_Rect h2 = { 40, HP_BAR_Y, 8, 24 };   // Right line of H
    SDL_Rect h3 = { 20, HP_BAR_Y + 10, 28, 6 }; // Middle bar of H
    SDL_Rect p1 = { 60, HP_BAR_Y, 8, 24 };   // Left line of P
    SDL_Rect p2 = { 60, HP_BAR_Y, 20, 8 };   // Top bar of P
    SDL_Rect p3 = { 60, HP_BAR_Y + 12, 20, 8 }; // Mid bar of P

    SDL_RenderFillRect(renderer, &h1);
    SDL_RenderFillRect(renderer, &h2);
    SDL_RenderFillRect(renderer, &h3);
    SDL_RenderFillRect(renderer, &p1);
    SDL_RenderFillRect(renderer, &p2);
    SDL_RenderFillRect(renderer, &p3);

    SDL_Rect bgRect = { HP_BAR_X, HP_BAR_Y, HP_BAR_WIDTH, HP_BAR_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &bgRect);

    SDL_Rect hpRect = { HP_BAR_X, HP_BAR_Y, (int)(HP_BAR_WIDTH * hpPercent), HP_BAR_HEIGHT };
    if (hpPercent > 0.8)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (hpPercent > 0.5)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    else if (hpPercent > 0.2)
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &hpRect);

    int numX = HP_BAR_X + HP_BAR_WIDTH + 20;
    for (char digit : std::to_string(hp)) {
        SDL_Rect numRect = { numX, HP_BAR_Y, 15, 24 };
        SDL_RenderFillRect(renderer, &numRect);
        numX += 15;
    }
}
};