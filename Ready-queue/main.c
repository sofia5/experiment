#define _POSIX_C_SOURCE 199309L

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
// Test - Time and memory to insert n (10, 100, 1000) values
void testDoubleLinkedList() {
    srand((unsigned int) time(NULL)); //Used for increased randomness
    struct timespec timeStart, timeEnd;
    struct rusage usage;
    int numberOfElements = 0;

    FILE *file_time, *file_memory, *file_shortest_time, *file_average_time, *file_longest_time;
    file_time = fopen("Ready_DoubleLinkedList_Time_Raw", "w+");
    file_memory = fopen("Ready_DoubleLinkedList_Memory_Raw", "w+");
    file_shortest_time = fopen("Ready_DoubleLinkedList_Best", "w+");
    file_average_time = fopen("Ready_DoubleLinkedList_Avg", "w+");
    file_longest_time = fopen("Ready_DoubleLinkedList_Worst", "w+");

    while(numberOfElements <= 1000) {
        fprintf(file_shortest_time, "\n%d,", numberOfElements);
        fprintf(file_average_time, "\n%d,", numberOfElements);
        fprintf(file_longest_time, "\n%d,", numberOfElements);
        /*Running 10 times in order to get average for box plot in graph*/

        for (int i = 0; i < 10; i++) {
            long memoryUsage = 0;
            double averageTime = 0;
            double elapsedTime = 0;
            double longestTime = LONG_MIN;
            double shortestTime = LONG_MAX;
            double sumOfTime = 0;
            fprintf(file_time, "\n%d,", numberOfElements);
            fprintf(file_memory, "\n%d,", numberOfElements);

        for (int i = 0; i < 100; i++) {
            getrusage(RUSAGE_SELF, &usage);
            clock_gettime(CLOCK_MONOTONIC, &timeStart);
            insertElementsDoubleLinkedList(numberOfElements);
            clock_gettime(CLOCK_MONOTONIC, &timeEnd);
            memoryUsage = usage.ru_maxrss;
            fprintf(file_memory, "%ld,", memoryUsage);
            fprintf(file_time, "%f,", elapsedTime);
            elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
            if (longestTime < elapsedTime) longestTime = elapsedTime;
            if (shortestTime > elapsedTime) shortestTime = elapsedTime;
            sumOfTime += elapsedTime;
        }
            //Print
            averageTime = sumOfTime / 100;
            fprintf(file_shortest_time, "%f,", shortestTime);
            fprintf(file_average_time, "%f,", averageTime);
            fprintf(file_longest_time, "%f,", longestTime);
        }

        numberOfElements += 10;
    }
    fclose(file_time);
    fclose(file_memory);
    fclose(file_shortest_time);
    fclose(file_average_time);
    fclose(file_longest_time);
}

// Test - Time and memory to insert n (10, 100, 1000) values
void testSplaytree() {
    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;
    int numberOfElements = 0;

    FILE *file_time, *file_memory, *file_shortest_time, *file_average_time, *file_longest_time;
    file_time = fopen("Ready_Splaytree_Time_Raw", "w+");
    file_memory = fopen("Ready_Splaytree_Memory_Raw", "w+");
    file_shortest_time = fopen("Ready_Splaytree_Best", "w+");
    file_average_time = fopen("Ready_Splaytree_Avg", "w+");
    file_longest_time = fopen("Ready_Splaytree_Worst", "w+");

    while(numberOfElements <= 1000) {
        fprintf(file_shortest_time, "\n%d,", numberOfElements);
        fprintf(file_average_time, "\n%d,", numberOfElements);
        fprintf(file_longest_time, "\n%d,", numberOfElements);
        /*Running 10 times in order to get average for box plot*/
        for (int i = 0; i < 10; i++) {
            long memoryUsage = 0;
            double elapsedTime = 0;
            double longestTime = LONG_MIN;
            double shortestTime = LONG_MAX;
            double sumOfTime = 0;
            double averageTime = 0;
            fprintf(file_time, "\n%d,", numberOfElements);
            fprintf(file_memory, "\n%d,", numberOfElements);

            for (int i = 0; i < 100; i++) {
                getrusage(RUSAGE_SELF, &usage);
                clock_gettime(CLOCK_MONOTONIC, &timeStart);
                insertNodesSplaytree(numberOfElements);
                clock_gettime(CLOCK_MONOTONIC, &timeEnd);
                memoryUsage = usage.ru_maxrss;
                fprintf(file_memory, "%ld,", memoryUsage);
                fprintf(file_time, "%f,", elapsedTime);
                elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
                if(longestTime < elapsedTime) longestTime = elapsedTime;
                if(shortestTime > elapsedTime) shortestTime = elapsedTime;
                sumOfTime += elapsedTime;
            }
            //Print
            averageTime = sumOfTime / 100;
            fprintf(file_shortest_time, "%f,", shortestTime);
            fprintf(file_average_time, "%f,", averageTime);
            fprintf(file_longest_time, "%f,", longestTime);
        }
        numberOfElements += 10;
    }
    fclose(file_time);
    fclose(file_memory);
    fclose(file_shortest_time);
    fclose(file_average_time);
    fclose(file_longest_time);
}

int main() {
    testDoubleLinkedList();
    testSplaytree();
    return 0;
}




