#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <vector>

// A normal C function that is executed as a thread when its name
// is specified in pthread_create()
sem_t customerSemaphore;
sem_t bakerSemaphore;
vector threadIds;
int customers = 0;
int breadBaked = 0;
bool customerWaiting = false;
int breadAvailable = 0;

void bakerCheckout() {
    printf("Customer waiting to checkout...\n");
    sem_wait(&bakerSemaphore);
    //CRITICAL SECTION
    printf("Thread has just checked out!\n");
    sem_post(&bakerSemaphore);
}

void *customerActions(void *vargp)
{
    threadIds.push_back(syscall(SYS_gettid));
    sem_wait(&customerSemaphore);
    //CRITICAL SECTION
    printf("Customer \n");

    //request bread
    while(breadAvailable == 0) {
        printf("Customer waiting for bread...\n");
    }

    breadAvailable--;
    printf("Customer received bread!\n");
    //pay
    bakerCheckout();
    //Finish the crtical section
    customers--;
    sem_post(&customerSemaphore);
    return NULL;
}

void *bakeBread() {
    while(breadBaked != 10) {
        sem_wait(&bakerSemaphore);
        //CRITICAL SECTION
        breadAvailable++;
	      breadBaked++;
        printf("Baker just baked a single loaf of bread\n");
        sem_post(&bakerSemaphore);
    }
    printf("Baker is completely done baking loaves of bread.\n");
}

void initSemaphores() {
    sem_init(&customerSemaphore, 0, 1);
    sem_init(&bakerSemaphore, 0, 1);
}

int main()
{
    initSemaphores();
    printf("---Creating Threads---\n");
    pthread_t bakeBreadId;
    pthread_create(&bakeBreadId, NULL, bakeBread, NULL);
    for(int i = 0; i < 10; i++) {
        customers++;
        pthread_t tid;
        pthread_create(&tid, NULL, customerActions, NULL);
    }
    pthread_exit(NULL);
    printf("---All customers have finished---\n");
    exit(0);
}
