#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void init();
void cleanup();
void *barber(void*);
void *customer(void*);

pthread_mutex_t barber_lock;

pthread_cond_t customer_come;
pthread_cond_t barber_available;
pthread_cond_t customer_come;
pthread_cond_t customer_done;
pthread_cond_t barber_done;

int customers = 0;
const int total = 4;
int barber_status;
int customer_status;

int main(int argc, char **argv)
{
  int nthreads = 5;
  init();

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

void init()
{
  pthread_mutex_init(&barber_lock, NULL);

  pthread_cond_init(&customer_come, NULL);
  pthread_cond_init(&barber_available, NULL);
  pthread_cond_init(&customer_done, NULL);
  pthread_cond_init(&barber_done, NULL);
}

void cleanup()
{
  pthread_mutex_destroy(&barber_lock);

  pthread_cond_destroy(&customer_come);
  pthread_cond_destroy(&barber_available);
  pthread_cond_destroy(&customer_done);
  pthread_cond_destroy(&barber_done);
}

void *barber(void*v)
{
  while (1) {
    pthread_mutex_lock(&barber_lock);
    if (customers == 0)
      pthread_cond_wait(&customer_come, &barber_lock);
    else
      pthread_cond_signal(&barber_available);
    barber_status = 0;
    pthread_mutex_unlock(&barber_lock);
    
    /* customer acquired. haitcut starting */

    printf("%s\n", "barber: next customer!");
    sleep(1);

    pthread_mutex_lock(&barber_lock);
    barber_status = 1;
    if (customer_status)
      pthread_cond_signal(&barber_done);
    else
      pthread_cond_wait(&customer_done, &barber_lock);
    pthread_mutex_unlock(&barber_lock);
    printf("%s\n", "barber: haircut finish");
  }
  pthread_exit(NULL);
}

void *customer(void*v)
{
  static int customer_no = 0;
  int customer_id=0;
  pthread_mutex_lock(&barber_lock);
  printf("customer %d enters barbershop\n", customer_id=customer_no++);
  if (customers == total) {
    printf("customer %d will go back barber full\n", customer_id);
    pthread_mutex_unlock(&barber_lock);
    pthread_exit(NULL);
  }
  else if (customers == 0) {
    printf("customer %d will wake barber. barber empty\n", customer_id);
    customers++;
    pthread_cond_signal(&customer_come);
  }
  else {
    customers++;
    printf("customer %d will wait in queue. current customers: %d\n", customer_id, customers);
    pthread_cond_wait(&barber_available, &barber_lock);
    printf("customer %d now its my turn\n", customer_id);
    customer_status = 0;
  }
  pthread_mutex_unlock(&barber_lock);

  /* barber will now cut my hair */

  printf("customer %d: barber is now cutting my hair\n", customer_id);
  sleep(1);

  pthread_mutex_lock(&barber_lock);
  customer_status = 1;
  if (barber_status) {
    printf("customer %d: haircut finished. notifying barber\n", customer_id);
    pthread_cond_signal(&customer_done);
  }
  else {
    printf("customer %d: haircut finished. waiting barber\n", customer_id);
    pthread_cond_wait(&barber_done, &barber_lock);
  }
  customers--;
  printf("customer %d: leaving barbershop. %d customer left\n", customer_id, customers);
  pthread_mutex_unlock(&barber_lock);

  pthread_exit(NULL);
}
