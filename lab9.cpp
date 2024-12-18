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

// Function to compute GCD of a and b using Euclidean Algorithm
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute modular inverse of a under modulo m
unsigned long long mod_inverse(unsigned long long a, unsigned long long m) {
    unsigned long long m0 = m;
    unsigned long long y = 0;
    unsigned long long x = 1;

    if (m == 1) return 0;

    while (a > 1) {
        unsigned long long q = a / m;
        unsigned long long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;

    return x;
}

int main() {
    unsigned long long p, q, n, phi, e, d;
    unsigned long long plaintext, ciphertext, decrypted_text;

    // Input two prime numbers
    printf("Enter prime number p: ");
    scanf("%llu", &p);
    printf("Enter prime number q: ");
    scanf("%llu", &q);

    // Compute n and phi
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    e = 0;
    for (unsigned long long i = 2; i < phi; i++) {
        if (gcd(i, phi) == 1) {
            e = i;
            break;
        }
    }

    // Compute d, the modular inverse of e
    d = mod_inverse(e, phi);

    // Input plaintext
    printf("Enter plaintext (integer less than %llu): ", n);
    scanf("%llu", &plaintext);

    // Encrypt
    ciphertext = modular_exponentiation(plaintext, e, n);
    printf("Encrypted ciphertext: %llu\n", ciphertext);

    // Decrypt
    decrypted_text = modular_exponentiation(ciphertext, d, n);
    printf("Decrypted plaintext: %llu\n", decrypted_text);

    return 0;
}

