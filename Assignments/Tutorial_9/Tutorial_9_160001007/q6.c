// Dining philosipher problem by arjun Srivastava

#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h> 
  

#define N 5 
#define LEFT (nump + 4) % N 
#define RIGHT (nump + 1) % N 

#define EATING 0 
#define HUNGRY 1 
#define THINKING 2

sem_t flag, S[N]; 
 

int state[N]; 
int philo[N] = { 0, 1, 2, 3, 4 }; 

void test(int nump){ 
    if (state[nump] == HUNGRY 
        && state[LEFT] != EATING 
        && state[RIGHT] != EATING) { 
        state[nump] = EATING; 
  
        sleep(2); 
        printf("Philo %d takes fork %d and %d\n", nump + 1, LEFT + 1, nump + 1); 
        printf("Philo %d is Eating\n", nump + 1); 

        sem_post(&S[nump]); 
    } 
} 

void put_down_fork(int nump) { 
    sem_wait(&flag); 
    state[nump] = THINKING; 
    printf("Philo %d putting fork %d and %d down\n", nump + 1, LEFT + 1, nump + 1); 
    printf("Philo %d is thinking\n", nump + 1); 
    test(LEFT); 
    test(RIGHT); 
    sem_post(&flag); 
} 

void pick_up_fork(int nump) { 
    sem_wait(&flag); 

    state[nump] = HUNGRY; 
    printf("Philo %d is Hungry\n", nump + 1); 
    test(nump); 
  
    sem_post(&flag); 
    sem_wait(&S[nump]); 
    sleep(1); 
} 
  

void* philospher(void* num) { 
    while (1) { 
        int* i = num; 
        sleep(1); 
        pick_up_fork(*i); 
        sleep(0); 
        put_down_fork(*i); 
    } 
} 
  
int main() { 
    int i; 
    pthread_t thread_id[N]; 
    sem_init(&flag, 0, 1); 
    for (i = 0; i < N; i++) 
        sem_init(&S[i], 0, 0); 
    for (i = 0; i < N; i++) { 
        pthread_create(&thread_id[i], NULL, philospher, &philo[i]); 
        printf("Philo %d is thinking\n", i + 1); 
    } 
    for (i = 0; i < N; i++) 
        pthread_join(thread_id[i], NULL); 
} 
