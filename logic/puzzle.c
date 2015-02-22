//  puzzle.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Slide puzzle with breadcrumb solution and invertion input options

#include "puzzle.h"
#include "rand.h"
#include <stdio.h>
#include <assert.h>

Position directionVectors[4];

void createDirections(Puzzle *puzzle);
void preformTrace(Puzzle *puzzle, int direction);
void trackSolution(Puzzle *puzzle, int direction);

Puzzle *createPuzzle(int size) {
    int i, j, count = 0;;
    
    Puzzle *puzzle = (Puzzle *)malloc(sizeof(Puzzle));
    puzzle->size = size;
    puzzle->emptySpace = getPosition(0, 0); // x = row, y = cols
    puzzle->solution = createList();
    puzzle->directions = createList();
    puzzle->inverted = true;
    
    createDirections(puzzle);
    setDirectionVectors(puzzle);
    
    // n x n matrix and initiated with incremental count
    puzzle->matrix = (int **)malloc(size * sizeof(int *));
    for(i = 0; i < puzzle->size; i++) {
        puzzle->matrix[i] = (int *)malloc(size * sizeof(int));
        for(j = 0; j < puzzle->size; j++, count++) {
            puzzle->matrix[i][j] = count;
        }
    }
    
    return puzzle;
}


Puzzle *createPuzzleCopy(Puzzle * puzzle) {
    int i, j, size = puzzle->size;
    
    Puzzle *puzzleCopy = (Puzzle *)malloc(sizeof(Puzzle));
    puzzleCopy->size = puzzle->size;
    puzzleCopy->emptySpace = getPosition(puzzle->emptySpace.x, puzzle->emptySpace.y); // x = row, y = cols
    puzzleCopy->solution = createList();
    puzzleCopy->directions = createList();
    puzzleCopy->inverted = puzzle->inverted;
    
    createDirections(puzzleCopy);
    setDirectionVectors(puzzleCopy);

    // n x n matrix and initiated with copy
    puzzleCopy->matrix = (int **)malloc(size * sizeof(int *));
    for(i = 0; i < size; i++) {
        puzzleCopy->matrix[i] = (int *)malloc(size * sizeof(int));
        for(j = 0; j < size; j++) {
            puzzleCopy->matrix[i][j] = puzzle->matrix[i][j];
        }
    }

    return puzzleCopy;
}


void shufflePuzzle(Puzzle *puzzle, int suffleCount) {
    srand( timeSeed() );
    while( isSolved(puzzle) ) {
        // swap one direciton at a time
        for(int i = 0; i < suffleCount; i++) {
            int randLength = getRand(puzzle->directions->size);
            Node *current = puzzle->directions->head;
            for(int j = 0; j < randLength; j++)
                current = current->next;
            
            applyDirection(puzzle, current->data);
        }
    }
}


void swapPositions(Puzzle *puzzle, Position pos1, Position pos2) {
    // update empty space position if needed
    if ( comparePositions(pos1, puzzle->emptySpace) ) {
        puzzle->emptySpace = pos2;
        
        createDirections(puzzle);
    } else if ( comparePositions(pos2, puzzle->emptySpace) ) {
        puzzle->emptySpace = pos1;
        
        createDirections(puzzle);
    }
    
    int temp = puzzle->matrix[pos1.x][pos1.y];
    puzzle->matrix[pos1.x][pos1.y] = puzzle->matrix[pos2.x][pos2.y];
    puzzle->matrix[pos2.x][pos2.y] = temp;
}


bool comparePuzzles(Puzzle *puzzel1, Puzzle *puzzel2) {
    int size = puzzel1->size;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(puzzel1->matrix[i][j] != puzzel2->matrix[i][j])
                return false;

    return true;
}


void applyDirection(Puzzle *puzzle, int direction) {
    Position directionVector = (puzzle->inverted) ?
                                    directionVectors[direction - 1] :
                                    directionVectors[getInverseDirection(direction) - 1];
    Position pos1 = puzzle->emptySpace;
    Position pos2 = addPositions(pos1, directionVector);
    
    swapPositions(puzzle, pos1, pos2);
    
    if(isSolved(puzzle)) {
        emptyList(puzzle->solution);
    } else {
        trackSolution(puzzle, direction);
    }
}

void preformTrace(Puzzle *puzzle, int direction) {
    Position directionVector = (puzzle->inverted) ?
                                    directionVectors[direction - 1] :
                                    directionVectors[getInverseDirection(direction) - 1];
    Position pos1 = puzzle->emptySpace;
    Position pos2 = addPositions(pos1, directionVector);
    if(pos2.x < 0 || pos2.x >= puzzle->size || pos2.y < 0 || pos2.y >= puzzle->size) {
        assert(false);
    }
    
    swapPositions(puzzle, pos1, pos2);
}

void setDirectionVectors(Puzzle *puzzle) {
    directionVectors[0] = getPosition(1, 0);     // UP
    directionVectors[1] = getPosition(-1, 0);    // DOWN
    directionVectors[2] = getPosition(0, 1);     // LEFT
    directionVectors[3] = getPosition(0, -1);    // RIGHT
}

void invertSolution(Puzzle *puzzle) {
    createDirections(puzzle);
    Node *current = puzzle->solution->head;
    while(current != NULL) {
        current->data = getInverseDirection(current->data);
        current = current->next;
    }
}


bool isSolved(Puzzle *puzzle) {
    int i, j, count = 0;
    
    for(i = 0; i < puzzle->size; i++)
        for(j = 0; j < puzzle->size; j++, count++)
            if(puzzle->matrix[i][j] != count)
                return false;
 
    return true;
}


int getInverseDirection(int direction) {
    if (direction == UP)
        return DOWN;
    if (direction == DOWN)
        return UP;
    if (direction == LEFT)
        return RIGHT;
    if (direction == RIGHT)
        return LEFT;
    // throw exception error, use assert for now
    assert(false);
    return 0;
}


void trackSolution(Puzzle *puzzle, int direction) {
    if(puzzle->solution->head == NULL) {
        prepend(puzzle->solution, createNode(direction, '\0'));
    }
    else if(getInverseDirection(direction) == puzzle->solution->head->data) {
        deleteHead(&puzzle->solution);
    } else {
        prepend(puzzle->solution, createNode(direction, '\0'));
        
        // look for loops
        Puzzle *puzzleCopy = createPuzzleCopy(puzzle);
        Node *current = puzzle->solution->head;
        
        while(current != NULL) {
            preformTrace(puzzleCopy, getInverseDirection(current->data));
            if(comparePuzzles(puzzle, puzzleCopy)) {
                chopHead(&puzzle->solution, current);
                Node *newCurrent = puzzle->solution->head;
                while(newCurrent != NULL) {
                    preformTrace(puzzleCopy, getInverseDirection(newCurrent->data));
                    newCurrent = newCurrent->next;
                }
                destroyPuzzle(&puzzleCopy);
                return;
            }
            
            current = current->next;
        }

        destroyPuzzle(&puzzleCopy);
    }
}


void createDirections(Puzzle *puzzle) {
    int posX = puzzle->emptySpace.x;
    int posY = puzzle->emptySpace.y;
    
    if(puzzle->directions->size != 0) {
        emptyList(puzzle->directions);
    }
    
    if(posX < puzzle->size - 1) {
        append(puzzle->directions, createNode((puzzle->inverted) ? UP : DOWN, '\0'));
    }
    if(posX > 0) {
        append(puzzle->directions, createNode((puzzle->inverted) ? DOWN : UP, '\0'));
    }
    if(posY < puzzle->size -1) {
        append(puzzle->directions, createNode((puzzle->inverted) ? LEFT : RIGHT, '\0'));
    }
    if(posY > 0) {
        append(puzzle->directions, createNode((puzzle->inverted) ? RIGHT : LEFT, '\0'));
    }
}


void destroyPuzzle(Puzzle **puzzle) {
    if((*puzzle)->matrix != NULL) {
        for (int i = 0; i < (*puzzle)->size; i++) {
            free((*puzzle)->matrix[i]);
            (*puzzle)->matrix[i] = NULL;
        }
        free((*puzzle)->matrix);
        (*puzzle)->matrix = NULL;
    }
    destroyList(&(*puzzle)->directions);
    destroyList(&(*puzzle)->solution);
    free((*puzzle));
    (*puzzle) = NULL;
}