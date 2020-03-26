#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t customer_sem;
sem_t customer_done;
sem_t barber_sem;
sem_t barber_done;

pthread_mutex_t mutex;

void init(void);
void cleanup(void);
void *barber(void*);
void *customer(void*);

int customers = 0;
const int n = 4;

int main()
{
    init();

    int nthreads = 5;
    pthread_t clients[15];
    pthread_t barber_t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
  
  
    pthread_create(&barber_t, &attr, barber, NULL);
    for (int i = 0; i < nthreads; i++)
      pthread_create(&clients[i], &attr, customer, NULL);
    sleep (3);
    for (int i = nthreads; i < 2*nthreads; i++)
      pthread_create(&clients[i], &attr, customer, NULL);
    usleep (2500000);
    for (int i = 2*nthreads; i < 3*nthreads; i++)
      pthread_create(&clients[i], &attr, customer, NULL);
  
    for (int i = 0; i < 3*nthreads; i++)
      pthread_join(clients[i], NULL);
    pthread_cancel(barber_t);

    cleanup();

    return 0;
}


void init(void)
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&customer_sem, 0, 0);
    sem_init(&customer_done, 0, 0);
    sem_init(&barber_sem, 0, 0);
    sem_init(&barber_done, 0, 0);
}

void cleanup(void)
{
    pthread_mutex_destroy(&mutex);
    sem_destroy(&customer_sem);
    sem_destroy(&customer_done);
    sem_destroy(&barber_sem);
    sem_destroy(&barber_done);
}

void *barber(void*v)
{
    for(;;) {
        sem_post(&barber_sem);
        printf("%s\n", "barber: ready for next customer");
        sem_wait(&customer_sem);
        printf("%s\n", "barber: next customer!");

        /* cut hair here */
        sleep(1);

        sem_post(&barber_done);
        printf("%s\n", "barber: finished haircut!");
        sem_wait(&customer_done);
    }

    pthread_exit(NULL);
}

void *customer(void*v)
{
    static int customer_count = 0;
    int customer_id = 0;
    pthread_mutex_lock(&mutex);
    customer_id = customer_count++;
    printf("customer %d: enters barbershop!\n", customer_id);
    if (customers == n) {
        printf("customer %d: barbershop full. leaving!\n", customer_id);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    customers++;
    printf("customer %d: %d customers waiting!\n", customer_id, customers);
    pthread_mutex_unlock(&mutex);

    sem_post(&customer_sem);
    printf("customer %d: waiting for haircut!\n", customer_id);
    sem_wait(&barber_sem);
    printf("customer %d: now gets haircut!\n", customer_id);

    /* haircut here */
    sleep(1);

    sem_post(&customer_done);
    printf("customer %d: finished haircut!\n", customer_id);
    sem_wait(&barber_done);

    pthread_mutex_lock(&mutex);
    customers--;
    printf("customer %d: leaving barbershop. %d customers left\n", customer_id, customers);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
