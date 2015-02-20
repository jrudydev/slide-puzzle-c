//  position.h <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Position struct library with some convenient functions

#ifndef __SlidePuzzleC__position__
#define __SlidePuzzleC__position__

#include <stdlib.h>
#include <stdbool.h>

typedef struct Position {
    int x;
    int y;
} Position;

Position getPosition(int x, int y);
Position addPositions(Position pos1, Position pos2);
Position subPositions(Position pos1, Position pos2);

bool comparePositions(Position pos1, Position pos2);

#endif
