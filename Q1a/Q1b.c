#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>

int main(int argc, char **argv) {
    struct timespec start[3], stop[3];
    int policy[3] = {SCHED_OTHER, SCHED_FIFO, SCHED_RR};
    pid_t children[3];

    for (int i = 0; i < 3; i++ ) {
        if( clock_gettime( CLOCK_REALTIME, &start[i]) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
        children[i] = fork();
        if(children[i] == 0){
            long long int n = (pow(2,32)-1);
            for(long long int i = 1; i <= n;i++){
            }
            if(execl("/bin/sh", "bash", "script.sh", NULL) == -1){
                printf("Exec call failed\n");
            }
        }
    }
    int ret;
    for (int i = 0; i < 3; i++ ) {   // Waiting all 3 children process finish
        waitpid(children[i], &ret, 0);
        if( clock_gettime( CLOCK_REALTIME, &stop[i]) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
    }

    double time_OTHER, time_FIFO, time_RR;

    time_OTHER = ( stop[0].tv_sec - start[0].tv_sec ) + ( stop[0].tv_nsec - start[0].tv_nsec ) / 1000000000.0;
    time_FIFO = ( stop[1].tv_sec - start[1].tv_sec ) + ( stop[1].tv_nsec - start[1].tv_nsec ) / 1000000000.0;
    time_RR = ( stop[2].tv_sec - start[2].tv_sec ) + ( stop[2].tv_nsec - start[2].tv_nsec ) / 1000000000.0;

    printf("Time taken by SCHED_OTHER: %f\n", time_OTHER);
    printf("Time taken by SCHED_FIFO: %f\n", time_FIFO);
    printf("Time taken by SCHED_RR: %f\n", time_RR);
}
