#include <stdio.h>
#include <ctype.h> // For isalpha() and tolower()

// Function to encrypt a message using Caesar cipher
void encrypt_caesar_cipher(char *plaintext, int shift, char *encrypted_message) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            encrypted_message[i] = (plaintext[i] - base + shift) % 26 + base;
        } else {
            encrypted_message[i] = plaintext[i];
        }
        i++;
    }
    encrypted_message[i] = '\0'; // Null-terminate the encrypted message
}

// Function to decrypt a message using Caesar cipher
void decrypt_caesar_cipher(char *ciphertext, int shift, char *decrypted_message) {
    encrypt_caesar_cipher(ciphertext, 26 - (shift % 26), decrypted_message);
}

int main() {
    char plaintext[] = "Hello, World!";
    int shift = 3;

    char encrypted_message[sizeof(plaintext)];
    char decrypted_message[sizeof(plaintext)];

    encrypt_caesar_cipher(plaintext, shift, encrypted_message);
    printf("Encrypted: %s\n", encrypted_message);

    decrypt_caesar_cipher(encrypted_message, shift, decrypted_message);
    printf("Decrypted: %s\n", decrypted_message);

    return 0;
}

