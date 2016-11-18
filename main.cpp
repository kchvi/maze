#include <iostream>
#include "MazeBuilder.hpp"

int main() {

    MazeBuilder * mazeBuilder = new MazeBuilder(25,25,1);
    mazeBuilder->buildMazes();

    return 0;
}