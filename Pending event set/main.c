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
    int numberOfElements = 0;

    FILE *file_time, *file_memory, *file_shortest_time, *file_average_time, *file_longest_time;
    file_time = fopen("Event_DoubleLinkedList_Time_Raw", "w+");
    file_memory = fopen("Event_DoubleLinkedList_Memory_Raw", "w+");
    file_shortest_time = fopen("Event_DoubleLinkedList_Best", "w+");
    file_average_time = fopen("Event_DoubleLinkedList_Avg", "w+");
    file_longest_time = fopen("Event_DoubleLinkedList_Worst", "w+");

    while(numberOfElements <= 1000) {
        fprintf(file_shortest_time, "\n%d,", numberOfElements);
        fprintf(file_average_time, "\n%d,", numberOfElements);
        fprintf(file_longest_time, "\n%d,", numberOfElements);
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
                int random;
                int num = numberOfElements;
                getrusage(RUSAGE_SELF, &usage);
                clock_gettime(CLOCK_MONOTONIC, &timeStart);
                //while number of elements to insert is bigger than 9, we will generate 0 - 10 new elements.
                createNewDoubleLinkedList();
                while(num > 0) {
                    if (num < 9) {
                        insertElementsDoubleLinkedList(num);
                        num = 0;
                    } else {
                        random = rand() % 10 + 1;
                        printf("Random: %d\n", random);
                        num = num - random;
                        insertElementsDoubleLinkedList(random);
                        deleteNode();
                    }
                }
                clock_gettime(CLOCK_MONOTONIC, &timeEnd);
                memoryUsage = usage.ru_maxrss;
                fprintf(file_memory, "%ld,", memoryUsage);
                elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
                fprintf(file_time, "%f,", elapsedTime);
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

// Test - Best, avg, worse time and memory to insert n (10-1000) values, with an increase of
// 10 per test and with 100 runs per test
void testSplaytree() {
    srand((unsigned int) time(NULL));
    struct timespec timeStart, timeEnd;
    struct rusage usage;
    int numberOfElements = 0;

    FILE *file_time, *file_memory, *file_shortest_time, *file_average_time, *file_longest_time;
    file_time = fopen("Event_Splaytree_Time_Raw", "w+");
    file_memory = fopen("Event_Splaytree_Memory_Raw", "w+");
    file_shortest_time = fopen("Event_Splaytree_Best", "w+");
    file_average_time = fopen("Event_Splaytree_Avg", "w+");
    file_longest_time = fopen("Event_Splaytree_Worst", "w+");

    while(numberOfElements <= 1000) {
        fprintf(file_shortest_time, "\n%d,", numberOfElements);
        fprintf(file_average_time, "\n%d,", numberOfElements);
        fprintf(file_longest_time, "\n%d,", numberOfElements);
        for (int i = 0; i < 1; i++) {
            long memoryUsage = 0;
            double elapsedTime = 0;
            double longestTime = LONG_MIN;
            double shortestTime = LONG_MAX;
            double sumOfTime = 0;
            double averageTime = 0;
            fprintf(file_time, "\n%d,", numberOfElements);
            fprintf(file_memory, "\n%d,", numberOfElements);
            createNewSplayTree();
            for (int i = 0; i < 1; i++) {
                int random;
                int num = numberOfElements;
                getrusage(RUSAGE_SELF, &usage);
                clock_gettime(CLOCK_MONOTONIC, &timeStart);
                //while number of elements to insert is bigger than 9, we will generate 0 - 10 new elements.
                while(num > 0) {
                    if (num < 9) {
                        insertNodesSplaytree(num);
                        num = 0;
                    } else {
                        random = rand() % 10 + 1;
                        printf("Random: %d\n", random);
                        num = num - random;
                        insertNodesSplaytree(random);
                        deleteNode();
                    }
                }
                clock_gettime(CLOCK_MONOTONIC, &timeEnd);
                memoryUsage = usage.ru_maxrss;
                fprintf(file_memory, "%ld,", memoryUsage);
                elapsedTime = converterToSeconds(&timeEnd) - converterToSeconds(&timeStart);
                fprintf(file_time, "%f,", elapsedTime);
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

int main() {
    testDoubleLinkedList();
    testSplaytree();
    return 0;
}
