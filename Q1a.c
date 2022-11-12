#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

void countA(){
    long long int i;
    for(i=0;i < (pow(2,32)-1);i++){
        int a = 'A';
    }
}

void countB(){
    long long int i;
    for(i=0; i < (pow(2,32)-1);i++){
        int a = 'B';
    }
}

void countC(){
    long long int i;
    for(i=0; i < (pow(2,32)-1);i++){
        int a = 'A';
    }
}

int main(){
    pthread_t thrA, thrB, thrC;
    pthread_create(&thrA, NULL, (void *)countA, NULL);
    pthread_create(&thrB, NULL, (void *)countB, NULL);
    pthread_create(&thrC, NULL, (void *)countC, NULL);
    pthread_join(thrA, NULL);
    pthread_join(thrB, NULL);
    pthread_join(thrC, NULL);
    return 0;
}