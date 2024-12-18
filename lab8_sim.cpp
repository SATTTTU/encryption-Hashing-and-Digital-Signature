#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_RANDOM_NUMBERS 1000
#define MAX_LAG 20

// Function to generate random numbers using LCG
unsigned int lcg(unsigned int *seed) {
    const unsigned int a = 1664525;
    const unsigned int c = 1013904223;
    const unsigned int m = 0xFFFFFFFF;

    *seed = (a * (*seed) + c) % m;
    return *seed;
}

// Function to compute mean of the random numbers
double compute_mean(const double data[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum / size;
}

// Function to compute autocorrelation
void compute_autocorrelation(const double data[], int size, double autocorr[], int max_lag) {
    double mean = compute_mean(data, size);
    double variance = 0.0;
    
    // Compute variance
    for (int i = 0; i < size; ++i) {
        variance += (data[i] - mean) * (data[i] - mean);
    }
    variance /= size;

    for (int lag = 0; lag <= max_lag; ++lag) {
        double numerator = 0.0;

        for (int i = 0; i < size - lag; ++i) {
            numerator += (data[i] - mean) * (data[i + lag] - mean);
        }

        autocorr[lag] = numerator / ((size - lag) * variance);
    }
}

int main() {
    unsigned int seed = 1234;
    double random_numbers[NUM_RANDOM_NUMBERS];
    double autocorr[MAX_LAG + 1] = {0};

    // Generate random numbers and normalize them to [0, 1]
    for (int i = 0; i < NUM_RANDOM_NUMBERS; ++i) {
        unsigned int rand_value = lcg(&seed);
        random_numbers[i] = (double)rand_value / 0xFFFFFFFF;
    }

    // Compute autocorrelation
    compute_autocorrelation(random_numbers, NUM_RANDOM_NUMBERS, autocorr, MAX_LAG);

    // Print autocorrelation values
    printf("Autocorrelation values:\n");
    for (int lag = 0; lag <= MAX_LAG; ++lag) {
        printf("Lag %2d: %f\n", lag, autocorr[lag]);
    }

    return 0;
}

