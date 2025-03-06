#include "grid.h"

void drawGrid(SDL_Renderer *renderer) {
    for (int i = 0; i <= SIZE; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_SIZE);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, WINDOW_SIZE, i * CELL_SIZE);
    }
}
