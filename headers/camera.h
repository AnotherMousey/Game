#pragma once
#include "SDL2/SDL.h"
#include <iostream>

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
    }
};