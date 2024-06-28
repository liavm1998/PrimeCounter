#include <CUnit/Basic.h>
#include <stdbool.h>
// #include "../include/counter.h"

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

// Test cases for the isPrime function
void test_isPrime(void) {
    CU_ASSERT_TRUE(isPrime(2));
    CU_ASSERT_TRUE(isPrime(3));
    CU_ASSERT_FALSE(isPrime(4));
    CU_ASSERT_TRUE(isPrime(5));
    CU_ASSERT_FALSE(isPrime(10));
    CU_ASSERT_TRUE(isPrime(13));
    CU_ASSERT_TRUE(isPrime(17));
    CU_ASSERT_FALSE(isPrime(18));
    CU_ASSERT_TRUE(isPrime(19));
    CU_ASSERT_FALSE(isPrime(20));
    CU_ASSERT_TRUE(isPrime(23));
    CU_ASSERT_FALSE(isPrime(24));
    CU_ASSERT_TRUE(isPrime(29));
    CU_ASSERT_TRUE(isPrime(31));
    CU_ASSERT_TRUE(isPrime(37));
    CU_ASSERT_FALSE(isPrime(1));
    CU_ASSERT_FALSE(isPrime(0));
    CU_ASSERT_FALSE(isPrime(-1));
    CU_ASSERT_FALSE(isPrime(-5));
}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite pSuite = CU_add_suite("Prime_Test_Suite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(pSuite, "test of isPrime()", test_isPrime))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
