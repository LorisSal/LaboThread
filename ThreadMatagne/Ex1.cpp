#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <SDL/SDL.h>

void* FctThread(void *);

int main()
{
    pthread_t tab[4];
    int i;
	
	printf("thread principal : debut\n");

    for(i=0;i<4;i++)
    {
        int *p = (int *)malloc(sizeof(int));

        *p=i;
        
        pthread_create(&tab[i], NULL, FctThread, p);
    }
	
    for(i=0;i<4;i++)
	    pthread_join(tab[i], NULL);

	exit(0);	
}


void* FctThread(void *param)
{
    struct timespec temps = { 1, 500000000 };
    
	printf("thread secondaire : debut\n");
	
	printf("valeur du parametre = %d\n", *(int *)param);
	
	free(param);
	
	nanosleep(&temps, NULL);//null = temps qui reste a attendre
	
	printf("thread naire %d : fin\n", pthread_self());
	
	pthread_exit(0);
}
