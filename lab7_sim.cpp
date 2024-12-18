#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_RANDOM_NUMBERS 1000
#define NUM_BINS 10

// Function to generate random numbers using LCG
unsigned int lcg(unsigned int *seed) {
    const unsigned int a = 1664525;
    const unsigned int c = 1013904223;
    const unsigned int m = 0xFFFFFFFF;

    *seed = (a * (*seed) + c) % m;
    return *seed;
}

// Function to compute the Chi-Square statistic
double chi_square_test(const int observed[], int num_observed, int num_bins) {
    double expected = (double)num_observed / num_bins;
    double chi_square = 0.0;

    for (int i = 0; i < num_bins; ++i) {
        double diff = observed[i] - expected;
        chi_square += (diff * diff) / expected;
    }

    return chi_square;
}

int main() {
    unsigned int seed = 1234;
    int observed[NUM_BINS] = {0};

    // Generate random numbers and bin them
    for (int i = 0; i < NUM_RANDOM_NUMBERS; ++i) {
        unsigned int rand_value = lcg(&seed);
        int bin = (int)(rand_value % NUM_BINS);
        observed[bin]++;
    }

    // Perform Chi-Square Test
    double chi_square = chi_square_test(observed, NUM_RANDOM_NUMBERS, NUM_BINS);

    printf("Observed frequencies:\n");
    for (int i = 0; i < NUM_BINS; ++i) {
        printf("Bin %d: %d\n", i, observed[i]);
    }

    printf("Chi-Square Statistic: %f\n", chi_square);

    return 0;
}

