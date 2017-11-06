#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Element {
    int prio;
    struct Element* next;
    struct Element* prev;
};

struct Element* head;
struct Element* tail;

struct Element* GetNewElement(){
    int random;
    random = rand() % 41;
    struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
    newElement->prio = random;
    newElement->next = NULL;
    newElement->prev = NULL;
}

//Inserts a Node at tail of Doubly linked list
void InsertFromTail(struct Element* newElement) {
    struct Element* temp = tail;
    while ( temp != NULL && temp->prio < newElement->prio ) {
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

        if ( nextElement == NULL){
            tail = newElement;
        }
        else {
            nextElement->prev = newElement;
            newElement->next = nextElement;
        }
    }
}

void InsertFromHead (struct Element* newElement) {
    struct Element* temp = head;
    while ( temp != NULL && temp->prio > newElement->prio) {
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

void InsertElements(int numberOfElements){
    for (int i = 0; i < numberOfElements; i++) {
        struct Element *newElement = GetNewElement();
        if (head == NULL) {
            head = newElement;
            tail = newElement;
        } else if (newElement->prio >= (head->prio + tail->prio) / 2) {
            InsertFromHead(newElement);
        } else {
            InsertFromTail(newElement);
        }
    }
}

//Prints all the elements in linked list in forward traversal order
void PrintAll() {
    struct Element* temp = head;
    while(temp != NULL) {
        printf("%d ",temp->prio);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    srand((unsigned int)time(NULL));
    /*
    for(int i = 0; i < 1000; i + 100) {
        int j = 0;
        while(j < 200) {
            InsertElements(i);
            PrintAll();
            j++;
        }
    }
     */
    InsertElements(25);
    PrintAll();
    return 0;
}

