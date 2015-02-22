//  tests.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Tests for list and puzzle functionality.

#include "../tests/tests.h"
#include "../logic/list.h"
#include "../logic/puzzle.h"

List *testList;
Puzzle *testPuzzle1, *testPuzzle2;

void testListAddNode();
void testListAddDuplicateKey();
void testListDeleteHead();
void testPuzzleCopy();
void testPuzzleShuffle();


void unitTests() {
    testList = createList();
    testPuzzle1 = createPuzzle(getRand(MAX_PUZZLE_SIZE - MIN_PUZZLE_SIZE) + MIN_PUZZLE_SIZE); // random board size between 2-6
    
    testListAddNode();
    testListAddDuplicateKey();
    testListDeleteHead();
    
    testPuzzleCopy();
    testPuzzleShuffle();
    
    testPuzzleCopy();
    
    destroyList(&testList);
    destroyPuzzle(&testPuzzle1);
    destroyPuzzle(&testPuzzle2);
}


void testListAddNode() {
    append(testList, createNode(5, 'a'));
    assert(testList->size = 1);
}


void testListAddDuplicateKey() {
    addKey(testList, createNode(3, 'b'));
    addKey(testList, createNode(3, 'b'));
    assert(testList->size == 2);
}


void testListDeleteHead() {
    deleteHead(&testList);
    assert(testList->size = 1);
}


void testPuzzleCopy() {
    testPuzzle2 = createPuzzleCopy(testPuzzle1);
    assert(comparePuzzles(testPuzzle1, testPuzzle2));
    assert(comparePositions(testPuzzle1->emptySpace, testPuzzle2->emptySpace));
    assert(testPuzzle1->inverted == testPuzzle2->inverted);
}


void testPuzzleShuffle() {
    shufflePuzzle(testPuzzle1, 1000);
    assert(testPuzzle1 != testPuzzle2);
}