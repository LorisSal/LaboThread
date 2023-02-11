#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <SDL/SDL.h>

void* FctThread(void *);
void* FctThread2(void *);
void* FctThread3(void *);

void handlerSIGALRM(int);
void handlerSIGUSR1(int);
void handlerSIGUSR2(int);

int main()
{
    pthread_t tab[3];
    int i;
    
    struct sigaction sigAct;

    sigset_t mask;
    sigemptyset(&mask);

    sigAct.sa_flags = 0;
    sigemptyset(&sigAct.sa_mask);

    sigAct.sa_handler = handlerSIGALRM;
    sigaction(SIGALRM, &sigAct, NULL);
    sigaddset(&mask, SIGALRM);

    sigAct.sa_handler = handlerSIGUSR1;
    sigaction(SIGUSR1, &sigAct, NULL);
    sigaddset(&mask, SIGUSR1);

    sigAct.sa_handler = handlerSIGUSR2;
    sigaction(SIGUSR2, &sigAct, NULL);
    sigaddset(&mask, SIGUSR2);

    sigprocmask(SIG_BLOCK, &mask, NULL);

    struct timespec temps = { 2, 000000000 };
	
	printf("thread principal : debut\n");

    pthread_create(&tab[0], NULL, FctThread, NULL);
    pthread_create(&tab[1], NULL, FctThread2, NULL);
    pthread_create(&tab[2], NULL, FctThread3, NULL);

    alarm(5);

    nanosleep(&temps, NULL);

    pthread_kill(tab[1], SIGUSR1);
    pthread_kill(tab[2], SIGUSR2);
	
    for(i=0;i<3;i++)
	    pthread_join(tab[i], NULL);
	
	printf("id thread principal = %u : fin\n", pthread_self());

	exit(0);	
}


void* FctThread(void *para)
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
        
	printf("thread Alarm id = %u : debut\n", pthread_self());
	
    pause();
	
	pthread_exit(0);
}
void* FctThread2(void *para)
{

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
        
	printf("thread SIGSUR1 id = %u : debut\n", pthread_self());

    pause();
	
	printf("thread SIGSUR1 id = %u : fin\n", pthread_self());
	
	pthread_exit(0);
}

void* FctThread3(void *para)
{

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
        
	printf("thread SIGSUR2 id = %u : debut\n", pthread_self());

    pause();
	
	printf("thread SIGSUR2 id = %u : fin\n", pthread_self());
	
	pthread_exit(0);
}

void handlerSIGALRM(int sig)
{
    printf("SIGALRM pour le thread (%u)\n", (unsigned int)pthread_self());
}
void handlerSIGUSR1(int sig)
{
    printf("SIGUSR1 pour le thread (%u)\n", (unsigned int)pthread_self());
}
void handlerSIGUSR2(int sig)
{
    printf("SIGUSR2 pour le thread (%u)\n", (unsigned int)pthread_self());
}

