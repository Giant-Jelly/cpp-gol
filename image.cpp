#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

SDL_Surface* loadMedia(char* path) {
    SDL_Surface* image = SDL_LoadBMP(path);
    if (image == NULL) {
        cout << "Unable to load image" << SDL_GetError() << endl;
        return NULL;
    }
    
    return image;
}


void drawImage(SDL_Window* window, SDL_Surface* image, SDL_Surface* screenSurface) {
    SDL_BlitSurface(image, NULL, screenSurface, NULL);
    SDL_UpdateWindowSurface(window);
}
