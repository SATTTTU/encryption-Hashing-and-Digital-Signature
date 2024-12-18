#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform modular exponentiation
// It computes (base^exp) % mod efficiently
unsigned long long modular_exponentiation(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    
    return result;
}

// Function to perform the Miller-Rabin primality test
int miller_rabin(unsigned long long n, int k) {
    // Edge cases
    if (n <= 1 || n == 4) return 0;
    if (n == 2 || n == 3) return 1;
    
    // Find d such that d * 2^r = n-1 with d odd
    unsigned long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    // Witness loop
    for (int i = 0; i < k; i++) {
        // Pick a random number a in [2, n-2]
        unsigned long long a = 2 + rand() % (n - 4);
        unsigned long long x = modular_exponentiation(a, d, n);
        
        if (x == 1 || x == n - 1) continue;
        
        int is_composite = 1;
        for (int j = 0; j < r - 1; j++) {
            x = modular_exponentiation(x, 2, n);
            if (x == n - 1) {
                is_composite = 0;
                break;
            }
        }
        
        if (is_composite) return 0;
    }
    
    return 1;
}

int main() {
    unsigned long long n;
    int k; // Number of iterations

    srand(time(NULL)); // Seed random number generator
    
    printf("Enter the number to test: ");
    scanf("%llu", &n);
    
    printf("Enter the number of iterations for Miller-Rabin test: ");
    scanf("%d", &k);
    
    if (miller_rabin(n, k)) {
        printf("%llu is probably prime.\n", n);
    } else {
        printf("%llu is composite.\n", n);
    }
    
    return 0;
}

