#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int count = 0;

void *myThread1(void)
{
    int i;
    for (i=0; i<3; i++)
    {
        printf("This is the 1st pthread.\n");
        count++;
        sleep(1);
    }
}


int main()
{
    int ret=0;
    pthread_t id1;

    printf("This is main thread!\n");

    ret = pthread_create(&id1, NULL, (void*)myThread1, NULL);
    if (ret)
    {
        printf("Create pthread error!/n");
        return 1;
    }

    pthread_join(id1, (void *)ret);

    printf("count:%d\n", count);
    pthread_exit(NULL);

    return 0;
}


