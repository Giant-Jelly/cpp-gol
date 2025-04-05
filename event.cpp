#include <SDL2/SDL.h>

#ifndef EVENT_H
#define EVENT_H 

class MouseEvents {
    public:
        bool mouseDown = false;
        int x = 0;
        int y = 0;
};

#endif

void handleQuitEvent(SDL_Event* e, bool &quit, vector<MouseEvents> &mouseEvents) {
    while (SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            quit = true;
            continue;
        }

        if (e->type == SDL_MOUSEBUTTONDOWN) {
            MouseEvents mouseEvent;
            mouseEvent.mouseDown = true;
            SDL_GetMouseState(&mouseEvent.x, &mouseEvent.y);
            mouseEvents.push_back(mouseEvent);
            continue;
        }
        
        if (e->type == SDL_MOUSEMOTION) {
            MouseEvents mouseEvent;
            SDL_GetMouseState(&mouseEvent.x, &mouseEvent.y);
            mouseEvents.push_back(mouseEvent);
            continue;
        }
    }
}