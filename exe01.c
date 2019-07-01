#include <pthread.h>
#include <semaphore.h>
#define NUM 40

pthread_t t0, t1, t2, t3;
sem_t s0, s1;
int buffer;

void *prod()
{
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s0);
    buffer = i;
    sem_post(&s1);
  }
}

void *cons()
{
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s1);
    int consumidor = buffer;
    printf("Consumi: %d\n", consumidor);
    sem_post(&s0);
  }
}

int main()
{
  sem_init(&s0, 0, 1);
  sem_init(&s1, 0, 0);

  pthread_create(&t0, NULL, prod, NULL);
  pthread_create(&t1, NULL, cons, NULL);
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
}
