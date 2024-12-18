#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TOTAL_POINTS 1000000

// Function to generate a random double between 0 and 1
double random_double() {
    return (double)rand() / RAND_MAX;
}

int main() {
    int inside_circle = 0;
    int total_points = TOTAL_POINTS;

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < total_points; ++i) {
        // Generate random points (x, y) in the square [0, 1) x [0, 1)
        double x = random_double();
        double y = random_double();

        // Check if the point (x, y) is inside the unit circle
        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    // Estimate pi
    double pi_estimate = 4.0 * inside_circle / total_points;

    printf("Estimated value of Pi: %f\n", pi_estimate);

    return 0;
}

