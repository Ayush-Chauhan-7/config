#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>



void fcaller1(){
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int pid1 = fork();
    struct sched_param schedp1;
    schedp1.sched_priority=0;
    sched_setscheduler(pid1,SCHED_OTHER,&schedp1);
    if (pid1 == 0){
        // execlp("/bin/bash","sh","bash1.sh",NULL);
        sleep(10);
    }
    else{
        int waitid1 = wait(NULL);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec+e1.tv_nsec-s1.tv_nsec);
        ans/=(double)1e9;
        printf("----------RunTime for first thread: %lfs----------\n",(ans));
    }
}

void fcaller2(){
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int pid2 = fork();
    struct sched_param schedp2;
    schedp2.sched_priority=1;
    sched_setscheduler(pid2, SCHED_FIFO, &schedp2);
    if (pid2 == 0){
        // execlp("/bin/bash","sh","bash1.sh",NULL);
        sleep(10);
    }
    else{
        int waitid1 = wait(NULL);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec+e1.tv_nsec-s1.tv_nsec);
        ans/=(double)1e9;
        printf("----------RunTime for second thread: %lfs----------\n",(ans));
    }
}

void fcaller3(){
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int pid3 = fork();
    struct sched_param schedp3;
    schedp3.sched_priority=0;
    sched_setscheduler(pid3,SCHED_RR,&schedp3);
    if (pid3 == 0){
        // execlp("/bin/bash","sh","bash1.sh",NULL);
        sleep(10);
    }
    else{
        int waitid1 = wait(NULL);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec+e1.tv_nsec-s1.tv_nsec);
        ans/=(double)1e9;
        printf("----------RunTime for third thread: %lfs----------\n",(ans));
    }
}


int main(){
    pid_t pid1, pid2, pid3;





    pid1 = fork();
    pid2 = fork();
    pid3 = fork();
    if(pid1==0 && pid2!=0 && pid3!=0){
       fcaller1();
    }

    else if(pid2==0 && pid1!=0 && pid3!=0){
        fcaller2();
    }

    else if(pid3==0 && pid2!=0 && pid1!=0){
        fcaller3();
    }

}