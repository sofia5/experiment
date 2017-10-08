#include <stdio.h>
#include <stdlib.h>

struct Element {
    int prio;
    struct Element* next;
    struct Element* prev;
};

struct Element* head;
struct Element* tail;

struct Element* GetNewElement(){
    int random = rand() % 41;
    struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
    newElement->prio = random;
    newElement->next = NULL;
    newElement->prev = NULL;
}

void Insert(int numberOfElements){
    for (int i = 0; i <= numberOfElements; i++) {
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

//Inserts a Node at head of doubly linked list
void InsertFromHead(struct Element* newElement) {
    struct Element* temp = head;
    while (temp->next != NULL) {
        if(newElement->prio > temp->prio){
            newElement->prev = temp->prev;
            newElement->next = temp;
            temp->prev = newElement;
            return;
        }
        else{
            temp = temp->next;
        }
    }
    newElement->prev = temp->prev;
    newElement->next = temp;
    temp->prev = newElement;
    tail = newElement;
}

//Inserts a Node at tail of Doubly linked list
void InsertFromTail(struct Element* newElement) {
    struct Element *temp = tail;
    while (temp->prev != NULL) {
        if (newElement->prio < temp->prio) {
            newElement->next = temp->next;
            newElement->prev = temp;
            temp->next = newElement;
            return;
        } else {
            temp = temp->prev;
        }
    }
    newElement->next = temp->next;
    newElement->prev = temp;
    temp->next = newElement;
    tail = newElement;
}

int main() {
    Insert(4);
    printf("Hello, World!\n");
    PrintAll();
    return 0;
}

//Prints all the elements in linked list in forward traversal order
void PrintAll() {
    struct Element* temp = head;
    printf("Forward: ");
    while(temp != NULL) {
        printf("%d ",temp->prio);
        temp = temp->prev;
    }
    printf("\n");
}
