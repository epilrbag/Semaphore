#include <pthread.h>
#include <semaphore.h>
#define NUM 100

pthread_t t0, t1, t2, t3, t4;

sem_t s0, s1, s2, s3;

int vetor[NUM], vetor1[NUM], vetor2[NUM], soma1, soma2, cont, cont2;

void *monitor()
{
  int i, valor;
  sem_wait(&s0);
  for(i = 0; i < NUM; i++)
  {
    //sem_wait(&s0);
    valor = rand()%1000;
    vetor[i] = valor;
    if(vetor[i] < 500)
    {
      vetor1[cont] = vetor[i];
      cont++;
    }
    else
    {
      vetor2[cont2] = vetor[i];
      cont2++;
    }
    //sem_post(&s1);
    //sem_post(&s2);
  }
  sem_post(&s1);
  sem_post(&s2);
}

void *relator1()
{
  sem_wait(&s1);
  for(int i = 0; i < cont; i++)
  //{
    //sem_wait(&s1);
    soma1 = soma1 + vetor1[i];
    sem_post(&s3);
  //}
}

void *relator2()
{
  sem_wait(&s2);
  for(int i = 0; i < cont2; i++)
  //{
    //sem_wait(&s2);
    soma2 = soma2 + vetor2[i];
    sem_post(&s3);
  //}
}

void *impressor()
{
  sem_wait(&s3);
  printf("Valor da soma menor que 500 é %d\n", soma1);
  printf("Valor da soma maior que 500 é %d\n", soma2);
  //sem_post(&s0);
}

int main()
{
  sem_init(&s0, 0, 1);
  sem_init(&s1, 0, 0);
  sem_init(&s2, 0, 0);
  sem_init(&s3, 0, 0);

  pthread_create(&t0, NULL, monitor, NULL);
  pthread_create(&t1, NULL, relator1, NULL);
  pthread_create(&t2, NULL, relator2, NULL);
  pthread_create(&t3, NULL, impressor, NULL);

  pthread_join(t0, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
}
