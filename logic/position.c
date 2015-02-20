//  position.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Position struct library with some convenient functions

#include "position.h"

Position getPosition(int x, int y) {
    Position pos ;;
    pos.x = x;
    pos.y = y;
    
    return pos;
}


Position addPositions(Position pos1, Position pos2) {
    return getPosition(pos1.x + pos2.x, pos1.y + pos2.y);
}


Position subPositions(Position pos1, Position pos2) {
    return getPosition(pos1.x - pos2.x, pos1.y - pos2.y);
}


bool comparePositions(Position pos1, Position pos2) {
    return (pos1.x == pos2.x && pos1.y == pos2.y);
}