//
// Created by Shane Kochvi on 11/11/16.
//

#include <iostream>
#include <fstream>
#include "MazeBuilder.hpp"
#include "RandomCellList.hpp"

MazeBuilder::MazeBuilder(int width, int height, int count) {

    _mazeHeight = height;
    _mazeWidth = width;
    _mazeCount = count;

    // Initialize node grid
    _cellGrid = new Cell**[_mazeHeight];
    for( int i = 0; i<_mazeHeight; i++){
        _cellGrid[i] = new Cell*[_mazeWidth];
        for( int j = 0; j<_mazeWidth; j++){
            _cellGrid[i][j] = new Cell{j,i,false};
        }
    }

    // Initialize character grid
//    int charGridWidth = 2*_mazeWidth+1;
    int charGridWidth = 4*_mazeWidth+2;
    int charGridHeight = 2*_mazeHeight+1;

    _charGrid = new char*[charGridHeight];
    for( int i = 0; i<charGridHeight; i++){
        _charGrid[i] = new char[charGridWidth];
        for( int j = 0; j<charGridWidth; j++){
            _charGrid[i][j] = '#';
        }
    }
}

void MazeBuilder::refreshGrids(){

    // Re-initialize node grid
    for( int i = 0; i<_mazeHeight; i++){
        for( int j = 0; j<_mazeWidth; j++){
            _cellGrid[i][j]->visited = false;
        }
    }

    // Re-initialize character grid
//    int charGridWidth = 2*_mazeWidth+1;
    int charGridWidth = 4*_mazeWidth+2;
    int charGridHeight = 2*_mazeHeight+1;

    for( int i = 0; i<charGridHeight; i++){
        for( int j = 0; j<charGridWidth; j++){
            _charGrid[i][j] = '#';
        }
    }
}

void MazeBuilder::buildMazes() {

    Cell * startCell = _cellGrid[0][0]; // Just to start
    for( int i = 0; i<_mazeCount; i++ ){
        refreshGrids();
        buildMaze(startCell);
        printCharGrid(i);
    }
}


void MazeBuilder::buildMaze(Cell* currentCell){

    currentCell->visited = true;

    RandomCellList * cells = new RandomCellList(currentCell,_cellGrid, _mazeWidth,_mazeHeight);

    Cell * nextCell = cells->next();

//    std::cout << "CURRENT CELL:" << "(" << currentCell->location.x << "," << currentCell->location.y << ")" << std::endl;
//    if( nextCell == nullptr ){
//        std::cout<<" null, returning"<<std::endl;
//    }else {
//        std::cout << "NEXT CELL:" << "(" << nextCell->location.x << "," << nextCell->location.y << ")" << std::endl;
//    }

    while( nextCell != nullptr ){

        updateCharGrid(currentCell, nextCell);
        buildMaze(nextCell);
        nextCell = cells->next();

    }
}


void MazeBuilder::printCharGrid(int count){

    std::string path("/Users/shanekochvi/ClionProjects/maze/mazes/");
    path += "maze_";
    path += std::to_string(_mazeWidth);
    path += "x";
    path += std::to_string(_mazeHeight);
    path += "_";
    path += std::to_string(count);

    std::ofstream outfile(path);

    // Print character grid
//    int charGridWidth = 2*_mazeWidth+1;
    int charGridWidth = 4*_mazeWidth+2;
    int charGridHeight = 2*_mazeHeight+1;

//    for( int i = 0; i<charGridHeight; i++){
//        for( int j = 0; j<charGridWidth; j++){
//            std::cout<<_charGrid[i][j];
//        }
//        std::cout<<std::endl;
//    }

    for( int i = 0; i<charGridHeight; i++){
        for( int j = 0; j<charGridWidth; j++){
            outfile<<_charGrid[i][j];
        }
        outfile<<std::endl;
    }

    outfile.close();

}


void MazeBuilder::updateCharGrid(Cell *cell1, Cell *cell2){

//    // Cell 1 char grid update
//    int cell1CharX = (cell1->location.x*2)+1;
//    int cell1CharY = (cell1->location.y*2)+1;
//    _charGrid[cell1CharY][cell1CharX] = '_';
//
//    std::cout<<"\tcurrent char: ("<<cell1CharX<<", "<<cell1CharY<<")"<<std::endl;
//
//    // Cell 2 char grid update
//    int cell2CharX = (cell2->location.x*2)+1;
//    int cell2CharY = (cell2->location.y*2)+1;
//    _charGrid[cell2CharY][cell2CharX] = '_';
//
//    std::cout<<"\tnext char: ("<<cell2CharX<<", "<<cell2CharY<<")"<<std::endl;
//
//
//    // Wall grid update, get average value for x and y each.
//    int wallX = (cell1CharX+cell2CharX)/2;
//    int wallY = (cell1CharY+cell2CharY)/2;
//    _charGrid[wallY][wallX] = '_';
//
//    std::cout<<"\twall char: ("<<wallX<<", "<<wallY<<")"<<std::endl;

    // Cell 1 char grid update
    int cell1CharX = (cell1->location.x*4)+2;
    int cell1CharY = (cell1->location.y*2)+1;
    _charGrid[cell1CharY][cell1CharX] = '_';
    _charGrid[cell1CharY][cell1CharX+1] = '_';

    // Cell 2 char grid update
    int cell2CharX = (cell2->location.x*4)+2;
    int cell2CharY = (cell2->location.y*2)+1;
    _charGrid[cell2CharY][cell2CharX] = '_';
    _charGrid[cell2CharY][cell2CharX+1] = '_';

    // Wall grid update, get average value for x and y each.
    int wallX = (cell1CharX+cell2CharX)/2;
    int wallY = (cell1CharY+cell2CharY)/2;
    _charGrid[wallY][wallX] = '_';
    _charGrid[wallY][wallX+1] = '_';

}