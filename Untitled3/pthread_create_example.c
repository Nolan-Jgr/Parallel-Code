#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_THREADS     5

void *doSomeThing(void *t)
{
        long tid = (long)t;
        printf("Thread id is %ld\n", tid);
        pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
        pthread_t threads[NUM_THREADS];
        int t;
        for(t=0;t<NUM_THREADS;t++){
                pthread_create(&threads[t], NULL, doSomeThing, (void *)(intptr_t)t);
        }
        pthread_exit(NULL);
}
