//Nolan Jaeger
//CS4504
//Project-pthread
//Kevin Suo
//Fall 2021
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX 10240
#define NUM_THREADS  10

int n1,n2;
char *s1,*s2;
FILE *fp;
int countArray[NUM_THREADS]={0};
int total;


//read input file and generate string s1/s2 and length n1/n2
int readf(FILE *fp)
{
	if((fp=fopen("strings.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
	return 0;
}

int num_substring(int t)
{
    int i,j,k;
    int count;

    long tid = (long)t;

    for (i = ((n1/10) * tid); i < (((n1/10) * tid)+n1/10)-n2; i++)
    {
        count =0;
        for(j = i, k = 0; k < n2; j++, k++)
        {
            if (*(s1 + j) != *(s2 + k))
            {
                break;
            }
            else
            {
                count++;
            }
            if(count == n2)
            {
                countArray[tid] = countArray[tid] + 1;
            }
        }
    }
    return countArray[tid];
}

void *calSubStringThread(void *threadid){
    long tid = (long)threadid;
    printf("The number of substrings thread %ld ", tid);
    int num = num_substring(tid);
    printf("has is: %d\n", num);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int t, rc;

	readf(fp);

	for(t=0; t<NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, calSubStringThread, (void *) (size_t)t);
	sleep(1);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    for(int i = 0; i < 10; i++)
    {
        total = total + countArray[i];
    }

    for(t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }

 	printf("Total substrings is: %d\n", total);
	return 0;
}










