//  tests.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Tests for list and puzzle functionality.

#include "../tests/tests.h"
#include "../logic/list.h"
#include "../logic/puzzle.h"

List *testList;
Puzzle *testPuzzle1, *testPuzzle2;

void testListAddNodeSizeIncrease();
void testListAddDuplicateKeyNotAdded();
void testListDeleteHeadReduceSize();
void testPuzzleCopyAreEqual();
void testPuzzleShuffleNotSame();


void unitTests() {
    testList = createList();
    testPuzzle1 = createPuzzle(getRand(MAX_PUZZLE_SIZE - MIN_PUZZLE_SIZE) + MIN_PUZZLE_SIZE); // random board size between 2-6
    
    testListAddNodeSizeIncrease();
    testListAddDuplicateKeyNotAdded();
    testListDeleteHeadReduceSize();
    
    testPuzzleCopyAreEqual();
    testPuzzleShuffleNotSame();
    
    destroyList(&testList);
    destroyPuzzle(&testPuzzle1);
    destroyPuzzle(&testPuzzle2);
}


void testListAddNodeSizeIncrease() {
    append(testList, createNode(5, 'a'));
    assert(testList->size = 1);
}


void testListAddDuplicateKeyNotAdded() {
    addKey(testList, createNode(3, 'b'));
    addKey(testList, createNode(3, 'b'));
    assert(testList->size == 2);
}


void testListDeleteHeadReduceSize() {
    deleteHead(&testList);
    assert(testList->size = 1);
}


void testPuzzleCopyAreEqual() {
    testPuzzle2 = createPuzzleCopy(testPuzzle1);
    assert(comparePuzzles(testPuzzle1, testPuzzle2));
    assert(comparePositions(testPuzzle1->emptySpace, testPuzzle2->emptySpace));
    assert(testPuzzle1->inverted == testPuzzle2->inverted);
    assert(testPuzzle1->size == testPuzzle2->size);
}


void testPuzzleShuffleNotSame() {
    shufflePuzzle(testPuzzle1, 1000);
    assert(testPuzzle1 != testPuzzle2);
}