#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>
#include <SDL/SDL.h>
#include <fcntl.h>

void* FctSlave(void *);
void* FctMaster(void *);
void fctMasterFin(void *);
void handlerSIGINT(int);
void handlerSIGUSR1(int);

int main()
{

    pthread_t Slave[4];
    pthread_t Master;
    int i;

    struct sigaction sigAct;
    sigset_t mask;

    sigemptyset(&mask);

        
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);


    sigemptyset(&sigAct.sa_mask);
    sigAct.sa_flags = 0;

    sigAct.sa_handler = handlerSIGUSR1;
    sigaction(SIGUSR1, &sigAct, NULL);

    sigAct.sa_handler = handlerSIGINT;
    sigaction(SIGINT, &sigAct, NULL);


    printf("Thread principale id = %u\n", pthread_self());

    for(i=0;i<4;i++)
        pthread_create(&Slave[i], NULL, FctSlave, NULL);
    
    pthread_create(&Master, NULL, FctMaster, NULL);

        
    for(i=0;i<4;i++)
        pthread_join(Slave[i], NULL);

    pthread_cancel(Master); 

    pthread_join(Master, NULL);

	exit(0);	
}

void* FctSlave(void *param)
{

    sigset_t mask;
    sigemptyset(&mask);

    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);


    printf("Slave : Attente d'un signal (id = %u)\n", pthread_self());

    pause();

    pthread_exit(0);
}

void * FctMaster(void *param)
{
    sigset_t mask;
    sigemptyset(&mask);

    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    pthread_cleanup_push(fctMasterFin,NULL); 

    if(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL)) 
        puts("Erreur de setcancelstate"); 

    if(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)) 
        puts("Erreur de setcanceltype"); 

    printf("Master : Attente d'un signal (id = %u)\n", pthread_self());

    while(1)
    {
        pause();
    }

    pthread_cleanup_pop(1);//le mettre avant de exit

    pthread_exit(0);


}

void fctMasterFin(void * param)
{
    printf("\nMaster se termine (id = %u)\n", pthread_self());

}

void handlerSIGINT(int sig)
{
    printf("\nSignal SIGINT recu (id = %u)\n", pthread_self());

    kill(getpid(),SIGUSR1);
}
void handlerSIGUSR1(int sig)
{
    printf("\nSignal SIGUSR1 recu (id = %u)\n", pthread_self());
}


