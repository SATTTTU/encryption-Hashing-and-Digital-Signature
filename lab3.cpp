#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Helper function to prepare the key by removing duplicates and treating 'J' as 'I'
void prepare_key(const char *key, char *prepared_key) {
    int seen[26] = {0}; // Array to track used letters
    int j = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I'; // Treat 'J' as 'I'
        if (isalpha(c) && !seen[c - 'A']) {
            prepared_key[j++] = c;
            seen[c - 'A'] = 1;
        }
    }

    // Add remaining letters of the alphabet
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'J' && !seen[c - 'A']) {
            prepared_key[j++] = c;
        }
    }

    prepared_key[j] = '\0';
}

// Helper function to create the 5x5 matrix from the prepared key
void create_matrix(const char *prepared_key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int k = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = prepared_key[k++];
        }
    }
}

// Helper function to find the position of a character in the matrix
void find_position(const char matrix[MATRIX_SIZE][MATRIX_SIZE], char c, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Prepare the plaintext by replacing 'J' with 'I', making pairs, and adding 'X' between duplicate letters
void prepare_plaintext(const char *plaintext, char *prepared_text) {
    int j = 0;
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        char c = toupper(plaintext[i]);
        if (c == 'J') c = 'I'; // Treat 'J' as 'I'
        
        if (isalpha(c)) {
            if (j > 0 && prepared_text[j - 1] == c) {
                prepared_text[j++] = 'X'; // Add 'X' between duplicate letters
            }
            prepared_text[j++] = c;
        }
    }

    if (j % 2 != 0) {
        prepared_text[j++] = 'X'; // Add 'X' to make the length even
    }

    prepared_text[j] = '\0';
}

// Encryption function
void encrypt_playfair(const char *plaintext, const char *key, char *encrypted_message) {
    char prepared_key[26];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char prepared_text[256];

    prepare_key(key, prepared_key);
    create_matrix(prepared_key, matrix);
    prepare_plaintext(plaintext, prepared_text);

    int length = strlen(prepared_text);

    for (int i = 0; i < length; i += 2) {
        int row1, col1, row2, col2;
        find_position(matrix, prepared_text[i], &row1, &col1);
        find_position(matrix, prepared_text[i + 1], &row2, &col2);

        if (row1 == row2) {
            encrypted_message[i] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            encrypted_message[i + 1] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            encrypted_message[i] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            encrypted_message[i + 1] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else {
            encrypted_message[i] = matrix[row1][col2];
            encrypted_message[i + 1] = matrix[row2][col1];
        }
    }

    encrypted_message[length] = '\0';
}

// Decryption function
void decrypt_playfair(const char *ciphertext, const char *key, char *decrypted_message) {
    char prepared_key[26];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char prepared_text[256];

    prepare_key(key, prepared_key);
    create_matrix(prepared_key, matrix);

    int length = strlen(ciphertext);

    for (int i = 0; i < length; i += 2) {
        int row1, col1, row2, col2;
        find_position(matrix, ciphertext[i], &row1, &col1);
        find_position(matrix, ciphertext[i + 1], &row2, &col2);

        if (row1 == row2) {
            decrypted_message[i] = matrix[row1][(col1 - 1 + MATRIX_SIZE) % MATRIX_SIZE];
            decrypted_message[i + 1] = matrix[row2][(col2 - 1 + MATRIX_SIZE) % MATRIX_SIZE];
        } else if (col1 == col2) {
            decrypted_message[i] = matrix[(row1 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col1];
            decrypted_message[i + 1] = matrix[(row2 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col2];
        } else {
            decrypted_message[i] = matrix[row1][col2];
            decrypted_message[i + 1] = matrix[row2][col1];
        }
    }

    // Remove padding 'X' from the decrypted text
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (decrypted_message[i] != 'X' || (i > 0 && decrypted_message[i - 1] != 'X')) {
            decrypted_message[j++] = decrypted_message[i];
        }
    }

    decrypted_message[j] = '\0';
}

int main() {
    char plaintext[] = "Hello, World!";
    char key[] = "KEYWORD";
    
    char encrypted_message[256];
    char decrypted_message[256];

    encrypt_playfair(plaintext, key, encrypted_message);
    printf("Encrypted: %s\n", encrypted_message);

    decrypt_playfair(encrypted_message, key, decrypted_message);
    printf("Decrypted: %s\n", decrypted_message);
    printf("Playfair Cipher");
    
    return 0;
}

