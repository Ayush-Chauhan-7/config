#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <sched.h>

#define BILLION  1000000000.0

typedef struct { double x; } Double;


void countA(){
    long int count = 0;
    unsigned int i = 0;
    while(i<UINT_MAX){
        count++;
        i += 1;
    }
}

void* p1caller(){
    struct sched_param paramA;
    paramA.sched_priority = 0;
    struct timespec start;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &paramA);
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    struct timespec end;
    Double *ptr = malloc(sizeof(Double));
    clock_gettime(CLOCK_REALTIME, &end);
    ptr->x = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / (double)1e9;
    return (void*)ptr;
}

void countB(){
    long int count = 0;
    unsigned int i = 0;
    while(i<UINT_MAX){
        count++;
        i += 1;
    }
}

void* p2caller(void *f){
    struct sched_param paramB;
    paramB.sched_priority = 1;
    struct timespec start;
    pthread_setschedparam(pthread_self(), SCHED_RR, &paramB);
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    struct timespec end;
    Double *ptr = malloc(sizeof(Double));
    clock_gettime(CLOCK_REALTIME, &end);
    ptr->x = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / (double)1e9;
    return (void*)ptr;
}

void countC(){
    long int count = 0;
    unsigned int i = 0;
    while(i<UINT_MAX){
        count++;
        i += 1;
    }
}

void* p3caller(void *f){
    struct sched_param paramC;
    paramC.sched_priority = 1;
    struct timespec start;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &paramC);
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    struct timespec end;
    Double *ptr = malloc(sizeof(Double));
    clock_gettime(CLOCK_REALTIME, &end);
    ptr->x = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / (double)1e9;
    return (void*)ptr;
}

int main(){
    pthread_t ThreadA;
    Double *r1;
    pthread_create(&ThreadA, NULL, &p1caller,NULL);
    pthread_t ThreadB;
    Double *r2;
    pthread_create(&ThreadB, NULL, &p2caller, NULL);
    pthread_t ThreadC;
    Double *r3;
    pthread_create(&ThreadC, NULL, &p3caller, NULL);
    pthread_join(ThreadA, (void **)&r1);
    pthread_join(ThreadB, (void **)&r2);
    pthread_join(ThreadC, (void **)&r3);
    printf("%lf %lf %lf",r1->x,r2->x,r3->x);
}
