#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <wchar.h>
#include <locale.h>

sem_t remain, apple, pear, mutex;
static unsigned int nremain = 3, napple = 0, npear = 0;

void *father(void *);
void *mather(void *);
void *son(void *);
void *daughter(void *);

int main() {
    pthread_t fa, ma, so, da;
    setlocale(LC_ALL, "en_US.utf8");

    sem_init(&remain, 0, 3);
    sem_init(&apple, 0, 0);
    sem_init(&pear, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&fa, NULL, &father, NULL);
    pthread_create(&ma, NULL, &mather, NULL);
    pthread_create(&so, NULL, &son, NULL);
    pthread_create(&da, NULL, &daughter, NULL);

    for(;;);
}

void *father(void *arg) {
    while(1) {
        sleep(5);  //simulate peel apple
        sem_wait(&remain);
        sem_wait(&mutex);
        printf("father  %lc: before put apple, remain=%u, apple%lc =%u, pear%lc =%u\n",
                0x1F468, nremain, 0x1F34E, napple, 0x1F350, npear);
        nremain--;
        napple++;
        printf("father  %lc: after  put apple, remain=%u, apple%lc =%u, pear%lc =%u\n\n",
                0x1F468, nremain, 0x1F34E, napple, 0x1F350, npear);
        sem_post(&mutex);
        sem_post(&apple);
    }
}

void *mather(void *arg) {
    while(1) {
        sleep(7);   //simulate peel pear
        sem_wait(&remain);
        sem_wait(&mutex);
        printf("mother  %lc: before put pear , remain=%u, apple%lc =%u, pear%lc =%u\n",
                0x1F469, nremain, 0x1F34E, napple, 0x1F350, npear);
        nremain--;
        npear++;
        printf("mother  %lc: after  put pear , remain=%u, apple%lc =%u, pear%lc =%u\n\n",
                0x1F469, nremain, 0x1F34E, napple, 0x1F350, npear);
        sem_post(&mutex);
        sem_post(&pear);
    }
}

void *son(void *arg) {
    while(1) {
        sem_wait(&pear);
        sem_wait(&mutex);
        printf("son     %lc: before eat pear , remain=%u, apple%lc =%u, pear%lc =%u\n",
                0x1F466, nremain, 0x1F34E, napple, 0x1F350, npear);
        nremain++;
        npear--;
        printf("son     %lc: after  eat pear , remain=%u, apple%lc =%u, pear%lc =%u\n\n",
                0x1F466, nremain, 0x1F34E, napple, 0x1F350, npear);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(10); //simulate eat pear
    }
}

void *daughter(void *arg) {
    while(1) {
        sem_wait(&apple);
        sem_wait(&mutex);
        printf("daughter%lc: before eat apple, remain=%u, apple%lc =%u, pear%lc =%u\n",
                0x1F467, nremain, 0x1F34E, napple, 0x1F350, npear);
        nremain++;
        napple--;
        printf("daughter%lc: after  eat apple, remain=%u, apple%lc =%u, pear%lc =%u\n\n",
                0x1F467, nremain, 0x1F34E, napple, 0x1F350, npear);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(10); //simulate eat apple
    }
}



