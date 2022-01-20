#include <stdio.h>
#include <pthread.h>

void *taskOne ()
{
  int m, n;
  while (1)
    {
      printf ("task 1\n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */
    }
}

void *taskTwo ()
{
  int m, n;
  while (1)
    {
      printf ("task 2\n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */
    }
}

void *taskThree ()
{
  int i, m, n;
  for (i = 0; i < 40; i++)
    {
      printf ("task 3 \n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* De for-lussen dienen omeen vertraging te realiseren, zodat er een aantal keer een context switchnaar taak 4 optreedt */
    }
}

void *taskFour ()
{
  int i, m, n;
  for (i = 0; i < 40; i++)
    {
      printf ("task 4\n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* De for-lussen dienen omeen vertraging te realiseren, zodat er een aantal keer een context switch naar taak 4 optreedt */
    }
}

int main (void){
    pthread_attr_t tattr;
    pthread_t thread1, thread2, thread3, thread4;
    pthread_attr_init (&tattr);
    pthread_attr_setschedpolicy (&tattr, SCHED_RR);	//sched policy aanpassen
    pthread_create (&thread3, &tattr, taskThree, NULL);
    pthread_create (&thread4, &tattr, taskFour, NULL);
    
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_create (&thread1, &tattr, taskOne, NULL);
    pthread_create (&thread2, &tattr, taskTwo, NULL);
    pthread_join(thread1, NULL);
  
}
