#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "text.h"

extern const int width;
extern const int height;
extern SDL_Renderer* renderer;

enum playerState {
    Idle,
    Down,
    Up,
    Left,
    Right
};

class Player {
    private:
        int x = width/2, y = height/2;
        int speed = 20;
        static const int maxhp = 100;
        int hp = 100;
        playerState state = Idle;

    public:
        int getX() {return x;}
        int getY() {return y;}

        int getHP() {return hp;}
        void decreaseHP(int amount) {hp -= amount;}
        void increaseHP(int amount) {hp += amount;}

        std::string getState() {
            switch(state) {
                case Idle: return "boy_down";
                case Down: return "boy_down";
                case Up: return "boy_up";
                case Left: return "boy_left";
                case Right: return "boy_right";
                default: return "unknown state";
            }
        }
        
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
        
            if (keystate[SDL_SCANCODE_W]) dy -= speed, state = Up;
            else if (keystate[SDL_SCANCODE_S]) dy += speed, state = Down;
            else if (keystate[SDL_SCANCODE_A]) dx -= speed, state = Left;
            else if (keystate[SDL_SCANCODE_D]) dx += speed, state = Right;
            else state = Idle;

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
            TTF_Font* hpfont = TTF_OpenFont("Fonts/Commissioner-Medium.ttf", 24);
            
            const float barWidth = 400, barHeight = 35;
            const float x = 60, y = 10;
            float hpWidth = (hp / (float) maxhp) * barWidth;
        
            SDL_Color white = {255, 255, 255, 255};
            renderText(hpfont, "HP:", 10, y, white);
        
            SDL_FRect bgRect = { x, y, barWidth, barHeight };
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(renderer, &bgRect);
        
            SDL_FRect hpRect = { x, y, hpWidth, barHeight };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &hpRect);
    
            std::string hpText = std::to_string(hp) + " / " + std::to_string(maxhp);
            renderText(hpfont, hpText.c_str(), x + barWidth - 120, y, white);
        }
};