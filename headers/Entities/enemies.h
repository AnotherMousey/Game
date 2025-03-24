#pragma once
#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include "../player.h"
#include "../camera.h"

extern SDL_Renderer* renderer;
extern Camera camera;
extern Player player;

class Enemy {
    protected:
        int x, y;
        int speed;
        int hp, maxhp;
        int dmg;
        int lastDamageTime = 0;
        int size;
        bool Damaged = false;

    public:
        Enemy(int x, int y) : x(x), y(y) {}

        int getX() {return x;}
        int getY() {return y;}

        int getLastDamageTime() {return lastDamageTime;}
        void setLastDamageTime(int time) {lastDamageTime = time;}

        void decreaseHP(int amount) {hp -= amount;}

        int getDMG() {return dmg;}

        bool isDead() {return hp <= 0;}

        bool isDamaged() {return Damaged;}
        void switchDamaged() {Damaged = !Damaged;}

        int getSize() {return size;}

        void move() {
            int dx = player.getX() - x + player.getSize() - size;
            int dy = player.getY() - y + player.getSize() - size;
            float length = sqrt(dx * dx + dy * dy);
            if (length > 0) {
                x += dx / length * speed;
                y += dy / length * speed;
            }

        }

        virtual void render() {}
};
