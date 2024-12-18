#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to simulate a coin toss
int coin_toss() {
    // Generate a random number: 0 or 1
    return rand() % 2;
}

int main() {
    int num_simulations = 100000; // Number of simulations
    int heads_count = 0;
    int tails_count = 0;

    // Initialize random number generator
    srand(time(NULL));

    // Perform coin toss simulations
    for (int i = 0; i < num_simulations; i++) {
        if (coin_toss() == 0) {
            heads_count++;
        } else {
            tails_count++;
        }
    }

    // Calculate probabilities
    double heads_probability = (double)heads_count / num_simulations;
    double tails_probability = (double)tails_count / num_simulations;

    // Print results
    printf("Number of simulations: %d\n", num_simulations);
    printf("Number of heads: %d\n", heads_count);
    printf("Number of tails: %d\n", tails_count);
    printf("Estimated probability of heads: %.4f\n", heads_probability);
    printf("Estimated probability of tails: %.4f\n", tails_probability);

    return 0;
}

