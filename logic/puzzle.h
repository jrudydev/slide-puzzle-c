//  puzzle.h <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Slide puzzle with solution and invertion options

#ifndef __SlidePuzzleC__puzzle__
#define __SlidePuzzleC__puzzle__

#include "list.h"
#include "position.h"

enum possibleMoves { UP = 1, DOWN, LEFT, RIGHT };
enum boardSizes { MIN_PUZZLE_SIZE = 2, MAX_PUZZLE_SIZE = 6 };

typedef struct Puzzle {
    int size;
    bool inverted;
    Position emptySpace;
    List *directions, *solution;
    int **matrix;
} Puzzle;

Puzzle *createPuzzle(int size);
Puzzle *createPuzzleCopy(Puzzle *puzzle);

void shufflePuzzle(Puzzle *puzzle, int suffleCount);
void swapPositions(Puzzle *puzzle, Position pos1, Position pos2);
bool comparePuzzles(Puzzle *puz1, Puzzle *puz2);

void applyDirection(Puzzle *puzzle, int direction);
void setDirectionVectors(Puzzle *puzzle);
void invertSolution(Puzzle *puzzle);

bool isSolved(Puzzle *puzzle);
int getInverseDirection(int direction);

void destroyPuzzle(Puzzle **puzzle);

#endif
