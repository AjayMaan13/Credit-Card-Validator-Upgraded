#include "openssl_crypto.h"
#include <openssl/evp.h>
#include <string.h>

// Define and initialize key and iv here
unsigned char key[64] = "01234567890123456789012345678901"; // 64 bytes
unsigned char iv[16]  = "0123456789012345"; // 16 bytes


void encrypt_data(const unsigned char *plaintext, int plaintext_len,
                  unsigned char *ciphertext, int *ciphertext_len,
                  const unsigned char *key, const unsigned char *iv)
{
    EVP_CIPHER_CTX *ctx;
    int len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        // Error handling
        return;
    }

    // Initialize the encryption operation.
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        // Error handling
        return;
    }

    // Provide the message to be encrypted, and obtain the encrypted output.
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {
        // Error handling
        return;
    }
    *ciphertext_len = len;

    // Finalize the encryption.
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        // Error handling
        return;
    }
    *ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

void decrypt_data(const unsigned char *ciphertext, int ciphertext_len,
                  unsigned char *decrypted, int *decrypted_len,
                  const unsigned char *key, const unsigned char *iv)
{
    EVP_CIPHER_CTX *ctx;
    int len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        // Error handling
        return;
    }

    // Initialize the decryption operation.
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        // Error handling
        return;
    }

    // Provide the message to be decrypted, and obtain the decrypted output.
    if (1 != EVP_DecryptUpdate(ctx, decrypted, &len, ciphertext, ciphertext_len))
    {
        // Error handling
        return;
    }
    *decrypted_len = len;

    // Finalize the decryption.
    if (1 != EVP_DecryptFinal_ex(ctx, decrypted + len, &len))
    {
        // Error handling
        return;
    }
    *decrypted_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

// Base64 decode
unsigned char *base64_decode(const char *input, int *out_len)
{
    BIO *b64, *bmem;
    int length = strlen(input);
    unsigned char *buffer = (unsigned char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // No newlines
    bmem = BIO_new_mem_buf((void *)input, length);
    bmem = BIO_push(b64, bmem);

    *out_len = BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}
