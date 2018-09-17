#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <limits.h>
#include "doubleLinkedList.h"
#include "splaytree.h"


static double converterToSeconds(struct timespec *ts){
    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
};

/********************
        Tests
*********************/
// Test - Time and memory to insert n (10, 100, 1000) values
void testDoubleLinkedList(int numberOfValues) {
    srand((unsigned int) time(NULL)); //Used for increased randomness
    struct timespec timeStart, timeEnd;

    struct rusage usage;
    int numberOfElements = 10;

    FILE *fp;
    fopen("randomDoubleLinkedList", "w+");

    while(numberOfElements <= 100) {
        long memoryUsage = 0;
        double elapsedTime = 0;
        double longestTime = LONG_MIN;
        double shortestTime = LONG_MAX;
        double sumOfTime = 0;
        double avgTime = 0;

        for (int i = 0; i < 100; i++) {
            getrusage(RUSAGE_SELF, &usage);
            clock_gettime(CLOCK_MONOTONIC, &timeStart);
            insertElementsDoubleLinkedList(numberOfValues);
            clock_gettime(CLOCK_MONOTONIC, &timeEnd);
            memoryUsage = usage.ru_maxrss;
            elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
            if (longestTime < elapsedTime) longestTime = elapsedTime;
            if (shortestTime > elapsedTime) shortestTime = elapsedTime;
            sumOfTime += elapsedTime;

        }
        //Print
        avgTime = sumOfTime / 100;
        fprintf(fp,"Number of elements:%d\t Best time:%f\t Worst time:%f\t Average time:%f\t Memory usage: %ld\n",
                numberOfElements, shortestTime, longestTime, avgTime, memoryUsage);
        numberOfElements += 10;
    }
    fclose(fp);
}

// Test - Time and memory to insert n (10, 100, 1000) values
void testSplaytree() {
    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;
    int numberOfElements = 10;

    FILE *fp;
    fp = fopen("EventSplaytree", "w+");

    while(numberOfElements <= 100) {
        long memoryUsage = 0;
        double elapsedTime = 0;
        double longestTime = 0;
        double shortestTime = 10000;
        double sumOfTime = 0;
        double averageTime = 0;
        
        for (int i = 0; i < 100; i++) {
            getrusage(RUSAGE_SELF, &usage);
            clock_gettime(CLOCK_MONOTONIC, &timeStart);
            insertNodesSplaytree(numberOfElements);
            clock_gettime(CLOCK_MONOTONIC, &timeEnd);
            memoryUsage = usage.ru_maxrss;
            elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
            if(longestTime < elapsedTime) longestTime = elapsedTime;
            if(shortestTime > elapsedTime) shortestTime = elapsedTime;
            sumOfTime += elapsedTime;
        }
        //Print
        averageTime = sumOfTime / 100;
        fprintf(fp, "Number of elements:%d\t Best time:%f\t Worst time:%f\t Average time:%f\t Memory usage: %ld\n",
                numberOfElements, shortestTime, longestTime, averageTime, memoryUsage);
        numberOfElements += 10;
    }
    fclose(fp);
}

int main() {
    //testDoubleLinkedList();
    testSplaytree();
    return 0;
}




