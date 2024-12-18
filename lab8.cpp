#include <stdio.h>
#include <math.h>

// Function to compute (base^exp) % mod using modular exponentiation
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

int main() {
    unsigned long long p, g; // Public parameters
    unsigned long long a, b; // Private keys
    unsigned long long A, B; // Public values
    unsigned long long S_A, S_B; // Shared secrets

    // Input public parameters
    printf("Enter a large prime number p: ");
    scanf("%llu", &p);
    printf("Enter the base (generator) g: ");
    scanf("%llu", &g);

    // Input private keys
    printf("Alice, enter your private key a: ");
    scanf("%llu", &a);
    printf("Bob, enter your private key b: ");
    scanf("%llu", &b);

    // Compute public values
    A = modular_exponentiation(g, a, p);
    B = modular_exponentiation(g, b, p);

    // Print public values
    printf("Alice sends: A = %llu\n", A);
    printf("Bob sends: B = %llu\n", B);

    // Compute shared secrets
    S_A = modular_exponentiation(B, a, p);
    S_B = modular_exponentiation(A, b, p);

    // Print shared secrets
    printf("Alice's computed shared secret: S_A = %llu\n", S_A);
    printf("Bob's computed shared secret: S_B = %llu\n", S_B);

    // Check if both secrets are the same
    if (S_A == S_B) {
        printf("Shared secret established successfully.\n");
    } else {
        printf("Error in shared secret establishment.\n");
    }

    return 0;
}

