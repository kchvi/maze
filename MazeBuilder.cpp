//
// Created by Shane Kochvi on 11/11/16.
//

#include <iostream>
#include <fstream>
#include "MazeBuilder.hpp"
#include "RandomCellList.hpp"

#include <iomanip>

#define DOUBLE_WIDTH 0

MazeBuilder::MazeBuilder(int width, int height, int count) {

    // prevent repetition between runs
    srand((unsigned int) time(NULL));

    _mazeHeight = height;
    _mazeWidth = width;
    _mazeCount = count;

    // Initialize node grid
    _cellGrid = new Cell **[_mazeHeight];
    for (int y = 0; y < _mazeHeight; y++) {
        _cellGrid[y] = new Cell *[_mazeWidth];
        for (int x = 0; x < _mazeWidth; x++) {
            _cellGrid[y][x] = new Cell{x, y, false};
        }
    }

    // Initialize character grid
#if DOUBLE_WIDTH
    _charGridWidth = 4 * _mazeWidth + 2;
    _startChar.x = 2;
    _endChar.x = _charGridWidth - 3;
#else
    _charGridWidth = 2*_mazeWidth+1;
    _startChar.x = 1;
    _endChar.x = _charGridWidth-2;
#endif
    _charGridHeight = 2 * _mazeHeight + 1;
    _startChar.y = _charGridHeight - 1;
    _endChar.y = 0;

    _charGrid = new char *[_charGridHeight];
    for (int y = 0; y < _charGridHeight; y++) {
        _charGrid[y] = new char[_charGridWidth];
    }
}

void MazeBuilder::refreshGrids() {

    // Re-initialize node grid
    for (int y = 0; y < _mazeHeight; y++) {
        for (int x = 0; x < _mazeWidth; x++) {
            _cellGrid[y][x]->visited = false;
        }
    }

    // Re-initialize character grid
    for (int y = 0; y < _charGridHeight; y++) {
        for (int x = 0; x < _charGridWidth; x++) {
            _charGrid[y][x] = '#';
        }
    }

    // Add start and end characters
    _charGrid[_startChar.y][_startChar.x] = '@';
    _charGrid[_endChar.y][_endChar.x] = '*';

}

void MazeBuilder::buildMazeStart() {

    for (int i = 0; i < _mazeCount; i++) {

        int x = rand() % _mazeWidth;
        int y = rand() % _mazeHeight;
        Cell *startCell = _cellGrid[y][x]; // Just to start
        refreshGrids();
        buildMaze(startCell);
        printCharGrid(i);

    }
}


void MazeBuilder::buildMaze(Cell *currentCell) {

    currentCell->visited = true;

    RandomCellList *cells = new RandomCellList(currentCell, _cellGrid, _mazeWidth, _mazeHeight);

    Cell *nextCell = cells->next();

    while (nextCell != nullptr) {

        updateCharGrid(currentCell, nextCell);
        buildMaze(nextCell);
        nextCell = cells->next();

    }

    delete cells;
}


void MazeBuilder::printCharGrid(int count) {

    std::string path("/Users/shanekochvi/ClionProjects/maze/mazes/");
    path += "maze_";
    path += std::to_string(_mazeWidth);
    path += "x";
    path += std::to_string(_mazeHeight);
    path += "_";
    path += std::to_string(count);

    std::ofstream outfile(path);

    //Print height and width
    outfile << _charGridWidth << std::endl;
    outfile << _charGridHeight << std::endl;

    // Print character grid
    for (int y = 0; y < _charGridHeight; y++) {
        for (int x = 0; x < _charGridWidth; x++) {
            outfile << _charGrid[y][x];
        }
        outfile << std::endl;
    }

    outfile.close();

    // Tests for randomness
//    for (int h = 0; h < 4; h++) {
//
//        if (h == 0) { std::cout << "UP:    " << "\n"; }
//        if (h == 1) { std::cout << "DOWN:  " << "\n"; }
//        if (h == 2) { std::cout << "LEFT:  " << "\n"; }
//        if (h == 3) { std::cout << "RIGHT: " << "\n"; }
//
//        for (int i = 0; i < 4; i++) {
//            std::cout << "\t" << i << " :" << positionList[h][i] << "\n";
//
//            float avg = 0;
//            for (int j = 0; j < 4; j++) {
//                if (j == i) { continue; }
//                avg += positionList[h][j];
//            }
//            avg = (float) avg / 3;
//
//            std::cout << "\t" << positionList[h][i] << "\n";
//            std::cout << "\t\tvariance: " << positionList[h][i] - avg << std::endl;
//            std::cout << std::fixed;
//            std::cout << std::setprecision(7);
//            std::cout << "\t\t          " << 100*(positionList[h][i] - avg)/positionList[h][i] <<"%"<< std::endl;
//
//        }
//
//    }

}

void MazeBuilder::updateCharGrid(Cell *cell1, Cell *cell2) {


#if DOUBLE_WIDTH
    // Cell 1 char grid update
    int cell1CharX = (cell1->location.x * 4) + 2;
    int cell1CharY = (cell1->location.y * 2) + 1;
    _charGrid[cell1CharY][cell1CharX] = '_';
    _charGrid[cell1CharY][cell1CharX + 1] = '_';

    // Cell 2 char grid update
    int cell2CharX = (cell2->location.x * 4) + 2;
    int cell2CharY = (cell2->location.y * 2) + 1;
    _charGrid[cell2CharY][cell2CharX] = '_';
    _charGrid[cell2CharY][cell2CharX + 1] = '_';

    // Wall grid update, get average value for x and y each.
    int wallX = (cell1CharX + cell2CharX) / 2;
    int wallY = (cell1CharY + cell2CharY) / 2;
    _charGrid[wallY][wallX] = '_';
    _charGrid[wallY][wallX + 1] = '_';
#else
    // Cell 1 char grid update
    int cell1CharX = (cell1->location.x*2)+1;
    int cell1CharY = (cell1->location.y*2)+1;
    _charGrid[cell1CharY][cell1CharX] = '_';

    // Cell 2 char grid update
    int cell2CharX = (cell2->location.x*2)+1;
    int cell2CharY = (cell2->location.y*2)+1;
    _charGrid[cell2CharY][cell2CharX] = '_';

    // Wall grid update, get average value for x and y each.
    int wallX = (cell1CharX+cell2CharX)/2;
    int wallY = (cell1CharY+cell2CharY)/2;
    _charGrid[wallY][wallX] = '_';
#endif

}