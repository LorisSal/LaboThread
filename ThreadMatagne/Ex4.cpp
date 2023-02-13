#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>
#include <SDL/SDL.h>
#include <fcntl.h>

void* FctThread(void *);
void destructeur(void* p);
void handlerSIGUSR1(int);

pthread_key_t cle;


int main()
{
    pthread_t thread[3];
    int i;
    
    struct timespec temps = { 2, 000000000 };

    struct sigaction sigAct;

    sigAct.sa_handler = handlerSIGUSR1;
    sigemptyset(&sigAct.sa_mask);
    sigaction(SIGUSR1, &sigAct, NULL);
    

    pthread_key_create(&cle, destructeur);

    for(i=0;i<3;i++)
    {
        int *p = (int *)malloc(sizeof(int));

        *p=i+1;
        
        pthread_create(&thread[i], NULL, FctThread, p);
    }

    nanosleep(&temps, NULL);

    for(i=0;i<3;i++)
        pthread_kill(thread[i], SIGUSR1);
        
    for(i=0;i<3;i++)
        pthread_join(thread[i], NULL);


	exit(0);	
}

void* FctThread(void *param)
{
    int *p = (int*)param;

    pthread_setspecific(cle, (const void*)p);


    printf("thread %d : debut (id = %u)\n", *p, pthread_self());

    pause();

    printf("thread %d : fin (id = %u)\n", *p, pthread_self());


    pthread_exit(0);
}
void handlerSIGUSR1(int sig)
{
    int *var = (int*)pthread_getspecific(cle);

    printf("SIGUSR1 pour le thread (%u)\n", *var, (unsigned int)pthread_self());
}
void destructeur(void* p)
{
    printf("Destructeur de la variable specifique pour le thread (%u)\n",(unsigned int)pthread_self());

    free(p);
}