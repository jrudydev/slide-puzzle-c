//  main.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Console sliding puzzle, Enjoy!

#include "logic/puzzle.h"
#include "ui/interface.h"
#include "tests/tests.h"

int main(int argc, const char *argv[]) {
    interfaceLoop();
    
    unitTests();
    
    return 0;
}