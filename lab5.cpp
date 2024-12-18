#include <stdio.h>

// Function to perform the Extended Euclidean Algorithm
// It returns the gcd of a and b, and updates x and y to be the coefficients
// of the equation: gcd(a, b) = a*x + b*y
int extended_gcd(int a, int b, int *x, int *y) {
    // Base case
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1; // Coefficients for a and b
    int gcd = extended_gcd(b, a % b, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

// Function to find the modular multiplicative inverse
// It returns the multiplicative inverse of a under modulo m
int modular_inverse(int a, int m) {
    int x, y;
    int gcd = extended_gcd(a, m, &x, &y);

    // Check if the inverse exists
    if (gcd != 1) {
        printf("No multiplicative inverse exists for %d modulo %d\n", a, m);
        return -1; // No modular inverse exists
    }

    // Return the positive modular inverse
    return (x % m + m) % m;
}

int main() {
    int a, m;
    
    printf("Enter the value of a: ");
    scanf("%d", &a);
    
    printf("Enter the value of m: ");
    scanf("%d", &m);
    
    int inverse = modular_inverse(a, m);
    
    if (inverse != -1) {
        printf("The modular multiplicative inverse of %d modulo %d is %d\n", a, m, inverse);
    }

    return 0;
}

