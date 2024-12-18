#include <stdio.h>

// Function to compute Euler's Totient Function
unsigned long long euler_totient(unsigned long long n) {
    unsigned long long result = n; // Initialize result as n
    unsigned long long p;
    
    // Check for every integer up to sqrt(n) for being a prime factor
    for (p = 2; p * p <= n; p++) {
        // Check if p is a divisor of n
        if (n % p == 0) {
            // If p is a prime factor, apply the formula
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    
    // If n is a prime number greater than 1
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

int main() {
    unsigned long long n;
    
    printf("Enter a number to compute its Euler's Totient Function: ");
    scanf("%llu", &n);
    
    printf("Euler's Totient Function of %llu is %llu\n", n, euler_totient(n));
    
    return 0;
}

