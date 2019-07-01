#include <pthread.h>
#include <semaphore.h>

pthread_t t0, t1, t2, t3;

sem_t s0, s1, s2, s3;

int buffer[132];

void *produtor()
{
  int valor;
  for(int i = 0; i < 132; i++)
  {
    sem_wait(&s0);
    valor = rand()%1000;
    buffer[i] = valor;
    sem_post(&s1);
  }
}

void *consumidor()
{
  int consumi;
  
  for(int i = 0; i < 132; i++)
  {
    sem_wait(&s1);
    consumi = buffer[i];
    printf("Consumi %d: %d\n", i, buffer[i]);
    sem_post(&s0);
  }
}

int main()
{
  sem_init(&s0, 0, 1);
  sem_init(&s1, 0, 0);

  pthread_create(&t0, NULL, produtor, NULL);
  pthread_create(&t1, NULL, consumidor, NULL);
  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
}
