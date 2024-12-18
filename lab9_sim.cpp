#include <stdio.h>
#include <stdbool.h>

#define ROWS 3
#define COLS 3

// Function to check if the matrix is a Markov matrix
bool is_markov_matrix(double matrix[ROWS][COLS], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        double row_sum = 0.0;
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < 0) {
                // Check for non-negative entries
                return false;
            }
            row_sum += matrix[i][j];
        }
        // Check if each row sums to 1
        if (row_sum < 0.9999 || row_sum > 1.0001) { // Allowing a small tolerance for floating-point comparison
            return false;
        }
    }
    return true;
}

int main() {
    // Example matrix to test
    double matrix[ROWS][COLS] = {
        {0.2, 0.5, 0.3},
        {0.0, 0.3, 0.7},
        {0.4, 0.4, 0.2}
    };

    // Test if the matrix is a Markov matrix
    if (is_markov_matrix(matrix, ROWS, COLS)) {
        printf("The matrix is a Markov matrix.\n");
    } else {
        printf("The matrix is not a Markov matrix.\n");
    }

    return 0;
}

