#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// A normal C function that is executed as a thread when its name
// is specified in pthread_create()
sem_t customerSemaphore;
int customers = 0;


void *customerActions(void *vargp)
{
    sem_close(&customerSemaphore);
    sleep(1);
    printf("Printing hello from Thread \n");
    printf(customers);
    printf("\n");
    customers--;
    sem_post(&customerSemaphore);
    return NULL;
}

int main()
{
    sem_init(&customerSemaphore, 0, 1);
    printf("---Creating Threads---\n");
    for(int i = 0; i < 10; i++) {
        customers++;
        pthread_t tid;
        pthread_create(&tid, NULL, customerActions, NULL);
    }
    pthread_exit(NULL);
    printf("---All customers have finished---\n");
    exit(0);
}
