#include <pthread.h>
#include <semaphore.h>
#define NUM 50

pthread_t t0, t1, t2, t3;
sem_t s0, s1, s2, s3, s4, s5, s6;

int a, b, c;

void *servidor()
{
  for(int i = 0; i < NUM; i++)
  {
    int buffer = rand()%NUM;
    sem_wait(&s1);
    a = buffer;
    sem_wait(&s2);
    b = buffer;
    sem_wait(&s3);
    c = buffer;
    sem_post(&s4);
    sem_post(&s5);
    sem_post(&s6);
  }
}

void *consum1()
{
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s4);
    printf("Valor do A: %d\n", a);
    sem_post(&s1);
  }
}

void *consum2()
{
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s5);
    printf("Valor do B: %d\n", b);
    sem_post(&s2);
  }
}

void *consum3()
{
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s6);
    printf("Valor do C: %d\n", c);
    sem_post(&s3);
  }
}

int main()
{
  sem_init(&s1, 0, 1);
  sem_init(&s2, 0, 1);
  sem_init(&s3, 0, 1);
  sem_init(&s4, 0, 0);
  sem_init(&s5, 0, 0);
  sem_init(&s6, 0, 0);

  pthread_create(&t0, NULL, servidor, NULL);
  pthread_create(&t1, NULL, consum1, NULL);
  pthread_create(&t2, NULL, consum2, NULL);
  pthread_create(&t3, NULL, consum3, NULL);

  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
}
