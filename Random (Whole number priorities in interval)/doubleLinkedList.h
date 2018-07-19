/***************************************
    Random insertions (interval 0-40)
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

struct Element {
    //int prio;
    double prio;
    struct Element* next;
    struct Element* prev;
};

struct Element* head;
struct Element* tail;

struct Element* GetNewElementRandom(){
    //srand((unsigned int) time(NULL));
    int random = rand() % 41;
    struct Element* newElement = (struct Element*)malloc(sizeof(struct Element));
    newElement->prio = random;
    newElement->next = NULL;
    newElement->prev = NULL;
}

//Inserts a Node at tail of Double Linked List
void InsertFromTailRandom (struct Element* newElement) {
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

void InsertFromHeadRandom (struct Element* newElement) {
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

void InsertElementsRandom (int numberOfElements){
    for (int i = 0; i < numberOfElements; i++) {
        struct Element *newElement = GetNewElementRandom();
        if (head == NULL) {
            head = newElement;
            tail = newElement;
        } else if (newElement->prio >= (head->prio + tail->prio) / 2) {
            InsertFromHeadRandom (newElement);
        } else {
            InsertFromTailRandom (newElement);
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;

    //InsertElements(25);
    //PrintAll();

    /********************
            Tests
    *********************/
    // Test 1 - Time and memory to insert 10 values
    for (int i = 0; i < 100; i++) {
        getrusage(RUSAGE_SELF, &usage);
        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        InsertElementsEvent (10);
        long memoryUsage = usage.ru_maxrss;
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        long elapsedTime = timeEnd.tv_nsec - timeStart.tv_nsec;
    }

    // Test 2 - Time and memory to insert 100 values


    // Test 3 - Time and memory to insert 1000 values

    return 0;
}

