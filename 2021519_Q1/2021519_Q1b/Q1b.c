#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <sched.h>

int main(int argc, char **argv) {
    struct timespec start[3], stop[3];
    int policy[3] = {SCHED_OTHER, SCHED_FIFO, SCHED_RR};
    char* paths[3] = {"script1.sh", "script2.sh", "script3.sh"};
    pid_t children[3];
    struct sched_param param_fifo, param_rr;

    int nice_val, sched_fifo_priority, sched_rr_priority;
    printf("Enter nice value for Process A - SCHED_OTHER (value b/w -20 and 19): ");
    scanf("%d", &nice_val);
    printf("Enter priority for Process B - SCHED_FIFO (value b/w 1 and 99): ");
    scanf("%d", &sched_fifo_priority);
    printf("Enter priority for Process C - SCHED_RR (value b/w 1 and 99): ");
    scanf("%d", &sched_rr_priority);
    
    if( clock_gettime( CLOCK_REALTIME, &start[0]) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    children[0] = fork();
    if(children[0] < 0){
        printf("Error in forking child 1\n");
    }
    else if(children[0] == 0){
        int ret = nice(nice_val);
        if(ret == -1){
            printf("Error in nice\n");
           
        }
        else{
            printf("Nice value of Child Process 1 (SCHED_OTHER) is: %d\n", ret);
        }
        
        int rc = sched_getscheduler(getpid());
        if(rc == -1){
            printf("Error in sched_getscheduler\n");
        }
        else{
            printf("Policy of Child Process 1 (SCHED_OTHER) is: %d\n", rc);
        }
        struct sched_param param0;
        int prio1 = sched_getparam(getpid(), &param0);
        printf("Priority of Child Process 1 (SCHED_OTHER) is: %d\n", param0.sched_priority);

	    fflush(stdout);
        if(execl("/bin/sh", "bash", paths[0], NULL) == -1){
            printf("Exec call failed\n");
        }
    }
    else{
        if( clock_gettime( CLOCK_REALTIME, &start[1]) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
        }
        children[1] = fork();
        if(children[1] < 0){
            printf("Error in forking child 2\n");
        }
        else if(children[1] == 0){
            param_fifo.sched_priority = sched_fifo_priority;
            int ret = sched_setscheduler(getpid(), policy[1], &param_fifo);
            if(ret == -1){
                perror("sched_setscheduler");
                exit(EXIT_FAILURE);
            }
            
            struct sched_param param2;
            int prio2 = sched_getparam(getpid(), &param2);
            int policy2 = sched_getscheduler(getpid());
            printf("Policy of Child Process 2 (SCHED_FIFO) is: %d\n", policy2);
            printf("Priority of Child Process 2 (SCHED_FIFO) is: %d\n", param2.sched_priority);
    
            fflush(stdout);
            if(execl("/bin/sh", "bash", paths[1], NULL) == -1){
                printf("Exec call failed\n");
            }
        }
        else{
            if( clock_gettime( CLOCK_REALTIME, &start[2]) == -1 ) {
                perror( "clock gettime" );
                exit( EXIT_FAILURE );
            }
            children[2] = fork();
            if(children[2] == 0){
                param_rr.sched_priority = sched_rr_priority;
                int ret = sched_setscheduler(getpid(), policy[2], &param_rr);
                if(ret == -1){
                    perror("sched_setscheduler");
                    exit(EXIT_FAILURE);
                }
                
                struct sched_param param3;
                int prio3 = sched_getparam(getpid(), &param3);
                int policy3 = sched_getscheduler(getpid());
                printf("Policy of Child Process 3 (SCHED_RR) is: %d\n", policy3);
                printf("Priority of Child Process 3 (SCHED_RR) is: %d\n", param3.sched_priority);
                fflush(stdout);
                if(execl("/bin/sh", "bash", paths[2], NULL) == -1){
                    printf("Exec call failed\n");
                }
            }
        }
    }

    int* test = malloc(sizeof(int));
    for (int i = 0; i < 3; i++ ) {   //Using waitpid() to wait for a particular child process and 
        waitpid(children[i], test, 0);
        if( clock_gettime( CLOCK_REALTIME, &stop[i]) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
    }

    double time_OTHER, time_FIFO, time_RR;

    time_OTHER = ( stop[0].tv_sec - start[0].tv_sec ) + ( stop[0].tv_nsec - start[0].tv_nsec ) / 1000000000.0;
    time_FIFO = ( stop[1].tv_sec - start[1].tv_sec ) + ( stop[1].tv_nsec - start[1].tv_nsec ) / 1000000000.0;
    time_RR = ( stop[2].tv_sec - start[2].tv_sec ) + ( stop[2].tv_nsec - start[2].tv_nsec ) / 1000000000.0;

    printf("Time taken by Child Process 1 - SCHED_OTHER: %f\n", time_OTHER);
    printf("Time taken by Child Process 2 - SCHED_FIFO: %f\n", time_FIFO);
    printf("Time taken by Child Process 3 - SCHED_RR: %f\n", time_RR);
}
