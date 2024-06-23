#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <limits.h>
#include "../include/counter.h"
#include "../include/queue.h"

QueuePointer queue;



// Function declarations
long long modPow(long long base, long long exp, long long mod);
bool miller_rabin(long long n);
bool isPrime(int n);
void* worker(void* arg);

// Thread function
void* worker(void* arg) {
    int *counter = (int *)arg;

	while (1)
	{
		int task = DEQUEUE(queue);

		// Safe fail - should never happen.
		if (task < 0)
			break;

		*counter += isPrime(task);
	}
    pthread_exit(NULL);
}

int main() {
    int total_count = 0;    
    int num;

    queue = queueCreate();

    int thread_num = 16;//sysconf(_SC_NPROCESSORS_ONLN) * 0.5 + 2; //num_processors > 1 ? num_processors : 2; // Ensure at least 2 threads
    
    int thread_counter[thread_num];
    pthread_t threads[thread_num];

    

    // Check if the queue was created successfully
	if (queue == NULL)
	{
		fprintf(stderr, "Error creating queue.\n");
		exit(1);
	}

    for (int i = 0; i < thread_num; ++i) {
        thread_counter[i] = 0;
        pthread_create(&threads[i], NULL, worker, &thread_counter[i]);
    }

    while (scanf("%d", &num) != EOF) {   
        ENQUEUE(queue,num);
    }

    for (int i = 0; i < thread_num; ++i) {
           ENQUEUE(queue,-1);
    }

    // Join threads
    for (int i = 0; i < thread_num; ++i) {
        pthread_join(threads[i], NULL);
        total_count += thread_counter[i];
    }

    // Destroy the queue and print the total number of primes.
	queueDestroy(queue);
	fprintf(stdout, "%d total primes.\n", total_count);
    return 0;
}

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
