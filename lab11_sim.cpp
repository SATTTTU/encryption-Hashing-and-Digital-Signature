#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIMULATION_TIME 50 // Total time for the simulation

// Function to generate exponential random variable
double exponential_random(double rate) {
    return -log(1.0 - ((double)rand() / RAND_MAX)) / rate;
}

// Function to simulate the single-server queue
void simulate_queue(double lambda, double mu) {
    double current_time = 0.0;
    double next_arrival = exponential_random(lambda);
    double next_departure = INFINITY; // Initialize to infinity (no departure initially)
    int total_customers_served = 0;
    int waiting_customers = 0;

    while (current_time < SIMULATION_TIME) {
        if (next_arrival < next_departure) {
            current_time = next_arrival;
            printf("Arrival at time %.2f\n", current_time);
            next_arrival = current_time + exponential_random(lambda);
            
            if (next_departure == INFINITY) {
                next_departure = current_time + exponential_random(mu);
            } else {
                waiting_customers++;
            }
        } else {
            current_time = next_departure;
            printf("Departure at time %.2f\n", current_time);
            next_departure = INFINITY;
            total_customers_served++;

            if (waiting_customers > 0) {
                waiting_customers--;
                next_departure = current_time + exponential_random(mu);
            }
        }
    }

    // Output the results
    printf("Total customers served: %d\n", total_customers_served);
    printf("Total customers waiting at end: %d\n", waiting_customers);
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Input parameters for the simulation
    double lambda, mu;
    printf("Enter the arrival rate (lambda): ");
    scanf("%lf", &lambda);
    printf("Enter the service rate (mu): ");
    scanf("%lf", &mu);

    // Simulate the queue
    simulate_queue(lambda, mu);

    return 0;
}

