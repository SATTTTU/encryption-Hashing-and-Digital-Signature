#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to normalize the keyword by repeating it to match the length of the text
void normalize_keyword(const char *keyword, char *normalized_keyword, int length) {
    int keyword_length = strlen(keyword);
    for (int i = 0; i < length; i++) {
        normalized_keyword[i] = keyword[i % keyword_length];
    }
    normalized_keyword[length] = '\0'; // Null-terminate the string
}

// Function to encrypt a plaintext message using the Vigenère cipher
void encrypt_vigenere(const char *plaintext, const char *keyword, char *encrypted_message) {
    int plaintext_length = strlen(plaintext);
    char normalized_keyword[plaintext_length + 1];
    
    normalize_keyword(keyword, normalized_keyword, plaintext_length);
    
    for (int i = 0; i < plaintext_length; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int shift = toupper(normalized_keyword[i]) - 'A';
            encrypted_message[i] = (plaintext[i] - base + shift) % 26 + base;
        } else {
            encrypted_message[i] = plaintext[i];
        }
    }
    encrypted_message[plaintext_length] = '\0'; // Null-terminate the encrypted message
}

// Function to decrypt a ciphertext message using the Vigenère cipher
void decrypt_vigenere(const char *ciphertext, const char *keyword, char *decrypted_message) {
    int ciphertext_length = strlen(ciphertext);
    char normalized_keyword[ciphertext_length + 1];
    
    normalize_keyword(keyword, normalized_keyword, ciphertext_length);
    
    for (int i = 0; i < ciphertext_length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int shift = toupper(normalized_keyword[i]) - 'A';
            decrypted_message[i] = (ciphertext[i] - base - shift + 26) % 26 + base;
        } else {
            decrypted_message[i] = ciphertext[i];
        }
    }
    decrypted_message[ciphertext_length] = '\0'; // Null-terminate the decrypted message
}

int main() {
    char plaintext[] = "Hello, World!";
    char keyword[] = "KEY";
    
    char encrypted_message[sizeof(plaintext)];
    char decrypted_message[sizeof(plaintext)];
    
    encrypt_vigenere(plaintext, keyword, encrypted_message);
    printf("Encrypted: %s\n", encrypted_message);
    
    decrypt_vigenere(encrypted_message, keyword, decrypted_message);
    printf("Decrypted: %s\n", decrypted_message);
    printf("Vigenere Cipher");
    
    return 0;
}

