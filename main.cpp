#include "common.h"
#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include "init.cpp"
#include "image.cpp"
#include "grid.cpp"
#include "event.cpp"
#include "renderer.cpp"

using namespace std;

int main(int argc, char *args[]) {
    SDL_Window* window = init();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (renderer == NULL) {
        SDL_GetError();
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

     vector<Cell> grid = initGrid(renderer);

    SDL_Event e; 
    bool quit = false;

    while (!quit) {
        vector<MouseEvents> mouseEvents;
        
        handleQuitEvent(&e, quit, mouseEvents);
        clearRenderer(renderer);

        handleGridHover(grid, mouseEvents);
        handleGridClick(grid, mouseEvents);

        drawGrid(grid, renderer);

        SDL_RenderPresent(renderer);
    }

    close(window, renderer);
    
    return 0;
}