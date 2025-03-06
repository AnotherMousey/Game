#ifndef GRID_H
#define GRID_H

#include "SDL2/SDL.h"  // Include SDL2 from the correct path

#define SIZE 9
#define CELL_SIZE 50
#define WINDOW_SIZE (SIZE * CELL_SIZE)

void drawGrid(SDL_Renderer *renderer);

#endif // GRID_H
