#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_DICE 1
#define MAX_DICE 6

// Function to toss a single die
int toss_die() {
    return (rand() % MAX_DICE) + 1;
}

// Function to simulate multiple dice tosses
void simulate_dice_toss(int num_dice, int num_tosses) {
    for (int i = 0; i < num_tosses; ++i) {
        printf("Toss %d: ", i + 1);
        for (int j = 0; j < num_dice; ++j) {
            printf("%d ", toss_die());
        }
        printf("\n");
    }
}

int main() {
    int num_dice, num_tosses;

    // Seed the random number generator
    srand(time(NULL));

    // Get user input
    printf("Enter the number of dice to toss: ");
    scanf("%d", &num_dice);

    // Validate input
    if (num_dice < 1) {
        printf("The number of dice must be at least 1.\n");
        return 1;
    }

    printf("Enter the number of times to toss the dice: ");
    scanf("%d", &num_tosses);

    // Validate input
    if (num_tosses < 1) {
        printf("The number of tosses must be at least 1.\n");
        return 1;
    }

    // Simulate dice tosses
    simulate_dice_toss(num_dice, num_tosses);

    return 0;
}

