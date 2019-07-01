#include <pthread.h>
#include <semaphore.h>

pthread_t t0, t1, t2;

sem_t s0, s1, s2;

void *thread0()
{
  while(1)
  {
    sem_wait(&s0);
    printf("Olá, eu sou o thread 1\n");
    sleep(1);
    sem_post(&s1);
  }
}

void *thread1()
{
  while(1)
  {
    sem_wait(&s1);
    printf("Olá, eu sou o thread 2\n");
    sleep(1);
    sem_post(&s2);
  }
}

void *thread2()
{
  while(1)
  {
    sem_wait(&s2);
    printf("Olá, eu sou o thread 3\n");
    sleep(1);
    sem_post(&s0);
  }
}

int main()
{
  sem_init(&s0, 0, 1);
  sem_init(&s1, 0, 0);
  sem_init(&s2, 0, 0);

  pthread_create(&t0, NULL, thread0, NULL);
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);

  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}
