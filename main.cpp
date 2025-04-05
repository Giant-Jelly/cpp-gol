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
    cout << "Starting game..." << endl;
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
    bool step = false;
    bool run = false;
    while (!quit) {
        vector<MouseEvents> mouseEvents;
        vector<KeyboardEvents> keyboardEvents;
        
        
        handleEvents(&e, quit, mouseEvents, keyboardEvents);

        for (KeyboardEvents keyboardEvent : keyboardEvents) {
            if (keyboardEvent.space) {
                run = !run;
                cout << "run: " << run << endl;
            }

            if (keyboardEvent.right) {
                step = true;
                cout << "step: " << step << endl;
            }
        }

        clearRenderer(renderer);


        if (run || step) {
            calculateGeneration(grid);
        } else {
            handleGridHover(grid, mouseEvents);
            handleGridClick(grid, mouseEvents);
        }

        drawGrid(grid, renderer);

        step = false;
        SDL_RenderPresent(renderer);
    }

    close(window, renderer);
    
    return 0;
}