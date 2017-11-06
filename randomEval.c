#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void RandGenerator(int numOfInstances){
    srand((unsigned int)time(NULL));

    for (int i = 0; i < numOfInstances; i++) {
        //random number generator between 0-40
        printf("%d \n", rand() % 41);
    }
}

int main() {
    RandGenerator(10000);
};

