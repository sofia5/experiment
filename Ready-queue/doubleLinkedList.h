/***************************************
    Random insertions (interval 0-40)
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

struct Element {
    int prio;
    struct Element* next;
    struct Element* prev;
};

struct Element* head;
struct Element* tail;

struct Element* getNewElementRandom(){
    int random = rand() % 41;
    struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
    newElement->prio = random;
    newElement->next = NULL;
    newElement->prev = NULL;
}

//Inserts a Node at tail of Double Linked List
void insertFromTailRandom (struct Element* newElement) {
    struct Element* temp = tail;
    while (temp != NULL && temp->prio < newElement->prio) {
        temp = temp->prev;
    }
    if (temp == NULL) {
        head->prev = newElement;
        newElement->next = head;
        head = newElement;
    }
    else {
        struct Element* nextElement = temp->next;
        temp->next = newElement;
        newElement->prev = temp;

        if (nextElement == NULL){
            tail = newElement;
        }
        else {
            nextElement->prev = newElement;
            newElement->next = nextElement;
        }
    }
}

void insertFromHeadRandom (struct Element* newElement) {
    struct Element* temp = head;
    while (temp != NULL && temp->prio > newElement->prio) {
        temp = temp->next;
    }
    if (temp == NULL) {
        tail->next = newElement;
        newElement->prev = tail;
        tail = newElement;
    }
    else {
        struct Element* prevElement = temp->prev;
        temp->prev = newElement;
        newElement->next = temp;

        if(prevElement == NULL){
            head = newElement;
        }
        else {
            prevElement->next = newElement;
            newElement->prev = prevElement;
        }
    }
}

void insertElementsDoubleLinkedList (int numberOfElements){
    head = NULL;
    tail = NULL;
    for (int i = 0; i < numberOfElements; i++) {
        struct Element *newElement = getNewElementRandom();
        if (head == NULL) {
            head = newElement;
            tail = newElement;
        } else if (newElement->prio >= (head->prio + tail->prio) / 2) {
            insertFromHeadRandom (newElement);
        } else {
            insertFromTailRandom (newElement);
        }
    }
}



