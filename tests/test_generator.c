#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // For boolean type
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#define MAX_NUMBERS 1000  // Maximum number of random numbers to read

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

int countPrimes(const char *command) {
    // Open a pipe to read the output of randomGenerator
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return -1;
    }

    // Read and print random numbers from the output
    int numbers[MAX_NUMBERS];
    int num_count = 0;

    while (num_count < MAX_NUMBERS && fscanf(fp, "%d", &numbers[num_count]) == 1) {
        num_count++;
    }

    // Close the pipe
    pclose(fp);

    // Count prime numbers
    int prime_count = 0;
    for (int i = 0; i < num_count; ++i) {
        if (isPrime(numbers[i])) {
            prime_count++;
        }
    }

    // Return total prime count
    return prime_count;
}

// Test function to check if the number of total prime numbers matches the expected count
void test_countPrimes(void) {
    // Test cases with different configurations of randomGenerator
    CU_ASSERT(countPrimes("./randomGenerator 10 100") == 5);
    CU_ASSERT(countPrimes("./randomGenerator 10 1000") == 58);
    CU_ASSERT(countPrimes("./randomGenerator 1000 3") == 1);
    CU_ASSERT(countPrimes("./randomGenerator 1000 400") == 22);
}

int main() {

    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Create a test suite
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("PrimeCountingSuite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test to the suite
    if (NULL == CU_add_test(pSuite, "test_countPrimes", test_countPrimes)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
