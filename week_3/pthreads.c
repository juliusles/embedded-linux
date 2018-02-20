#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Threads
#include <errno.h>   // errno
#include <string.h>  // strerror
#include <unistd.h>  // intptr_t (long int)

pthread_t tid1, tid2;
void *tret;

void * thread_fn1(void * arg){
	sleep(1);
	int err;
	err = pthread_join(tid2,&tret);
	if (err!=0)
		printf("Error in joining thread1.\n");

	// Warning: Different size between pointer and int 
	//printf("thread 2 exit code: %d\n", (int)tret); 

	// Segmentation Fault 
	//printf("thread 2 exit code: %d\n", *((int*)tret));  
	
	printf("thread 2 exit code: %ld\n", (intptr_t)tret);

	printf("thread 1 returning.\n");
	return ((void *)2);
}

void * thread_fn2(void * arg){
	printf("thread 2 exiting.\n");
	pthread_exit((void *)3);
}


int main(void){

	int err;
	err = pthread_create(&tid1, NULL, thread_fn1, NULL);
	if (err != 0) {
		fprintf(stderr, "Can't Create Thread 1: %s\n", strerror(err));
		exit(1);
	}	
	err = pthread_create(&tid2, NULL, thread_fn2, NULL);	
	if (err!=0)
		printf("Can't Create Thread 2.\n");

	err = pthread_join(tid1, &tret);
	if (err!=0)
		printf("Error in joining thread1.\n");
	printf("thread 1 exit code: %ld\n", (intptr_t)tret);
	return 0;
}







