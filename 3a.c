#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/* semaphore variable*/
sem_t sem;

/* first thread entering non critical section first time, after the second thread,
 * it will enter the critical section and update variable sem*/

void *thread1()
{
    for (int i = 0; i < 5; ++i) {
        printf("sectie 1\n");
        sleep(1);
    }
    sem_post(&sem);
}
void *thread2() {
    sem_wait(&sem);
    for (int i = 0; i < 5; ++i) {
        printf("sectie 2\n");
        sleep(1);
    }
}

int main()
{
    sem_init(&sem,0,0);

    pthread_t tid1;
    pthread_attr_t tattr;

    pthread_attr_init(&tattr);

    /* round robin*/
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    /* create pthreads*/
    pthread_create(&tid1,&tattr,thread1,NULL);
    pthread_create(&tid1,&tattr,thread2,NULL);

    pthread_join(tid1,NULL);
}
