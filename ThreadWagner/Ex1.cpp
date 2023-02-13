#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>
#include <SDL/SDL.h>
#include <fcntl.h>

struct data
{
    char nomFichier[15];
    char mot[15];
    short nbTab;
};


void* FctThread(void *);
// void* FctThread2(void *);
// void* FctThread3(void *);
// void* FctThread4(void *);

int main()
{
    int * compteur[4];
    pthread_t thread[4];
    char mot[4][15] = {"printf", "cout", "dans", "cible"};
    char nomFichier[4][15] = {"fichier1.txt", "fichier2.txt", "fichier3.txt", "fichier4.txt"};
    int i;
    // struct data a;

	//etape 2

    // pthread_create(&thread[0], NULL, FctThread, NULL);
    // pthread_create(&thread[1], NULL, FctThread2, NULL);
    // pthread_create(&thread[2], NULL, FctThread3, NULL);
    // pthread_create(&thread[3], NULL, FctThread4, NULL);

    for(i=0;i<4;i++)
    {

        struct data *a = (struct data *)malloc(sizeof(struct data));

        strcpy(a->nomFichier, nomFichier[i]);
        strcpy(a->mot, mot[i]);
        a->nbTab=i;

        pthread_create(&thread[i], NULL, FctThread, a);
    }
        
    for(i=0;i<4;i++)
        pthread_join(thread[i], (void**)&compteur[i]);

    for(i=0;i<4;i++)
        printf("\n compteur = %d\n", *compteur[i]);

	exit(0);	
}

//etape3

void* FctThread(void *param)
{
    int fichier;
    int compteur=0;
    int i=0, end=0;
    struct data* data = (struct data*) param;
    char buffer[10];

    printf("%d\n", data->nbTab);

    while(end==0)
    {
        if((fichier = open(data->nomFichier, O_RDONLY))==-1)
        {
            printf("impossible d'ouvrir le fichier\n");
            exit(1);
        }

        for(i=0;i<data->nbTab;i++)
            printf("\t");

        printf("*\n");

        lseek(fichier, i, SEEK_SET);

        if(read(fichier, buffer, strlen(data->mot))!=strlen(data->mot))
            end=1;

        close(fichier);

        if(strcmp(buffer, data->mot)==0)
            compteur++;

        i++;
    }

    pthread_exit(&compteur);
}



//etape 2


// void* FctThread(void *param)
// {
    
//     int fichier;
//     static int compteur=0;
//     int i=0, end=0;
//     char buffer[10];


//     while(end==0)
//     {
//         if((fichier = open("fichier1.txt", O_RDONLY))==-1)
//         {
//             printf("impossible d'ouvrir le fichier\n");
//             exit(1);
//         }

//         printf("*\n");

//         lseek(fichier, i, SEEK_SET);

//         if(read(fichier, buffer, 6)!=6)
//             end=1;

//         close(fichier);

//         if(strcmp(buffer, "printf")==0)
//             compteur++;

//         i++;
//     }

// 	pthread_exit(&compteur);
// }

// void* FctThread2(void *param)
// {
    
//     int fichier;
//     static int compteur=0;
//     int i=0, end=0;
//     char buffer[10];


//     while(end==0)
//     {
//         if((fichier = open("fichier2.txt", O_RDONLY))==-1)
//         {
//             printf("impossible d'ouvrir le fichier\n");
//             exit(1);
//         }

//         printf("\t*\n");

//         lseek(fichier, i, SEEK_SET);

//         if(read(fichier, buffer, 4)!=4)
//             end=1;

//         close(fichier);

//         if(strcmp(buffer, "cout")==0)
//             compteur++;

//         i++;
//     }

// 	pthread_exit(&compteur);
// }
// void* FctThread3(void *param)
// {
    
//     int fichier;
//     static int compteur=0;
//     int i=0, end=0;
//     char buffer[10];


//     while(end==0)
//     {
//         if((fichier = open("fichier3.txt", O_RDONLY))==-1)
//         {
//             printf("impossible d'ouvrir le fichier\n");
//             exit(1);
//         }

//         printf("\t\t*\n");

//         lseek(fichier, i, SEEK_SET);

//         if(read(fichier, buffer, 4)!=4)
//             end=1;

//         close(fichier);

//         if(strcmp(buffer, "dans")==0)
//             compteur++;

//         i++;
//     }

// 	pthread_exit(&compteur);
// }
// void* FctThread4(void *param)
// {
    
//     int fichier;
//     static int compteur=0;
//     int i=0, end=0;
//     char buffer[10];


//     while(end==0)
//     {
//         if((fichier = open("fichier4.txt", O_RDONLY))==-1)
//         {
//             printf("impossible d'ouvrir le fichier\n");
//             exit(1);
//         }

//         printf("\t\t\t*\n");

//         lseek(fichier, i, SEEK_SET);

//         if(read(fichier, buffer, 5)!=5)
//             end=1;

//         close(fichier);

//         if(strcmp(buffer, "cible")==0)
//             compteur++;

//         i++;
//     }

// 	pthread_exit(&compteur);
// }


