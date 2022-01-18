/* compile: gcc spinlock.c -o spinlock.o -pthread  */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
static pthread_spinlock_t splock;

void *compute()
{
    int i = 0;
//    pthread_spin_lock(&splock);
    while (i < 10000) {
        counter = counter + 1;
        i++;
    }
//    pthread_spin_unlock(&splock);
    printf("Counter value: %d\n", counter);
}

int main()
{
    pthread_t thread1, thread2, thread3, thread4, thread5;
    if (pthread_spin_init(&splock, 0) != 0)
    {
        printf("spin init failed\n");
        return 1;
    }

    pthread_create(&thread1, NULL, compute, (void *)&thread1);
    pthread_create(&thread2, NULL, compute, (void *)&thread2);
    pthread_create(&thread3, NULL, compute, (void *)&thread3);
    pthread_create(&thread4, NULL, compute, (void *)&thread4);
    pthread_create(&thread5, NULL, compute, (void *)&thread5);

    pthread_exit(NULL);
    pthread_spin_destroy(&splock);
    exit(0);
}
