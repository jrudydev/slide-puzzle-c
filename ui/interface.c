//  interface.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: Interface used to output puzzle to console

#include "interface.h"
#include <curses.h>

#define UP_KEY 'e'
#define DOWN_KEY 'd'
#define LEFT_KEY 's'
#define RIGHT_KEY 'f'

#define QUIT_KEY 'q'
#define RESTART_KEY 't'
#define INVERT_KEY 'z'
#define SOLVE_KEY 'v'

int shuffleCount;
bool showSolution;
List *directionKeys, *optionKeys;

void printMenu();
void printSolution(List *solution);
int cleanStdin();

void createDirectionKeys() {
    directionKeys = createList();
    addKey(directionKeys, createNode(UP, UP_KEY));
    addKey(directionKeys, createNode(DOWN, DOWN_KEY));
    addKey(directionKeys, createNode(LEFT, LEFT_KEY));
    addKey(directionKeys, createNode(RIGHT, RIGHT_KEY));
}


void createOptionKeys() {
    optionKeys = createList();
    addKey(optionKeys, createNode(0, QUIT_KEY));
    addKey(optionKeys, createNode(0, RESTART_KEY));
    addKey(optionKeys, createNode(0, INVERT_KEY));
    addKey(optionKeys, createNode(0, SOLVE_KEY));
}


void interfaceLoop() {
    Puzzle *puzzle = NULL;
    char command = '\0';
    
    showSolution = false;
    
    createDirectionKeys();
    createOptionKeys();
    
    do {
        puzzle = createPuzzle(getPuzzleSize());
        shuffleCount = getShuffleCount();
        shufflePuzzle(puzzle, shuffleCount);
        
        showSolution = false;
        
        while( !isSolved(puzzle) ){
            printHeader();
            printPuzzle(puzzle);
            command = getNextCommand(puzzle);
            
            if(command == INVERT_KEY) {
                puzzle->inverted = (puzzle->inverted) ? false : true;
                invertSolution(puzzle);
                setDirectionVectors(puzzle);
            }
            else if(command == SOLVE_KEY)
                showSolution = (showSolution) ? false : true;
            else if(command == QUIT_KEY || command == RESTART_KEY)
                break;
            else
                applyDirection(puzzle, getData(directionKeys, command));
        }
        
        if( isSolved(puzzle) ) {
            printPuzzle(puzzle);
            printWinner();
        }
        
        destroyPuzzle(&puzzle);
    } while(command == RESTART_KEY);
    
    destroyOptionKeys();
    destroyDirectionKeys();
}

int getPuzzleSize() {
    int num = 0;
    char ch;
    do {
        printf("\nChoose a puzzle SIZE(%d-%d)-> ", MIN_PUZZLE_SIZE, MAX_PUZZLE_SIZE);
        
        // continue until exactly one number entered
    } while(((scanf("%d%c", &num, &ch) != 2 || ch != '\n') && cleanStdin())
            || num < MIN_PUZZLE_SIZE
            || num > MAX_PUZZLE_SIZE);
    
    return num;
}


int getShuffleCount() {
    int num = 0;
    char ch;
    do {
        printf("\nEnter number of SHUFFLES(1-1000)-> ");
        
        // continue until exactly one number entered
    } while(((scanf("%d%c", &num, &ch) != 2 || ch != '\n') && cleanStdin())
            || num < 1
            || num > 1000);
    
    return num;
}


char getNextCommand(Puzzle *puzzle) {
    char ch, n_ch;
    do {
        printf("\nSLIDE the numbers to order the tiles.\n");
        printDirections(puzzle->directions, false);
        printf("-> ");
        
        // continue until exactly one char entered
    } while(tolower((scanf("%c%c", &ch, &n_ch) != 2 || n_ch != '\n') && cleanStdin())
            || (!isDataInList(puzzle->directions, getData(directionKeys, tolower(ch))) &&
            !isKeyInList(optionKeys, tolower(ch))));
    
    return tolower(ch);
}

void printHeader() {
    // make this pc compatible
    //system("clear");
    printf("\n==============================\n");
    printf("||%7cSLIDE PUZZLE%7c||", ' ', ' ');
    printf("\n==============================");
}


void printBorder(int size) {
    char bg = 35;
    printf("%5c", ' ');
    for (int i = 0; i < (size * 2) + (size + 3); i++)
        printf("%c", bg);
    printf("\n");
}


void printPuzzle(Puzzle *puzzle) {
    int i, j, size = puzzle->size;
    printf("\n\nDificulty: %d x %d\n", size, size);
    printf("Shuffles: %d\n\n", shuffleCount);
    
    printBorder(size);
    
    for (i = 0; i < size; i++) {
        printf("%5c#|", ' ');
        for (j = 0; j < size; j++) {
            if(puzzle->matrix[i][j] == 0) {
                if(puzzle->inverted)
                    printf("%2c", ' ');
                else
                    printf("%2d", 0);
            } else {
                printf("%2d", puzzle->matrix[i][j]);
            }
            printf("|");
        }
        printf("#\n");
    }
    
    printBorder(size);
    printMenu();
    
    if(showSolution && puzzle->solution->size > 0)
        printSolution(puzzle->solution);
}


void printDirections(List *directions, bool inverse) {
    Node *current = directions->head;
    int data, count = 0;
    
    printf("[");
    while(current != NULL && count < 5) {
        data = (inverse) ? getInverseDirection(current->data) : current->data;
        switch(data) {
            case UP:
                printf("(%c)Up", toupper(UP_KEY));
                break;
            case DOWN:
                printf("(%c)Down", toupper(DOWN_KEY));
                break;
            case LEFT:
                printf("(%c)Left", toupper(LEFT_KEY));
                break;
            case RIGHT:
                printf("(%c)Right", toupper(RIGHT_KEY));
                break;
            default:
                break;
                
        }
        
        if(current->next != NULL) {
            printf(", ");
        }
        
        
        current = current->next;
        count++;
    }
    
    if(count >= 5) {
        printf("...");
    } else {
        printf("]");
    }
}


void printList(List *list) {
    Node *current = list->head;
    // print list with format [1, 2, ..., n]
    printf("[");
    for(int i = 0; current != NULL; i++) {
        printf("%d", current->data);
        if(current->key != '\0') {
            printf("-%c", current->key);
        }
        if(current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

void printMenu() {
    printf("\n%15cOPTIONS-> [(%c)Solve, (%c)Invert, (%c)Restart, (%c)Quit]\n",
           ' ',
           toupper(SOLVE_KEY),
           toupper(INVERT_KEY),
           toupper(RESTART_KEY),
           toupper(QUIT_KEY));
}

void printSolution(List *solution) {
    printf("\nSOLUTION(%d)-> ", solution->size);
    printDirections(solution, true);
    printf("\n");
}


void printWinner() {
    printf("\nCongrats. You win!\n");
}

// clear input buffer
int cleanStdin() {
    while(getchar() != '\n');
    return 1;
}


void destroyOptionKeys() {
    free(optionKeys);
    optionKeys = NULL;
}


void destroyDirectionKeys() {
    free(directionKeys);
    directionKeys = NULL;
}