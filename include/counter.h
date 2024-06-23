#include "Queue.h"

/*
 * @brief Function that checks if a number is prime.
 * @param n The number to be checked if it is prime.
 * @return True if the number is prime, false otherwise.
*/
bool isPrime(int n);

/*
 * @brief Function that is executed by each thread.
 * @param arg The number of primes found by the thread.
 * @return NULL.
*/
void *worker(void *arg);
