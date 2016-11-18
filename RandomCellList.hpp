//
// Created by Shane Kochvi on 11/12/16.
//

#ifndef MAZE_RANDOMDIRECTIONARRAY_HPP
#define MAZE_RANDOMDIRECTIONARRAY_HPP

#include "MazeBuilder.hpp"

const Coordinates UP{0, -1};
const Coordinates DOWN{0, 1};
const Coordinates LEFT{-1, 0};
const Coordinates RIGHT{1, 0};

class RandomCellList{

private:
    Coordinates directions[4]{UP, DOWN, LEFT, RIGHT};
    Cell* _currentCell;
    Cell*** _cellGrid;
    int _mazeWidth;
    int _mazeHeight;
public:

    /* Constructor */
    RandomCellList( Cell *&currentCell, Cell*** &cellGrid, int width, int height ){

        _currentCell = currentCell;
        _cellGrid = cellGrid;
        _mazeHeight = height;
        _mazeWidth = width;

        // Shuffle the directions array
        Coordinates temp;
        for( int i = 3; i>0; i--){

            int j = rand() % (i+1);
            temp = directions[i];
            directions[i] = directions[j];
            directions[j] = temp;

        }

          // For randomness tests
//        for( int j = 0; j<4; j++) {
//
//            if (directions[j].x == UP.x && directions[j].y == UP.y) {
//                positionList[0][j]++; }
//            if (directions[j].x == DOWN.x && directions[j].y == DOWN.y) {
//                positionList[1][j]++; }
//            if (directions[j].x == LEFT.x && directions[j].y == LEFT.y) {
//                positionList[2][j]++; }
//            if (directions[j].x == RIGHT.x && directions[j].y == RIGHT.y) {
//                positionList[3][j]++; }
//        }

    }

    /**
     * Some redundancy. Might use a stack
     * @return pointer to next cell
     */
    Cell* next(){

        int curX = _currentCell->location.x;
        int curY = _currentCell->location.y;

        // Select an unvisited cell
        Cell* nextCell;
        int nextX;
        int nextY;
        for (int k = 0; k < 4; ++k) {
            nextX = curX+directions[k].x;
            nextY = curY+directions[k].y;

            // Skip if out of range
            if( nextY < 0 || _mazeHeight <= nextY ){continue;}
            if( nextX < 0 || _mazeWidth <= nextX ){continue;}

            nextCell = _cellGrid[nextY][nextX];

            // Skip if already visited
            if(nextCell->visited){continue;}

            return nextCell;
        }
        return nullptr;
    }
};


#endif //MAZE_RANDOMDIRECTIONARRAY_HPP
