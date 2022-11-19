#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#include<sched.h>



int main(){
     
    printf("MAX_OTHER: %i\n", sched_get_priority_max(SCHED_OTHER));
    printf("MIN_OTHER: %i\n", sched_get_priority_min(SCHED_OTHER));
    printf("MAX_RR: %i\n", sched_get_priority_max(SCHED_RR));
    printf("MIN_RR: %i\n", sched_get_priority_min(SCHED_RR));
    printf("MAX_FIFO: %i\n", sched_get_priority_max(SCHED_FIFO));
    printf("MIN_FIFO: %i\n", sched_get_priority_min(SCHED_FIFO));
}