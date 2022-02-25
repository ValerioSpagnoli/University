#include "performance.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

void do_work() {
    int* array = (int*)malloc(25*sizeof(int));
    int i;
    printf("Start!\n");
    for(i = 0; i<25600; i+=1024){
        printf("Write %d\n", i);
        array[i] = i;
    }
    printf("Finish!\n");
    free(array);
	return;
}

void* thread_fun(void *arg) {
	do_work();
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Syntax: %s <N>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// parse N from the command line
	int n = atoi(argv[1]);

	// thread reactivity
	printf("Thread reactivity, %d tests...\n", n);
	unsigned long sum = 0;
	timer t;
	int i, ret;

	begin(&t);
	for (i = 0; i < n; i++) {
		pthread_t thread;
		ret = pthread_create(&thread, NULL, thread_fun, NULL);
		if (ret != 0) {
			fprintf(stderr, "Can't create a new thread, error %d\n", ret);
			exit(EXIT_FAILURE);
		}
		ret = pthread_join(thread, NULL);
		if (ret != 0) {
			fprintf(stderr, "Cannot join on thread, error %d\n", ret);
			exit(EXIT_FAILURE);
		}
	}
	end(&t);
	sum += get_microseconds(&t);

	// compute statistics
	unsigned long thread_avg = sum / n;
	printf("Average: %lu microseconds\n", thread_avg);

	return EXIT_SUCCESS;
}
