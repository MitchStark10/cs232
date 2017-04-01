#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

// A normal C function that is executed as a thread when its name
// is specified in pthread_create()
sem_t customerSemaphore;
sem_t bakerSemaphore;
int customers = 0;
bool customerWaiting = false;
int breadAvailable = 0;

void bakerCheckout() {
    printf("Customer waiting to checkout...");
    sem_wait(&bakerSemaphore);
    //CRITICAL SECTION
    printf("Thread has just checked out!");
    sem_post(&bakerSemaphore);
}

void *customerActions(void *vargp)
{
    sem_wait(&customerSemaphore);
    //CRITICAL SECTION
    printf("Printing hello from customer\n");

    //request bread
    while(breadAvailable == 0) {
        printf("Customer waiting for bread...");
    }

    breadAvailable--;
    printf("Customer received bread!");
    //pay
    bakerCheckout();
    //Finish the crtical section
    customers--;
    sem_post(&customerSemaphore);
    return NULL;
}

void bakeBread() {
    while(customers != 0) {
        sem_wait(&bakerSemaphore);
        //CRITICAL SECTION
        breadAvailable++;
        printf("Baker just baked a single loaf of bread");
        sem_post(&bakerSemaphore);
    }
    printf("Baker is completely done baking loaves of bread.");
}

void initSemaphores() {
    sem_init(&customerSemaphore, 0, 1);
    sem_init(&bakerSemaphore, 0, 1);
}

int main()
{
    initSemaphores();
    printf("---Creating Threads---\n");
    for(int i = 0; i < 10; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, customerActions, NULL);
    }
    pthread_exit(NULL);
    printf("---All customers have finished---\n");
    exit(0);
}
