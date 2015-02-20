//  interface.h <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Interface used to output puzzle to console

#ifndef __SlidePuzzleC__interface__
#define __SlidePuzzleC__interface__

#include <ctype.h>
#include <stdio.h>
#include "../logic/list.h"
#include "../logic/puzzle.h"

void createKeys();

void interfaceLoop();

int getPuzzleSize();
int getShuffleCount();
char getNextCommand(Puzzle *puzzle);

void printHeader();

void printPuzzle(Puzzle *puzzle);
void printDirections(List *directions, bool inverse);
void printList(List *list);

void printWinner();

void destroyOptionKeys();
void destroyDirectionKeys();

#endif
