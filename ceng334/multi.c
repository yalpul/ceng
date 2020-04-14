#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<semaphore.h>

enum Direction { READER, WRITER};
char *tostring[] = {"reader","writer"};

pthread_mutex_t totmut = PTHREAD_MUTEX_INITIALIZER;
int total = 0;

int counter[2] = { 0, 0 };      // # of readers and  writers
sem_t *readerwriter[2];			// a semaphore for each type of threads
sem_t *mutex;					// a general mutex for protection

void cleanup() {
	sem_unlink("readerlock");
	sem_unlink("writerlock");
	sem_unlink("mutex");
}

void init() {
	readerwriter[0] = sem_open("readerlock", O_CREAT, 0666, 1);
	if (readerwriter[0] == SEM_FAILED)
		exit(1);
	readerwriter[1] = sem_open("writerlock", O_CREAT, 0666, 1);
	if (readerwriter[1] == SEM_FAILED)
		exit(1);
	mutex = sem_open("mutex", O_CREAT, 0666, 1);
	if (mutex == SEM_FAILED)
		exit(1);
}

void enter(enum Direction dir) {///fill in here
  sem_wait(readerwriter[dir]);
  if (counter[dir] == 0)
    sem_wait(mutex);
  counter[dir]++;
  sem_post(readerwriter[dir]);
}


void leave(enum Direction dir) { /// fill in here
  sem_wait(readerwriter[dir]);
  counter[dir]--;
  if (counter[dir] == 0)
    sem_post(mutex);
  sem_post(readerwriter[dir]);
}


void *process_thread(void *p)
{
	enum Direction d = *(enum Direction *) p;
	free(p);
	enter(d);
	printf("entered %s, count %d\n", tostring[d], counter[d]);
	usleep(rand() % 400);
	leave(d);
	printf("left %s, count %d total %d\n", tostring[d], counter[d], total);
	pthread_mutex_lock(&totmut);
	total = total + 1;
	pthread_mutex_unlock(&totmut);
	return NULL;
}

#define thread_num 1000
int main() {
	int i;
	pthread_t tno[thread_num];
  int threads[thread_num] = {0};
	//pthread_attr_t at;
	//pthread_attr_init(&at);
	//pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);
	init();
  int actual = 0;
	for (i=0 ; i < thread_num; i++) { // create 10000 threads randomly
		int *p;
		p = malloc(sizeof(int));
		*p = rand() % 2;		// reader or writer
    threads[i] = 0 == pthread_create(tno+i, NULL, process_thread, (void *) p);
    actual += threads[i];
	}

	for (i=0; i < thread_num; i++)
    if (threads[i])
      pthread_join(tno[i],NULL);
  printf("actual %d\n", actual);
  cleanup();

	return 0;
}

