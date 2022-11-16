#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv) {
    int run_time[3];    // Variable to save the running time of the children process
    struct timespec start[3];        // Variable to help measure the actual time
    struct timespec stop[3];
    pid_t children[3];
    int status;
    int i;

    for ( i = 0; i < 3; i++ ) {
        // Start time of child process
        if( clock_gettime( CLOCK_REALTIME, &start[i]) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
        children[i] = fork();
        if( children[i] == 0 )  {
            for(long long int i=0;i < (pow(2,32)-1);i++){
            }
	    execl("/bin/ls", "ls", NULL);
        }
    }
    for ( i = 0; i < 3; i++ ) {   // Waiting all 3 children process finish
        waitpid(children[i], &status, 0);
        if( clock_gettime( CLOCK_REALTIME, &stop[i]) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
        if (WIFEXITED(status)) {
            run_time[i] = WEXITSTATUS(status); // use the low-order 8 bits from the exit code
        } else {
            run_time[i] = -1; // unknown run time
        }
    }

    for(int i = 0; i < 3; i++){
        double time = (stop[i].tv_sec - start[i].tv_sec) + (stop[i].tv_nsec - start[i].tv_nsec) / 1000000000.0;
        printf("%f\n", time);
    }

}
