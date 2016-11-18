#include <iostream>
#include "MazeBuilder.hpp"

int main() {

    MazeBuilder * mazeBuilder = new MazeBuilder(200,200,30);
    mazeBuilder->buildMazeStart();

    return 0;
}