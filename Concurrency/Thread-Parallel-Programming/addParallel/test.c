#include <stdio.h>
#include <pthread.h>
#include "thpool.h"


void task1(){
	printf("Thread #%u working on task1\n", (int)pthread_self());
}


void task2(){
	printf("Thread #%u working on task2\n", (int)pthread_self());
}


int main(){
	
	puts("Making threadpool with 4 threads");
	threadpool thpool = thpool_init(4);

	puts("Adding 40 tasks to threadpool");
	int i;
	for (i=0; i<20; i++){
		thpool_add_work(thpool, (void*)task1, NULL);
		thpool_add_work(thpool, (void*)task2, NULL);
	};

	puts("Killing threadpool");
	thpool_destroy(thpool);
	
	return 0;
}
