//  list.h <> SlidePuzzleC
//  Created by Rodolfo
//
//  Description: This is a linked list library which also acts as a dictionary
//  Referenced: http://codingfreak.blogspot.com/2009/08/implementation-of-singly-linked-list-in.html

#ifndef __SlidePuzzleC__list__
#define __SlidePuzzleC__list__

#include <stdbool.h>
#include "rand.h"

typedef struct Node {
    int data;
    char key;
    struct Node *next;
} Node;

typedef struct List {
    int size;
    struct Node *head;
    struct Node *tail;
} List;

List *createList();
Node *createNode(int num, char key);

void prepend(List *list, Node *newHead);
void append(List *list, Node *newTail);
void prependAt(List *list, Node *newNode, int pos);
void appendAt(List *list, Node *newNode, int Pos);

void makeHead(List **list, Node *newHead);
void chopHead(List **list, Node *oldHead);

void addKey(List *list, Node *newNode);
bool hasKey(List *list, char key);
int getData(List *list, char key);
bool isDataInList(List *list, int data);
bool isKeyInList(List *list, char key);

void deleteHead(List **list);
//void deleteTail(List *list);
//void deleteAt(List *list, int pos);

void buildRand(List *list, int size);

void emptyList(List *list);
void destroyNode(Node **node);
void destroyList(List **list);

#endif

