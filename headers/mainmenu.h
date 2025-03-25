#pragma once
#include <SDL3/SDL.h>
#include "button.h"

Button playButton(860, 400, "PLAY");
Button quitButton(860, 600, "QUIT");

void updateMainMenu(float mouseX, float mouseY) {
    playButton.hovered = playButton.isInside(mouseX, mouseY);
    quitButton.hovered = quitButton.isInside(mouseX, mouseY);
}

void runMainMenu() {
    playButton.render();
    quitButton.render();
}