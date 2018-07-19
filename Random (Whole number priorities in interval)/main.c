#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <doubleLinkedList.h>

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
        doubleLinkedList.InsertElementsEvent (10);
        long memoryUsage = usage.ru_maxrss;
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        long elapsedTime = timeEnd.tv_nsec - timeStart.tv_nsec;
    }

    // Test 2 - Time and memory to insert 100 values


    // Test 3 - Time and memory to insert 1000 values

    return 0;
}

