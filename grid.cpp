#include "common.h"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <list>
#include "event.h"
#include <map>

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

map<vector<int>, Cell*> gridAsMap(vector<Cell> grid) {
    map<vector<int>, Cell*> gridMap;
    for (Cell &cell : grid) {
        gridMap[{cell.x, cell.y}] = &cell;
    }
    return gridMap;
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
                mouseEvent.x > cell.x && 
                mouseEvent.x <= cell.x + cell.w && 
                mouseEvent.y > cell.y && 
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
                mouseEvent.x > cell.x && 
                mouseEvent.x <= cell.x + cell.w && 
                mouseEvent.y > cell.y && 
                mouseEvent.y <= cell.y + cell.h
            ) {
                cout << "cell clicked: " << cell.x << " " << cell.y << endl;
                cell.isAlive = !cell.isAlive;
            }
        }
    }
}

Cell* getCellFromGrid(vector<Cell> grid, int x, int y) {
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT) {
        return NULL;
    }

    for (Cell &cell : grid) {
        if (cell.x == x && cell.y == y) {
            return &cell;
        }
    }
    return NULL;
}

int getAliveNeighborCount(map<vector<int>, Cell*> gridMap, Cell cell) {
    list<Cell*> neighbors;
    // neighbors.push_back(getCellFromGrid(grid, cell.x-CELL_SIZE, cell.y-CELL_SIZE));
    // neighbors.push_back(getCellFromGrid(grid, cell.x, cell.y-CELL_SIZE));
    // neighbors.push_back(getCellFromGrid(grid, cell.x+CELL_SIZE, cell.y-CELL_SIZE));
    // neighbors.push_back(getCellFromGrid(grid, cell.x-CELL_SIZE, cell.y));
    // neighbors.push_back(getCellFromGrid(grid, cell.x+CELL_SIZE, cell.y));
    // neighbors.push_back(getCellFromGrid(grid, cell.x-CELL_SIZE, cell.y+CELL_SIZE));
    // neighbors.push_back(getCellFromGrid(grid, cell.x, cell.y+CELL_SIZE));
    // neighbors.push_back(getCellFromGrid(grid, cell.x+CELL_SIZE, cell.y+CELL_SIZE));

    neighbors.push_back(gridMap[{cell.x-CELL_SIZE, cell.y-CELL_SIZE}]);
    neighbors.push_back(gridMap[{cell.x, cell.y-CELL_SIZE}]);
    neighbors.push_back(gridMap[{cell.x+CELL_SIZE, cell.y-CELL_SIZE}]);
    neighbors.push_back(gridMap[{cell.x-CELL_SIZE, cell.y}]);
    neighbors.push_back(gridMap[{cell.x+CELL_SIZE, cell.y}]);
    neighbors.push_back(gridMap[{cell.x-CELL_SIZE, cell.y+CELL_SIZE}]);
    neighbors.push_back(gridMap[{cell.x, cell.y+CELL_SIZE}]);
    neighbors.push_back(gridMap[{cell.x+CELL_SIZE, cell.y+CELL_SIZE}]);
    

    int aliveNeighborCount = 0;
    for (Cell* neighbor : neighbors) {
        if (neighbor == NULL) {
            continue;
        }

        if (neighbor->isAlive) {
            aliveNeighborCount++;
        }
    }
    return aliveNeighborCount;
}

/*
RULES:
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, 
live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, 
vertically, or diagonally adjacent. At each step in time, the following transitions occur:

Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

The initial pattern constitutes the seed of the system. The first generation is created by applying 
the above rules simultaneously to every cell in the seed, live or dead; births and deaths occur simultaneously, 
and the discrete moment at which this happens is sometimes called a tick.[nb 1] Each generation is a pure function of the preceding one. 
The rules continue to be applied repeatedly to create further generations.
*/

void calculateGeneration(vector<Cell> &grid) {
    map<vector<int>, Cell*> gridMap = gridAsMap(grid);
    vector<Cell> newGrid;
    for (Cell cell : grid) {
        Cell* neighbor = gridMap[{cell.x-CELL_SIZE, cell.y-CELL_SIZE}];
        if (neighbor != NULL) {
            cout << "neighbor: " << neighbor->x << " " << neighbor->y << endl;
        }
        // int aliveNeighbors = getAliveNeighborCount(gridMap, cell);

        // if (aliveNeighbors < 2) {
        //     cell.isAlive = false;
        // }

        // if (aliveNeighbors > 3) {
        //     cell.isAlive = false;
        // }

        // if (aliveNeighbors == 3) {
        //     cell.isAlive = true;
        // }

        newGrid.push_back(cell);
    }

    grid = newGrid;
}