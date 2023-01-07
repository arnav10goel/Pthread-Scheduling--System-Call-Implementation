# OS Assignment 2

The following repository provides the solutions to Assignment 2 given during the course Operating Systems (CSE-231) at IIITD during the Monsoon'22 semester. The description is as follows:

## Question 1
### Part A (Scheduling of Pthreads)
This required us to generate three pthreads which count from 1 to 2<sup>32</sup>. We need to use the system call `pthread_sched_setparam()` to schedule the three threads using different scheduling policies. The policies are:
- `SCHED_OTHER`
- `SCHED_FIFO`
- `SCHED_RR`

We are then supposed to time the counting of the three threads. We then need to compare the times taken by changing the priority values for `SCHED_FIFO` and `SCHED_RR` and the Nice Value for `SCHED_OTHER` and then plot histograms to illustrate the difference.

### Part B
This required us to schedule 3 processes which were all child processes of the same parent process. They must be scheduled using the same policies as in Part A. However this time, we are supposed to compile 3 different Linux kernels version `5.19.8` by making 3 separate bash scripts which each process executes. We then time each of the processes by changing the priority and NICE values and plot a histogram for the same to illustrate the difference.

## Question 2 (System Call Implementation)
For this, we implement our own custom Linux System Call `kernel_2d_memcpy` which makes use of the system calls `copy_from_user()` and `copy_to_user()` which takes a 2D matrix as input and copies it to the required target matrix.

## End
All the program logics and explanations are given with the code in the respective folders and can be referenced accordingly.
