#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "doubleLinkedList.h"
#include "splaytree.h"

int main() {

    //testDoubleLinkedList(10);
    //testDoubleLinkedList(100);
    //testDoubleLinkedList(1000);
    testSplaytree(10);
    //testSplaytree(100);
    //testSplaytree(1000);

    return 0;

}
/********************
        Tests
*********************/
// Test - Time and memory to insert n (10, 100, 1000) values
void testDoubleLinkedList(int numberOfValues) {
    char filename[64];
    sprintf(filename, "output%s%d.txt", "EventDoubleLinkedList", numberOfValues);
    fclose(fopen(filename, "w"));

    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;

    for (int i = 0; i < 100; i++) {
        getrusage(RUSAGE_SELF, &usage);
        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        insertElementsDoubleLinkedList(numberOfValues);
        long memoryUsage = usage.ru_maxrss;
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        long elapsedTime = timeEnd.tv_nsec - timeStart.tv_nsec;

        //Print
        FILE *fp;
        char filename[64];
        sprintf(filename, "output%s%d.txt", "EventDoubleLinkedList", numberOfValues);
        fp = fopen(filename, "a");
        fprintf(fp, "%ld\t%ld\n", elapsedTime, memoryUsage);
        fclose(fp);

        printAll();
    }
}

// Test - Time and memory to insert n (10, 100, 1000) values
void testSplaytree(int numberOfValues) {

    char filename[64];
    sprintf(filename, "output%s%d.txt", "EventSplaytree", numberOfValues);
    fclose(fopen(filename, "w"));

    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;

    for (int i = 0; i < 100; i++) {
        getrusage(RUSAGE_SELF, &usage);
        clock_gettime(CLOCK_MONOTONIC, &timeStart);
        insertNodesSplaytree(numberOfValues);
        long memoryUsage = usage.ru_maxrss;
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        long elapsedTime = timeEnd.tv_nsec - timeStart.tv_nsec;

        //Print
        FILE *fp;
        char filename[64];
        sprintf(filename, "output%s%d.txt", "EventSplaytree", numberOfValues);
        fp = fopen(filename, "a");
        fprintf(fp, "%ld\t%ld\n", elapsedTime, memoryUsage);
        fclose(fp);
    }
}




