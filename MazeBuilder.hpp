//
// Created by Shane Kochvi on 11/11/16.
//

#ifndef MAZE_MAZEBUILDER_HPP
#define MAZE_MAZEBUILDER_HPP

#include <utility>
#include <stdbool.h>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <string>
#include <time.h>

//static int positionList[4][4]; // For testing randomness

struct Coordinates {
    int x;
    int y;
};

struct Cell {
    Coordinates location;
    bool visited;
    Cell(int x, int y, bool visited ){
        location.x = x;
        location.y = y;
        this->visited = visited;
    }
};

class MazeBuilder {

private:

    char **_charGrid;

    Cell ***_cellGrid;

    int _mazeWidth;
    int _mazeHeight;
    int _mazeCount;

    int _charGridWidth;
    int _charGridHeight;

    Coordinates _startChar{0,0};
    Coordinates _endChar{0,0};

public:

    /**
     * Constructor
     */
    MazeBuilder(int, int, int);

    /**
     * Refresh grids for a new maze.
     */
    void refreshGrids();

    /**
     * Builds the mazes, man.
     */
    void buildMazeStart();

    /**
     * Recursive method for building a maze.
     * @param nextCell the next cell to be recursed into
     */
    void buildMaze(Cell *nextCell);

    /**
     * Prints character grid
     * @param num maze number
     */
    void printCharGrid(int num);

    /**
     * Updates character grid after a move.
     * @param cell_1 one cell
     * @param cell_2 two cell
     */
    void updateCharGrid(Cell *cell_1, Cell *cell_2);

};


#endif //MAZE_MAZEBUILDER_HPP
