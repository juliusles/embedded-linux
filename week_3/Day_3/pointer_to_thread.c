#include <pthread.h>
#include <stdio.h>

#define MAX_THREADS	8

struct thread_data
{
  int number;
  char * message;
};

char * messages[MAX_THREADS] = {
                                 "\n Hello world!",
                                 "\n Paevaa!",
                                 "\n Moro maalilma!"                                 
                               };

void * PrintHello(void * data)
{
    struct thread_data * my_data;

    my_data = (struct thread_data *)data;
    printf("%s from thread %d\n", my_data->message, my_data->number);
    free(my_data);
    pthread_exit(NULL);
}

int main()
{
    int i, rc;
    pthread_t thread_id;
    struct thread_data * datap;

    for(i = 0; i < MAX_THREADS; i++)
    {
        datap = (struct thread_data*)malloc(sizeof(struct thread_data));
        if(!datap)
        {
             printf("\n ERROR: malloc cannot allocate memory \n");
             exit(1);
        }
        datap->number = i;
        datap->message = messages[i];
        rc = pthread_create(&thread_id, NULL, PrintHello, (void*)datap);
        if(rc)
        {
             printf("\n ERROR: return code from pthread_create is %d \n", rc);
             exit(1);
        }
        printf("\n I am thread %d. Created new thread (%d) in iteration %d ...\n", 
                pthread_self(), thread_id, i);
        if(i % 5 == 0) sleep(1);
    }

    pthread_exit(NULL);
}