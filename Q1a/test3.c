#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
    int pid, pid2, pid3;
    struct timespec startA, stopA;
    struct timespec startB, stopB;
    struct timespec startC, stopC;
    int a = 0;
    pid = fork();
    if(pid == 0)
    {
        if( clock_gettime( CLOCK_REALTIME, &startA) == -1 ) {
          perror( "clock gettime" );
          exit( EXIT_FAILURE );
        }
        printf("Child process 1\n");
        a++;
        
    }
    else if(pid < 0){
        printf("Fork Failed\n");
    }
    else
    {
        pid2 = fork();
        if(pid2 < 0){
            printf("Fork failed\n");
        }
        else if(pid2 == 0){
            if( clock_gettime( CLOCK_REALTIME, &startB) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
            }
            printf("Child process 2\n");
            a++;
        }
        else{
            pid3 = fork();
            if(pid3 < 0){
                printf("Fork failed\n");
            }
            else if(pid3 == 0){
                if( clock_gettime( CLOCK_REALTIME, &startC) == -1 ) {
                perror( "clock gettime" );
                exit( EXIT_FAILURE );
                }
                printf("Child process 3\n");
                a++;
            }
            else{
                waitpid(pid3, NULL, WNOHANG);
                if( clock_gettime( CLOCK_REALTIME, &stopC) == -1 ) {
                    perror( "clock gettime" );
                    exit( EXIT_FAILURE );
                }
            }
            waitpid(pid2, NULL, WNOHANG);
            if( clock_gettime( CLOCK_REALTIME, &stopB) == -1 ) {
                perror( "clock gettime" );
                exit( EXIT_FAILURE );
            }
        }
        waitpid(pid, NULL, WNOHANG);
        if( clock_gettime( CLOCK_REALTIME, &stopA) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
        double resA = ( stopA.tv_nsec - startA.tv_nsec );
        double resB = ( stopB.tv_nsec - startB.tv_nsec );
        double resC = ( stopC.tv_nsec - startC.tv_nsec );
        printf("Child Process 1: %f\n", resA);
        printf("Child Process 2: %f\n", resB);
        printf("Child Process 3: %f\n", resC);
    }
    return 0;
}