//  list.c <> SlidePuzzleC
//  Created by Rodolfo Gomez
//
//  Description: This is a linked list library which also acts as a dictionary
//  Referenced: http://codingfreak.blogspot.com/2009/08/implementation-of-singly-linked-list-in.html

#include "list.h"

List *createList() {
    List *newList;
    
    newList = (List *)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    
    return newList;
}


Node *createNode(int num, char key) {
    Node *newNode;
    
    newNode = (Node *)malloc(sizeof(Node));
    newNode->data = num;
    newNode->key = key;
    newNode->next = NULL;
    
    return newNode;
}


bool headExists(List *list, Node *node) {
    if(list->head != NULL)
        return true;
    
    // make this node the new head and tail
    list->head = node;
    list->tail = node;
    list->size = 1;
    
    return false;
}


void prepend(List *list, Node *newHead) {
    if (headExists(list, newHead)) {
        newHead->next = list->head;
        list->head = newHead;
        list->size++;
    }
}


void append(List *list, Node *newTail) {\
    if (headExists(list, newTail)) {
        list->tail->next = newTail;
        newTail->next = NULL;
        list->tail = newTail;
        list->size++;
    }
}


void prependAt(List *list, Node *newNode, int pos) {
    if (headExists(list, newNode)) {
        Node *current = list->head;
        for(int i = 0; current->next != NULL && i < pos - 1; i++) {
            current = current->next;
        }
        // insert before current node
        if(pos == 0) {
            newNode->next = current;
            list->head = newNode;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
        list->size++;
    }
}


void appendAt(List *list, Node *newNode, int pos) {
    if (headExists(list, newNode)) {
        Node *current = list->head;
        for(int i = 0; current->next != NULL && i < pos; i++) {
            current = current->next;
        }
        // anset after current node
        newNode->next = current->next;
        current->next = newNode;
        list->size++;
    }
}

void makeHead(List **list, Node *newHead) {
    Node *current = (*list)->head;
    while (current != newHead) {
        current = current->next;
        deleteHead(&(*list));
    }
}


void chopHead(List **list, Node *oldHead) {
    makeHead(&(*list), oldHead);
    deleteHead(&(*list));
}


void addKey(List *list, Node *newNode){
    if(list->size != 0) {
        if(newNode->key == '\0' || hasKey(list, newNode->key))
            return;
    }
    
    append(list, newNode);
}


bool hasKey(List *list, char key){
    Node *current = list->head;
    for(int i = 0; current != NULL; i++) {
        if(current->key == key)
            return true;
        current = current->next;
    }
    
    return false;
}


int getData(List *list, char key) {
    Node *current = list->head;
    for(int i = 0; current != NULL; i++) {
        if(current->key == key) {
            return current->data;
        }
        current = current->next;
    }
    
    return 0;
}


bool isDataInList(List *list, int data) {
    Node *current = list->head;
    
    while(current != NULL) {
        if(current->data == data)
            return true;
        
        current = current->next;
    }
    
    return false;
}


bool isKeyInList(List *list, char key) {
    Node *current = list->head;
    
    while(current != NULL) {
        if(current->key == key)
            return true;
        
        current = current->next;
    }
    
    return false;
}


void deleteHead(List **list) {
    if((*list) != NULL && (*list)->size > 0) {
        if((*list)->head != NULL) {
            if((*list)->tail == (*list)->head) {
                (*list)->tail = NULL;
            }
            Node *temp = (*list)->head;
            (*list)->head = (*list)->head->next;
            (*list)->size--;
            destroyNode(&temp);
        }
    }
}


//void deleteTail(List *list) {
//    Node *current = list->head;
//    int prevPos = getSize(list) - 1;
//    for(int i = 0; current->next != NULL && i < prevPos; i++) {
//        current = current->next;
//    }
//    if(current->next != NULL) {
//        Node *temp = current->next;
//        current->next = NULL;
//        free(temp);
//    }/* else if(current != NULL) {
//        free(current);
//        current = NULL;
//    }*/
//}


//void deleteAt(List *list, int pos) {
//    /*Node *current = list->head;
//    for(int i = 0; current->next != NULL && i < pos; i++) {
//        current = current->next;
//    }
//    Node *temp = list->head;
//    list->head = list->head->next;
//    free(temp);*/
//}



void buildRand(List *list, int size) {
    if(list->head != NULL) {
        destroyList(&list);
    }
    srand( timeSeed() );
    for (int x = 0; x < size; x++) {
        int randIdx = getRand(list->size);
        // randomly insert each node on creation
        int randInsert = getRand(2);
        (randInsert) ? appendAt(list, createNode(x, '\0'), randIdx)
        : prependAt(list, createNode(x, '\0'), randIdx);
    }
}

void emptyList(List *list) {
    while(list->head != NULL) {
        deleteHead(&list);
    }
    list->tail = NULL;
}

void destroyNode(Node **node) {
    free(*node);
    *node = NULL;
}

void destroyList(List **list) {
    while((*list)->head != NULL) {
        deleteHead(&(*list));
    }
    (*list)->tail = NULL;
    free((*list));
    (*list) = NULL;
}