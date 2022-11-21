#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <sched.h>

struct timespec startA, stopA;
struct timespec startB, stopB;
struct timespec startC, stopC;

void countA(int priority){
    if( clock_gettime( CLOCK_REALTIME, &startA) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param = {.sched_priority = priority};
    //int ret = setpriority(PRIO_PROCESS, 0, priority);
    int rc_set = pthread_setschedparam(pthread_self(), SCHED_OTHER, &param); 
    printf("RC SET A: %i\n", rc_set);
    long long int i;
    long long int n = pow(2,32);
    for(i=1; i <= n;i++){
    }
    if( clock_gettime( CLOCK_REALTIME, &stopA) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param1;
    int policy1;
    int rc = pthread_getschedparam(pthread_self(), &policy1, &param1);
    //int priority2 = getpriority(PRIO_PROCESS, 0);
    printf("Thread A priority: %d\n", param1.sched_priority);
    printf("RC GET A: %i\n", rc);
}

void countB(int priority){
    if( clock_gettime( CLOCK_REALTIME, &startB) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param = {.sched_priority = priority};

    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param); 
    long long int i;
    long long int n = pow(2,32);
    for(i=1; i <= n;i++){
    }
    if( clock_gettime( CLOCK_REALTIME, &stopB) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param1;
    int policy1;
    int rc = pthread_getschedparam(pthread_self(), &policy1, &param1);
    printf("Thread B priority: %d\n", param1.sched_priority);
    printf("Thread B policy: %d\n", policy1);
}

void countC(int priority){
    if( clock_gettime( CLOCK_REALTIME, &startC) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param = {.sched_priority = priority};
    pthread_setschedparam(pthread_self(), SCHED_RR, &param); 
    
    long long int i;
    long long int n = pow(2,32);
    for(i=1; i <= n;i++){
    }
    if( clock_gettime( CLOCK_REALTIME, &stopC) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    struct sched_param param1;
    int policy1;
    int rc = pthread_getschedparam(pthread_self(), &policy1, &param1);
    printf("Thread C priority: %d\n", param1.sched_priority);
    printf("Thread C policy: %d\n", policy1);
}

int main(){
    int priority_a, priority_b, priority_c;
    printf("Enter priority for A (value b/w -19 and 20): ");
    scanf("%d", &priority_a);
    printf("Enter priority for B (value b/w 0 and 99): ");
    scanf("%d", &priority_b);
    printf("Enter priority for C (value b/w 0 and 99): ");
    scanf("%d", &priority_c);

    pthread_t thrA, thrB, thrC;
    double resA;
    double resB;
    double resC;

    pthread_create(&thrA, NULL, (void *)&countA, (void*)priority_a);
    pthread_create(&thrB, NULL, (void *)&countB, (void*)priority_b);
    pthread_create(&thrC, NULL, (void *)&countC, (void*)priority_c);
    
    pthread_join(thrA, NULL);
    // if( clock_gettime( CLOCK_REALTIME, &stopA) == -1 ) {
    //   perror( "clock gettime" );
    //   exit( EXIT_FAILURE );
    // }

    pthread_join(thrB, NULL);
    // if( clock_gettime( CLOCK_REALTIME, &stopB) == -1 ) {
    //   perror( "clock gettime" );
    //   exit( EXIT_FAILURE );
    // }

    pthread_join(thrC, NULL);
    // if( clock_gettime( CLOCK_REALTIME, &stopC) == -1 ) {
    //   perror( "clock gettime" );
    //   exit( EXIT_FAILURE );
    // }
    resA = (stopA.tv_sec - startA.tv_sec) + ( stopA.tv_nsec - startA.tv_nsec ) / 1000000000.0;
    resB = (stopB.tv_sec - startB.tv_sec) + ( stopB.tv_nsec - startB.tv_nsec ) / 1000000000.0;
    resC = (stopC.tv_sec - startC.tv_sec) + ( stopC.tv_nsec - startC.tv_nsec ) / 1000000000.0;
    
    printf("Thread A (SCHED_OTHER): %f\n", resA);
    printf("Thread B (SCHED_FIFO): %f\n", resB);
    printf("Thread C (SCHED_RR): %f\n", resC);
    return 0;
}
