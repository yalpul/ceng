#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define PASS_BRIDGE 1

void *north_farmer(void*);
void *south_farmer(void*);
pthread_mutex_t bridge_lock;

int main(int argc, char **argv)
{
  int north_farmers = atoi(argv[1]);
  int south_farmers = atoi(argv[2]);
  int i;

  pthread_t north_farmers_t[north_farmers];
  pthread_t south_farmers_t[south_farmers];
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_mutex_init(&bridge_lock, NULL);

  for (i = 0; i < north_farmers; i++)
    pthread_create(&north_farmers_t[i], &attr, north_farmer, (void*)(long)i);
  for (i = 0; i < south_farmers; i++)
    pthread_create(&south_farmers_t[i], &attr, south_farmer, (void*)(long)i);

  for (i = 0; i < north_farmers; i++)
    pthread_join(north_farmers_t[i], NULL);
  for (i = 0; i < south_farmers; i++)
    pthread_join(south_farmers_t[i], NULL);
  return 0;
}

void *south_farmer(void *v)
{
  int farmer_id = (int)v;
  pthread_mutex_lock(&bridge_lock);
  printf("South village farmer %d is passing the bridge\n", farmer_id);
  sleep(PASS_BRIDGE);
  pthread_mutex_unlock(&bridge_lock);
  printf("South village farmer %d has passed the bridge\n", farmer_id);

  pthread_exit(0);
}

void *north_farmer(void *v)
{
  int farmer_id = (int)v;
  pthread_mutex_lock(&bridge_lock);
  printf("North village farmer %d is passing the bridge\n", farmer_id);
  sleep(PASS_BRIDGE);
  pthread_mutex_unlock(&bridge_lock);
  printf("North village farmer %d has passed the bridge\n", farmer_id);

  pthread_exit(0);
}
