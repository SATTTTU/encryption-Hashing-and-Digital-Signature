#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the function f(x) for which you want to find the area
double f(double x) {
    // Example function: f(x) = x^2
    return x * x;
}

// Function to generate a random double between min and max
double random_double(double min, double max) {
    return min + (max - min) * (double)rand() / RAND_MAX;
}

int main() {
    // Define the interval [a, b]
    double a = 0.0;
    double b = 1.0;

    // Number of random points to generate
    int num_points = 1000000;
    int points_under_curve = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Generate random points and count how many fall under the curve
    for (int i = 0; i < num_points; ++i) {
        // Generate a random x within the interval [a, b]
        double x = random_double(a, b);

        // Generate a random y within the range of the function's output
        double y = random_double(0, f(b));

        // Check if the point (x, y) is below the curve f(x)
        if (y <= f(x)) {
            points_under_curve++;
        }
    }

    // Compute the area under the curve using Monte Carlo estimation
    double width = b - a;
    double height = f(b); // Maximum y value we used for random generation
    double area_estimate = width * height * (double)points_under_curve / num_points;

    printf("Estimated area under the curve: %f\n", area_estimate);

    return 0;
}

