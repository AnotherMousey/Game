#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL2 Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture* renderText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return texture;
}

enum MenuOption { START, OPTIONS, EXIT, TOTAL_OPTIONS };
int selectedOption = 0;

void handleInput(bool &running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    selectedOption = (selectedOption - 1 + TOTAL_OPTIONS) % TOTAL_OPTIONS;
                    break;
                case SDLK_DOWN:
                    selectedOption = (selectedOption + 1) % TOTAL_OPTIONS;
                    break;
                case SDLK_RETURN:
                    if (selectedOption == EXIT) {
                        running = false;
                    } else {
                        std::cout << "Selected option: " << selectedOption << std::endl;
                    }
                    break;
            }
        }
    }
}

void renderMenu(TTF_Font* font) {
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0};

    const std::string options[TOTAL_OPTIONS] = {"Start Game", "Options", "Exit"};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < TOTAL_OPTIONS; ++i) {
        SDL_Color color = (i == selectedOption) ? red : white;
        SDL_Texture* texture = renderText(options[i], font, color, renderer);
        if (!texture) continue;

        int textWidth, textHeight;
        SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect renderQuad = {SCREEN_WIDTH / 2 - textWidth / 2, 200 + i * 50, textWidth, textHeight};

        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[]) {
    if (!init()) return -1;

    TTF_Font* font = TTF_OpenFont("arial.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    bool running = true;
    while (running) {
        handleInput(running);
        renderMenu(font);
        SDL_Delay(100);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}
