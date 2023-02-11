#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <SDL/SDL.h>

void* FctThread(void *para);
void handlerSIGALRM(int sig);

int main()
{

    struct sigaction sigAct;

    sigset_t mask;
    sigemptyset(&mask);

    sigemptyset(&sigAct.sa_mask);
    sigAct.sa_handler = handlerSIGALRM;
    sigAct.sa_flags = 0;

    sigaction(SIGALRM, &sigAct, NULL);
    
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK, &mask, NULL);

	pthread_t hThread;
	
	printf("thread principal (id = %u) : debut\n", pthread_self());
	
	pthread_create(&hThread, NULL, FctThread, NULL);

    alarm(5);
	
	pthread_join(hThread, NULL);

    
	printf("thread principal: fin\n", hThread);
    
	exit(0);	
}


void* FctThread(void *para)
{
    struct timespec temps = { 1, 500000000 };

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
        
	printf("thread secondaire id = %d : debut\n", pthread_self());
	
    // alarm(5);

    pause();
	
	printf("thread secondaire id = %d : fin\n", pthread_self());
	
	pthread_exit(0);
}

void handlerSIGALRM(int sig)
{
    printf("SIGALRM pour le thread %u\n",pthread_self());
    exit(0);
}
