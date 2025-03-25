#pragma once
#include <string>
#include <SDL3/SDL.h> 
#include "text.h"

extern SDL_Renderer *renderer;

struct Button {
    SDL_FRect rect;
    SDL_Color color;
    SDL_Color hoverColor;
    std::string message;
    bool hovered;

    Button(int x, int y, std::string msg): rect{(float) x, (float) y, 200, 100}, color({0, 128, 255, 255}), hoverColor({0, 200, 255, 255}), hovered(false), message(msg) {}

    void render() {
        if (hovered) {
            SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        } else {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        }
        SDL_RenderFillRect(renderer, &rect);
        TTF_Font* buttonfont = TTF_OpenFont("Fonts/Commissioner-Bold.ttf", 24);

        renderText(buttonfont, message.c_str(), rect.x+72, rect.y+36, {0, 0, 0, 255});
    }

    bool isInside(int mx, int my) {
        return (mx >= rect.x && mx <= rect.x + rect.w &&
                my >= rect.y && my <= rect.y + rect.h);
    }
};