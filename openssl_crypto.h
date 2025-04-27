#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <stddef.h>
#include "credit.h"

// Declare the key and iv as extern (without initializing them)
extern unsigned char key[64];  // declare key as extern
extern unsigned char iv[16];   // declare iv as extern

// Updated function prototype for encrypt_data
void encrypt_data(const unsigned char *plaintext, int plaintext_len,
    unsigned char *ciphertext, int *ciphertext_len,
    const unsigned char *key, const unsigned char *iv);


// Updated function prototype for decrypt_data
void decrypt_data(const unsigned char *ciphertext, int ciphertext_len,
    unsigned char *decrypted, int *decrypted_len,
    const unsigned char *key, const unsigned char *iv);


// Helper functions you add:
char* base64_encode(const unsigned char *input, int length);
unsigned char* base64_decode(const char *input, int *out_len);


#endif // CRYPTO_UTILS_H

