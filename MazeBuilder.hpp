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

    std::stack<Cell*> _cellStack;

    char **_charGrid;

    Cell ***_cellGrid;

    int _mazeWidth;
    int _mazeHeight;
    int _mazeCount;

public:

    /**
     * Constructor
     */
    MazeBuilder(int, int, int);

    /**
     *
     * Refresh grids for a new maze.
     */
    void refreshGrids();

    /**
     * Builds the mazes, man.
     */
    void buildMazes();

    /**
     * Recursive method for building a maze.
     * @param nextCell the next cell to be recursed into
     */
    void buildMaze(Cell *nextCell);


    void printCharGrid(int num);


    void updateCharGrid(Cell *cell_1, Cell *cell_2);

};


#endif //MAZE_MAZEBUILDER_HPP
