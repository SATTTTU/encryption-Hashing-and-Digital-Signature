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

// Function to compute the empirical cumulative distribution function (ECDF)
void compute_ecdf(const double data[], int size, double ecdf[]) {
    int counts[NUM_BINS] = {0};

    for (int i = 0; i < size; ++i) {
        int bin = (int)(data[i] * NUM_BINS);
        if (bin >= NUM_BINS) bin = NUM_BINS - 1;
        counts[bin]++;
    }

    for (int i = 0; i < NUM_BINS; ++i) {
        ecdf[i] = (double)counts[i] / size;
    }

    // Compute cumulative distribution function
    for (int i = 1; i < NUM_BINS; ++i) {
        ecdf[i] += ecdf[i - 1];
    }
}

// Kolmogorov-Smirnov Test function
double ks_test(double ecdf[]) {
    double d_max = 0.0;
    for (int i = 0; i < NUM_BINS; ++i) {
        double theoretical_cdf = (i + 1) / (double)NUM_BINS;
        double d = fabs(ecdf[i] - theoretical_cdf);
        if (d > d_max) d_max = d;
    }
    return d_max * sqrt(NUM_RANDOM_NUMBERS);
}

int main() {
    unsigned int seed = 1234;
    double random_numbers[NUM_RANDOM_NUMBERS];
    double ecdf[NUM_BINS] = {0};

    // Generate random numbers
    for (int i = 0; i < NUM_RANDOM_NUMBERS; ++i) {
        unsigned int rand_value = lcg(&seed);
        random_numbers[i] = (double)rand_value / 0xFFFFFFFF;
    }

    // Compute ECDF
    compute_ecdf(random_numbers, NUM_RANDOM_NUMBERS, ecdf);

    // Perform KS Test
    double d_max = ks_test(ecdf);

    printf("KS Statistic: %f\n", d_max);

    return 0;
}

