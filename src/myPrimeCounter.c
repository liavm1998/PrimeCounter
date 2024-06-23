#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <limits.h>

// Global variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
int total_count = 0;

// Function declarations
long long modPow(long long base, long long exp, long long mod);
bool miller_rabin(long long n);
bool isPrime(int n);
void* worker(void* arg);

// Function to perform modular exponentiation (base^exp % mod)
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        exp = exp >> 1;    // exp = exp / 2
        base = (base * base) % mod;  // base = base^2 % mod
    }
    return result;
}

// Miller-Rabin primality test
bool miller_rabin(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;  // If n is even, it's not prime

    // Find d such that d * 2^r = n-1 with d odd
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // Strong pseudoprime bases for deterministic tests
    long long bases[] = {2, 7, 61};
    int num_bases = 3;

    for (int i = 0; i < num_bases && bases[i] < n; ++i) {
        long long a = bases[i];
        long long x = modPow(a, d, n); // calculate x = a ^ d mod n

        if (x == 1 || x == n - 1) 
            continue;

        bool is_composite = true;
        for (int j = 1; j < r; ++j) {
            x = (x * x) % n;
            if (x == n - 1) {
                is_composite = false;
                break;
            }
        }

        if (is_composite)
            return false;  // n is composite
    }

    return true;  // n is likely prime
}

// Function to check if a number is prime using Miller-Rabin primality test
bool isPrime(int n) {
    return miller_rabin(n);
}

// Thread function
void* worker(void* arg) {
    int* worker_total_counter = malloc(sizeof(int));
    *worker_total_counter = 0;
    char buf[1024]; // Buffer size for input handling

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        int num;
        if (sscanf(buf, "%d", &num) != 1)
            continue; // Skip invalid input

        if (isPrime(num)) {
            (*worker_total_counter)++;
        }
    }

    pthread_mutex_lock(&count_mutex);
    total_count += *worker_total_counter;
    pthread_mutex_unlock(&count_mutex);

    free(worker_total_counter);
    pthread_exit(NULL);
}

int main() {
    int num_processors = sysconf(_SC_NPROCESSORS_ONLN);
    int thread_num =num_processors * 0.5; //num_processors > 1 ? num_processors : 2; // Ensure at least 2 threads

    pthread_t threads[thread_num];
    for (int i = 0; i < thread_num; ++i) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    // Join threads
    for (int i = 0; i < thread_num; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("%d total primes.\n", total_count);
    return 0;
}
