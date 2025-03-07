#include "grid.h"

void drawGrid(SDL_Renderer *renderer) {
    for (int i = 0; i <= SIZE; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE + 800, 400, i * CELL_SIZE+800, SIZE*CELL_SIZE+400);
        SDL_RenderDrawLine(renderer, 800, i * CELL_SIZE + 400,SIZE*CELL_SIZE+800, i * CELL_SIZE+400);
    }
}
