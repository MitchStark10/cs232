/*
Created by: Mitch Stark (mjs73)
Date completed: April 4, 2017
Bakeshop implementation using semaphores/threading
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/syscall.h>

//This semaphore only admits one customer to request bread/pay/checkout at a time.
sem_t customerSemaphore;

//This semaphore ensures that the baker is either baking or at the cash register,
//but not both
sem_t bakerSemaphore;

//This semaphore ensures that only 5 people are allowed into the store at a time.
sem_t storeSemaphore;

//This is the 10 threads to be used (and referenced for id numbers)
pthread_t tid[10];

int customers = 0;
int breadBaked = 0;
bool customerWaiting = false;
int breadAvailable = 0;


//Return the number of the thread
int getThreadNum() {
    pthread_t id = pthread_self();
    int i;
    for(i = 0; i < 10; i++) {
        if (pthread_equal(id, tid[i])) {
            return i;
        }
    }

    return -1;
}

//Allows the customer to checkout
//Ensures that the baker is not currently baking bread
void bakerCheckout() {
    printf("Customer [%d] waiting to checkout...\n", getThreadNum());
    sem_wait(&bakerSemaphore);
    //CRITICAL SECTION
    sleep(1);
    printf("Baker has just printed a receipt for customer [%d]\n", getThreadNum());
    sem_post(&bakerSemaphore);
}

//The starting place of each customer thread.
//5 may enter the store, 1 can request bread/checkout at a time.
void *customerActions(void *vargp)
{
    if (getThreadNum() == 9) {
        pthread_setschedprio(pthread_self(), 0);
    }
    printf("Customer [%d] attempting to enter the store...\n", getThreadNum());
    sem_wait(&storeSemaphore);
    printf("Customer [%d] entered the store!\n", getThreadNum());

    sem_wait(&customerSemaphore);
    //request bread
    printf("Customer [%d] waiting for bread...\n", getThreadNum());
    while(breadAvailable == 0) {
      	sleep(0.1); //sleep, check again
    }

    breadAvailable--;
    printf("Customer [%d] received bread!\n", getThreadNum());
    sleep(2);
    //pay
    printf("Customer [%d] has paid!\n", getThreadNum());
    bakerCheckout();
    printf("Customer [%d] has now taken the receipt and left the store\n", getThreadNum());
    //Finish the crtical section
    customers--;
    sem_post(&customerSemaphore);
    sem_post(&storeSemaphore);
    return NULL;
}

//This is the thread that the baker is automatically entered into.
//The baker bakes bread until 10 pieces of bread have been bakeed.
//The baker waits at the semaphore when a customer needing to checkout grabs hold.
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

//inits semaphores, store starts at 5, all others start at 1
void initSemaphores() {
    sem_init(&customerSemaphore, 0, 1);
    sem_init(&bakerSemaphore, 0, 1);
    sem_init(&storeSemaphore, 0, 5);
}

//starting place of the program, starts up all of the threads, and waits
//for them to complete
int main()
{
    initSemaphores();
    printf("---Creating Threads---\n");
    pthread_t bakeBreadId;
    pthread_create(&bakeBreadId, NULL, bakeBread, NULL);
    int i;
    for(i = 0; i < 10; i++) {
        customers++;
        pthread_create(&tid[i], NULL, customerActions, NULL);
    }
    pthread_exit(NULL);
    printf("---All customers have finished---\n");
    exit(0);
}
