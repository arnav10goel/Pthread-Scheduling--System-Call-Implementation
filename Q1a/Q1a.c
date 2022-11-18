#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

struct timespec startA, stopA;
struct timespec startB, stopB;
struct timespec startC, stopC;

void countA(){
    if( clock_gettime( CLOCK_REALTIME, &startA) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param = {.sched_priority = 9};

    pthread_setschedparam(pthread_self(), SCHED_OTHER, &param); 
    long long int i;
    long long int n = pow(2,32);
    for(i=1; i <= n;i++){
    }
}

void countB(){
    if( clock_gettime( CLOCK_REALTIME, &startB) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param = {.sched_priority = 16};

    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param); 
    long long int i;
    long long int n = pow(2,32);
    for(i=1; i <= n;i++){
    }

}

void countC(){
    if( clock_gettime( CLOCK_REALTIME, &startC) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param = {.sched_priority = 80};
    pthread_setschedparam(pthread_self(), SCHED_RR, &param); 
    
    long long int i;
    long long int n = pow(2,32);
    for(i=1; i <= n;i++){
    }
}

int main(){
    
    pthread_t thrA, thrB, thrC;
    double resA;
    double resB;
    double resC;

    pthread_create(&thrA, NULL, (void *)&countA, NULL);
    pthread_create(&thrB, NULL, (void *)&countB, NULL);
    pthread_create(&thrC, NULL, (void *)&countC, NULL);
    
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
    resA = (stopA.tv_sec - startA.tv_sec) + ( stopA.tv_nsec - startA.tv_nsec ) / 1000000000.0;
    resB = (stopB.tv_sec - startB.tv_sec) + ( stopB.tv_nsec - startB.tv_nsec ) / 1000000000.0;
    resC = (stopC.tv_sec - startC.tv_sec) + ( stopC.tv_nsec - startC.tv_nsec ) / 1000000000.0;
    
    printf("Thread A (SCHED_OTHER): %f\n", resA);
    printf("Thread B (SCHED_FIFO): %f\n", resB);
    printf("Thread C (SCHED_RR): %f\n", resC);
    return 0;
}
