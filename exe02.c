#include <pthread.h>
#include <semaphore.h>

pthread_t t0, t1, t2;

sem_t s0, s1, s2;

int buffer;

void *thread0()
{
  for(int i = 0; i < 100; i++)
  {
    sem_wait(&s0);
    buffer = i;
    sem_post(&s1);
  }
}

void *thread1()
{
  int consumidor;
  for(int i = 0; i < 100; i++)
  {
    sem_wait(&s1);
    consumidor = buffer;
    printf("Consumi: %d\n", consumidor);
    sem_post(&s0);
  }
}

int main()
{
  sem_init(&s0, 0, 1);
  sem_init(&s1, 0, 0);

  pthread_create(&t0, NULL, thread0, NULL);
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
}
