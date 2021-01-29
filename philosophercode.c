
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#define n 5
#define left (i+n-1)%n
#define right (i+1)%n
#define thinking 0
#define hungry 1
#define eating 2


int state[n];
sem_t mutex;
sem_t s[n];

void *philosopher(int *i)
{
while(1)
{
think();
take_forks(i);
eat();
put_forks(i);
}
}

void take_forks(int i)
{
sem_wait(&mutex);
state[i]= hungry;
test(i);
sem_post(&mutex);
sem_wait(&s[i]);
}


void put_forks(int i)
{
sem_wait(&mutex);
state[i]=thinking;
test(left);
test(right);
sem_post(&mutex);
}

void test(int i)
{
if(state[i]==hungry && state[left]!= eating && state[right]!=eating)
{
state[i]=eating;
sem_post(&s[i]);
}
}

void eat()
{
int wait;
printf("\nStarted Eating...\n");
wait=rand();
Sleep(wait);
printf("\nFinished Eating...\n");
}

void think()
{
int wait;
printf("\nStarted thinking...\n");
wait=rand();
Sleep(wait);
printf("\nFinished thinking...\n");
}




int main()
{
sem_init(&mutex, 0, 1);
sem_init(&s[0], 0, 1);
sem_init(&s[1], 0, 1);
sem_init(&s[2], 0, 1);
sem_init(&s[3], 0, 1);
sem_init(&s[4], 0, 1);
pthread_t philosopherthread1;
pthread_t philosopherthread2;
pthread_t philosopherthread3;
pthread_t philosopherthread4;
pthread_t philosopherthread5;
pthread_create(&philosopherthread1, NULL, philosopher, NULL);
pthread_create(&philosopherthread2, NULL, philosopher, NULL);
pthread_create(&philosopherthread3, NULL, philosopher, NULL);
pthread_create(&philosopherthread4, NULL, philosopher, NULL);
pthread_create(&philosopherthread5, NULL, philosopher, NULL);
pthread_join(philosopherthread1, NULL);
pthread_join(philosopherthread2, NULL);
pthread_join(philosopherthread3, NULL);
pthread_join(philosopherthread4, NULL);
pthread_join(philosopherthread5, NULL);
sem_destroy(&mutex);
sem_destroy(&s[0]);
sem_destroy(&s[1]);
sem_destroy(&s[2]);
sem_destroy(&s[3]);
sem_destroy(&s[4]);

return 0;

}
