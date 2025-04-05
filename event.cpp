#include <SDL2/SDL.h>

#ifndef EVENT_H
#define EVENT_H 

class MouseEvents {
    public:
        bool mouseDown = false;
        int x = 0;
        int y = 0;
};

class KeyboardEvents {
    public:
        bool space = false;
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
};
#endif

void handleEvents(SDL_Event* e, bool &quit, vector<MouseEvents> &mouseEvents, vector<KeyboardEvents> &keyboardEvents) {
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

        if (e->type == SDL_KEYDOWN) {
            cout << "key down" << e->key.keysym.sym << endl;
            KeyboardEvents keyboardEvent;
            if (e->key.keysym.sym == SDLK_SPACE) {
                keyboardEvent.space = true;
            }

            if (e->key.keysym.sym == SDLK_RIGHT) {
                keyboardEvent.right = true;
            }

            if (e->key.keysym.sym == SDLK_UP) {
                keyboardEvent.up = true;
            }

            if (e->key.keysym.sym == SDLK_DOWN) {
                keyboardEvent.down = true;
            }

            if (e->key.keysym.sym == SDLK_LEFT) {
                keyboardEvent.left = true;
            }   

            keyboardEvents.push_back(keyboardEvent);
            continue;
        }
    }
}