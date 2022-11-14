#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#define BILLION  1000000000L;

void countA(){
    long long int i;
    for(i=0;i < (pow(2,32)-1);i++){
    }
}

void countB(){
    long long int i;
    for(i=0; i < (pow(2,32)-1);i++){
    }

}

void countC(){
    long long int i;
    for(i=0; i < (pow(2,32)-1);i++){
    }
}

int main(){
    struct timespec startA, stopA;
    struct timespec startB, stopB;
    struct timespec startC, stopC;
    pthread_t thrA, thrB, thrC;
    double resA;
    double resB;
    double resC;
    pthread_create(&thrA, NULL, (void *)&countA, NULL);
    if( clock_gettime( CLOCK_REALTIME, &startA) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    pthread_create(&thrB, NULL, (void *)&countB, NULL);
    if( clock_gettime( CLOCK_REALTIME, &startB) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    pthread_create(&thrC, NULL, (void *)&countC, NULL);
    if( clock_gettime( CLOCK_REALTIME, &startC) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    pthread_join(thrA, NULL);
    if( clock_gettime( CLOCK_REALTIME, &stopA) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    pthread_join(thrB, NULL);
    if( clock_gettime( CLOCK_REALTIME, &stopB) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    pthread_join(thrC, NULL);
    if( clock_gettime( CLOCK_REALTIME, &stopC) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    resA = ( stopA.tv_nsec - startA.tv_nsec );
    resB = ( stopB.tv_nsec - startB.tv_nsec );
    resC = ( stopC.tv_nsec - startC.tv_nsec );
    printf("Thread A: %f\n", resA);
    printf("Thread B: %f\n", resB);
    printf("Thread C: %f\n", resC);
    return 0;
}