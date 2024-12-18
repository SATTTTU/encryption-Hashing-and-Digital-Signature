#include <stdio.h>

// Function to generate the next random number using the Mid-Square Method
unsigned int mid_square(unsigned int seed) {
    // Square the seed
    unsigned long long squared = (unsigned long long)seed * seed;

    // Extract the middle 4 digits from the squared number
    // We assume a 4-digit number, so we need to handle up to 8 digits in the squared number
    unsigned int middle_digits = (unsigned int)((squared / 100) % 10000);
    
    return middle_digits;
}

int main() {
    // Seed value (initial value for the random number generator)
    unsigned int seed = 1234;

    // Generate and print 10 random numbers
    printf("Generated random numbers:\n");
    for (int i = 0; i < 10; i++) {
        seed = mid_square(seed);
        printf("%04u\n", seed); // Print the number with leading zeros if necessary
        
    }
    printf("Mid Square method");

    return 0;
}

