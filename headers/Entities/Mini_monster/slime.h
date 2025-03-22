#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "../../player.h"
#include "../../camera.h"
#include "../enemies.h"

extern SDL_Renderer* renderer;
extern Player player;
extern Camera camera;

class slime: public Enemy {
    
};