#include "common.h"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "event.h"

using namespace std;

class Cell {
    public:
        int x;
        int y;
        int w;
        int h;
        SDL_Color borderColor = {0xFF, 0xFF, 0xFF, 0xFF};
        SDL_Color deadColor = {0x00, 0x00, 0x00, 0xFF};
        SDL_Color aliveColor = {0xFF, 0xFF, 0xFF, 0xFF};
        SDL_Color hoveredColor = {0x70, 0x70, 0x70, 0xFF};
        bool isAlive = false;
        bool isHovered = false;

        Cell(int x, int y, int w, int h) {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }

        void draw(SDL_Renderer* renderer) {
            SDL_Rect rect = {x, y, w, h};
            if (isAlive) {  
                SDL_SetRenderDrawColor(renderer, aliveColor.r, aliveColor.g, aliveColor.b, aliveColor.a);
            } else if (isHovered) {
                SDL_SetRenderDrawColor(renderer, hoveredColor.r, hoveredColor.g, hoveredColor.b, hoveredColor.a);
            } else {
                SDL_SetRenderDrawColor(renderer, deadColor.r, deadColor.g, deadColor.b, deadColor.a);
            }
            
            SDL_RenderFillRect(renderer, &rect);
            // Draw border
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_RenderDrawRect(renderer, &rect);
        }
};

vector<Cell> initGrid(SDL_Renderer* renderer) {
    vector<Cell> grid;
    for (int i = 0; i < SCREEN_WIDTH / CELL_SIZE; i++) {
        for (int j = 0; j < SCREEN_HEIGHT / CELL_SIZE; j++) {
            Cell cell(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            grid.push_back(cell);
        }
    }

    return grid;
}

void drawGrid(vector<Cell> grid, SDL_Renderer* renderer) {
    for (Cell cell : grid) {
        cell.draw(renderer);
    }
}

void handleGridHover(vector<Cell> &grid, vector<MouseEvents> &mouseEvents) {
    for (Cell &cell : grid) {
        for (MouseEvents mouseEvent : mouseEvents) {
            if (
                mouseEvent.x >= cell.x && 
                mouseEvent.x <= cell.x + cell.w && 
                mouseEvent.y >= cell.y && 
                mouseEvent.y <= cell.y + cell.h
            ) {
                cell.isHovered = true;
            } else {
                cell.isHovered = false;
            }
        }
    }
}

void handleGridClick(vector<Cell> &grid, vector<MouseEvents> &mouseEvents) {
    for (Cell &cell : grid) {
        for (MouseEvents mouseEvent : mouseEvents) {
            if (
                mouseEvent.mouseDown &&
                mouseEvent.x >= cell.x && 
                mouseEvent.x <= cell.x + cell.w && 
                mouseEvent.y >= cell.y && 
                mouseEvent.y <= cell.y + cell.h
            ) {
                cell.isAlive = !cell.isAlive;
            }
        }
    }
}