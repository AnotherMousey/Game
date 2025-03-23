#pragma once
#include <cmath>
#include <SDL3/SDL.h>
#include "../player.h"
#include "../camera.h"

extern SDL_Renderer* renderer;
extern Camera camera;
extern Player player;

class Enemy {
    private:
        int x, y;
        int speed;
        int hp, maxhp;
        int dmg;
        int lastDamageTime = 0;
        bool Damaged = false;

    public:
        Enemy(int x, int y, int speed, int maxhp, int dmg) : x(x), y(y), speed(speed), maxhp(maxhp), hp(maxhp), dmg(dmg) {}

        int getX() {return x;}
        int getY() {return y;}

        int getLastDamageTime() {return lastDamageTime;}
        void setLastDamageTime(int time) {lastDamageTime = time;}

        void decreaseHP(int amount) {hp -= amount;}

        int getDMG() {return dmg;}

        bool isDead() {return hp <= 0;}

        bool isDamaged() {return Damaged;}
        void switchDamaged() {Damaged = !Damaged;}

        void move() {
            int dx = player.getX() - x;
            int dy = player.getY() - y;
            float length = sqrt(dx * dx + dy * dy);
            if (length > 0) {
                x += dx / length * speed;
                y += dy / length * speed;
            }
        }

        void render() {
            SDL_FRect rectF = { (float) x - camera.x, (float) y - camera.y, 32, 32 };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rectF);
        }
};
