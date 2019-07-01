#include <pthread.h>
#include <semaphore.h>
#define NUM 100

pthread_t t0, t1, t2, t3;

int buffer[NUM];

sem_t s0, s1, s2, s3;

void *thread0()
{
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s0);
    buffer[i] = rand()%10000;
    printf("Buffer[%d]: %d\n", i, buffer[i]);
    sem_post(&s1);
  }
}

void *thread1()
{
  int result;
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s1);
    printf("Thread1 realiza calculo\n");
    result = buffer[i];
    result = result + 7;
    printf("Result: %d\n", result);
    buffer[i] = result;
    printf("Buffer: %d\n", buffer[i]);
    sem_post(&s2);
  }
}

void *thread2()
{
  int result;
  for(int i = 0; i < NUM; i++)
  {
    sem_wait(&s2);
    printf("Thread2 realiza calculo\n");
    result = buffer[i];
    result = result + 2;
    printf("Result: %d\n", result);
    buffer[i] = result;
    printf("Buffer: %d\n", buffer[i]);
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
