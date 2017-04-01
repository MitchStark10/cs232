#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/syscall.h>

// A normal C function that is executed as a thread when its name
// is specified in pthread_create()
sem_t customerSemaphore;
sem_t bakerSemaphore;
sem_t storeSemaphore;
pthread_t tid[10];
int customers = 0;
int breadBaked = 0;
bool customerWaiting = false;
int breadAvailable = 0;

int getThreadNum() {
    pthread_t id = pthread_self();
    for(int i = 0; i < 10; i++) {
        if (pthread_equal(id, tid[i])) {
            return i;
        }
    }

    return -1;
}

void bakerCheckout() {
    printf("Customer [%d] waiting to checkout...\n", getThreadNum());
    sem_wait(&bakerSemaphore);
    //CRITICAL SECTION
    sleep(1);
    printf("Customer [%d] has just checked out!\n", getThreadNum());
    sem_post(&bakerSemaphore);
}

void *customerActions(void *vargp)
{
    printf("Customer [%d] attempting to enter the store...", getThreadNum());
    sem_wait(&storeSemaphore);
        printf("Customer [%d] entered the store!", getThreadNum());
    sem_post(&storeSemaphore)

    sem_wait(&customerSemaphore);
    //CRITICAL SECTION
    printf("Customer [%d] has entered the store...\n", getThreadNum());

    //request bread
    printf("Customer [%d] waiting for bread...\n", getThreadNum());
    while(breadAvailable == 0) {
	//busy wait
    }

    breadAvailable--;
    printf("Customer [%d] received bread!\n", getThreadNum());
    sleep(2);
    //pay
    bakerCheckout();
    //Finish the crtical section
    customers--;
    sem_post(&customerSemaphore);
    return NULL;
}

void *bakeBread() {
    printf("Bread baker is ready to work!\n");
    while(breadBaked != 10) {
        sem_wait(&bakerSemaphore);
        //CRITICAL SECTION
        breadAvailable++;
	      breadBaked++;
        printf("Baker just baked a single loaf of bread\n");
        sem_post(&bakerSemaphore);
        sleep(1);
    }
    printf("Baker is completely done baking loaves of bread.\n");
}

void initSemaphores() {
    sem_init(&customerSemaphore, 0, 1);
    sem_init(&bakerSemaphore, 0, 1);
    sem_init(&storeSemaphore, 0, 10);
}

int main()
{
    initSemaphores();
    printf("---Creating Threads---\n");
    pthread_t bakeBreadId;
    pthread_create(&bakeBreadId, NULL, bakeBread, NULL);
    for(int i = 0; i < 10; i++) {
        customers++;
        sleep(1);
        pthread_create(&tid[i], NULL, customerActions, NULL);
    }
    pthread_exit(NULL);
    printf("---All customers have finished---\n");
    exit(0);
}
