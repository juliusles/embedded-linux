#include <pthread.h>
#include <stdio.h>

#define MAX_THREADS	8

//Struct
struct thread_data
{
  int number;
  char * message;
};

char * messages[MAX_THREADS] = {
                                 "\n Hello world!",
                                 "\n P�ivaa!",
                                 "\n Paevaa!",
                               };

struct thread_data thread_data_array[MAX_THREADS];

void * PrintHello(void * data)
{

    struct thread_data * my_data;

    my_data = (struct thread_data *)data;
    printf("%s from thread %d\n", my_data->message, my_data->number);
    pthread_exit(NULL);
}

int main()
{
    int rc;
    pthread_t thread_id[MAX_THREADS];

    int i;

    for(i = 0; i < MAX_THREADS; i++)
    {
        thread_data_array[i].number = i;
        thread_data_array[i].message = messages[i];
        rc = pthread_create(&thread_id[i], NULL, PrintHello, (void*)&thread_data_array[i]);
        if(rc)
        {
             printf("\n ERROR: return code from pthread_create is %d \n", rc);
             exit(1);
        }
        printf("\n I am thread %d. Created new thread (%d) in iteration %d ...\n", 
                pthread_self(), thread_id[i], i);
        if(i % 5 == 0) sleep(1);
    }

    pthread_exit(NULL);
}