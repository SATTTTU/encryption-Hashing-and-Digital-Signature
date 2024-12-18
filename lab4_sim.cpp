#include <stdio.h>

// Parameters for the Linear Congruential Generator
#define a 1664525    // Multiplier
#define c 1013904223 // Increment
#define m 0xFFFFFFFF // Modulus (2^32)

// Function to generate the next random number
unsigned int lcg(unsigned int *seed) {
    *seed = (a * (*seed) + c) % m;
    return *seed;
}

int main() {
    // Seed value (initial value for the random number generator)
    unsigned int seed = 123456789;

    // Generate and print 10 random numbers
    printf("Generated random numbers:\n");
    for (int i = 0; i < 10; i++) {
        unsigned int random_number = lcg(&seed);
        printf("%u\n", random_number);
    }

    return 0;
}

