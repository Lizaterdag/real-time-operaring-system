#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *thread1()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5; ++i) {
        printf("sectie 1\n");
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
}

void *thread2() {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5; ++i) {
        printf("sectie 2\n");
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{

    /* when it starts with thread 1 it works perfectly fine, but sometimes it skips thread 1 and
     * goes right to thread and the whole thing only prints sectie 2
     * five times and sectie 1 just once*/
    
    pthread_mutex_init(&mutex,NULL);

    pthread_t tid1;
    pthread_attr_t tattr;

    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    pthread_create(&tid1,&tattr,thread1,NULL);
    pthread_create(&tid1,&tattr,thread2,NULL);

    pthread_join(tid1,NULL);
}

