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
    FILE *f;
    f = fopen("times.txt","a");
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int pid1 = fork();
    struct sched_param schedp1;
    schedp1.sched_priority=0;
    sched_setscheduler(pid1,SCHED_OTHER,&schedp1);
    if (pid1 == 0){
        execlp("/bin/bash","sh","bash1.sh",NULL);
    }
    else if (pid1 > 0){
        int waitid1 = wait(NULL);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec)+(e1.tv_nsec-s1.tv_nsec)/(double)1e9;
        fprintf(f,"%lf\n",(ans));
    }
    fclose(f);
}

void fcaller2(){
    FILE *f;
    f = fopen("times.txt","a");
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int pid2 = fork();
    struct sched_param schedp2;
    schedp2.sched_priority=1;
    sched_setscheduler(pid2, SCHED_FIFO, &schedp2);
    if (pid2 == 0){
        execlp("/bin/bash","sh","bash2.sh",NULL);
    }
    else if(pid2 > 0){
        int waitid1 = wait(NULL);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec)+(e1.tv_nsec-s1.tv_nsec)/(double)1e9;
        fprintf(f,"%lf\n",(ans));
    }
    fclose(f);
}

void fcaller3(){
    FILE *f;
    f = fopen("times.txt","a");
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int pid3 = fork();
    struct sched_param schedp3;
    schedp3.sched_priority=0;
    sched_setscheduler(pid3,SCHED_RR,&schedp3);
    if (pid3 == 0){
        execlp("/bin/bash","sh","bash3.sh",NULL);
    }
    else if(pid3 > 0){
        int waitid1 = wait(NULL);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec)+(e1.tv_nsec-s1.tv_nsec)/(double)1e9;
        fprintf(f,"%lf\n",(ans));
    }
    fclose(f);
}


int main(){
    pid_t pid1, pid2, pid3;
    int id = fork();
    if(id==0)
    {
        fcaller1();
    }
    else
    {
        int id2 = fork();
        if(id2==0)
        {
            fcaller2();
        }
        else
        {
            int id3 = fork();
            if(id3==0)
            {
                fcaller3();
            }
            wait(NULL);
        }
        wait(NULL);
    }
    wait(NULL);
}