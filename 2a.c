#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/fcntl.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

void * reader(void * args) {
    mqd_t mq;
    ssize_t bytes_read;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);

    while(1) {

        memset(buffer, 0x00, sizeof(buffer));
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if(bytes_read >= 0) {
            printf("THREAD 2: Received message: %s\n", buffer);
        } else {
            printf("THREAD 2: None \n");
        }

        fflush(stdout);
        sleep(1);
    }

    /* cleanup */
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return NULL;
}


void * sender(void * args) {

    mqd_t mq;
    char buffer[MAX_SIZE];

    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);

    for (int i = 0; i < 50; ++i) {
        snprintf(buffer, sizeof(buffer), "MESSAGE %d", i);

        printf("THREAD 1: Send integer... \n");
        mq_send(mq, buffer, MAX_SIZE, 0);

        fflush(stdout);
    }

    mq_close(mq);

    return NULL;
}


int main(int argc, char** argv) {

    pthread_t thread_1, thread_2;

    pthread_attr_t tattr;

    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    pthread_create(&thread_2, &tattr, &reader, NULL);
    pthread_create(&thread_1, &tattr, &sender, NULL);

    pthread_join(thread_2, NULL);
    pthread_join(thread_1, NULL);

    return (EXIT_SUCCESS);
}
