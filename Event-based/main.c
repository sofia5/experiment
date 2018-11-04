#define _POSIX_X_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <limits.h>
#include "doubleLinkedList.h"
#include "splaytree.h"


static double converterToSeconds(struct timespec *ts){
    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
};

/********************
        Tests
*********************/
// Test - Best, avg, worse time and memory to insert n (10-1000) values, with an increase of
// 10 per test and with 100 runs per test
void testDoubleLinkedList() {
    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;
    int numberOfElements = 10;

    FILE *fp;
    FILE *file;
    fp = fopen("EventDoubleLinkedList", "w+");
    file = fopen("EventDoubleLinkedListAll", "w+");
    fprintf(fp, "Number of elements:;Best time:;Worst time:;Average time:;Memory usage:\n");

    while(numberOfElements <= 1000) {
        long memoryUsage = 0;
        double averageTime = 0;
        double elapsedTime = 0;
        double longestTime = LONG_MIN;
        double shortestTime = LONG_MAX;
        double sumOfTime = 0;

        fprintf(file, "\n%d;", numberOfElements);

        for (int i = 0; i < 100; i++) {
            int num = numberOfElements;
            getrusage(RUSAGE_SELF, &usage);
            clock_gettime(CLOCK_MONOTONIC, &timeStart);
            insertElementsDoubleLinkedList(num);
            clock_gettime(CLOCK_MONOTONIC, &timeEnd);
            memoryUsage = usage.ru_maxrss;
            elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
            if(longestTime < elapsedTime) longestTime = elapsedTime;
            if(shortestTime > elapsedTime) shortestTime = elapsedTime;
            sumOfTime += elapsedTime;

            fprintf(file,"%f;", elapsedTime);

        }
        //Print
        averageTime = sumOfTime / 100;
        fprintf(fp, "%d;%f;%f;%f;%ld\n",numberOfElements, shortestTime, longestTime, averageTime, memoryUsage);
        //fprintf(fp,"Number of elements:%d\t Best time:%f\t Worst time:%f\t Average time:%f\t Memory usage: %ld\n",
        //        numberOfElements, shortestTime, longestTime, averageTime, memoryUsage);
        fflush(fp);
        fflush(file);
        numberOfElements += 10;
    }
    fclose(fp);
    fclose(file);
}

// Test - Best, avg, worse time and memory to insert n (10-1000) values, with an increase of
// 10 per test and with 100 runs per test
void testSplaytree() {
    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;

    FILE *fp;
    fp = fopen("EventSplaytree", "w+");
    fprintf(fp, "Number of elements:;Best time:;Worst time:;Average time:;Memory usage:\n");

    int numberOfElements = 10;

    while(numberOfElements <= 1000) {
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
        fprintf(fp, "%d;%f;%f;%f;%ld\n",numberOfElements, shortestTime, longestTime, averageTime, memoryUsage);
        numberOfElements += 10;
    }
    fclose(fp);
}

int main() {

    //testDoubleLinkedList();
    testSplaytree();
    return 0;

}




