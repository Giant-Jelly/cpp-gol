#include <SDL2/SDL.h>
#include <iostream>
#include "common.h"

using namespace std;

SDL_Window* init() {
    // Get current time
    time_t now = time(0);
    cout << "Initializing SDL at " << now << endl;
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    now = time(0);
    cout << "SDL initialized at " << now << endl;
    return window;
}

void close(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
