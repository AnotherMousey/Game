#pragma once
#include "SDL3/SDL.h"

extern const int entitySize;

struct Camera {
    int x = 0, y = 0;
    int width, height;

    Camera(int w, int h) {
        width = w;
        height = h;
    }

    void reposition(int player_x, int player_y) {
        x = player_x - width/2;
        y = player_y - height/2;

        if(x < 0) x = 0;
        if(y < 0) y = 0;
        if(x > 4000 - width) x = 4000 - width;
        if(y > 4000 - height) y = 4000 - height;
    }
};