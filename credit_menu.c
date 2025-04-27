#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "api.h"
#include "logger.h"
#include "credit.h"
#include "openssl_crypto.h"
#include "cJSON.h"
#include "credit_menu.h"
#include <openssl/evp.h>



#define MAX_CARD_LEN 32
#define HISTORY_FILE "history.txt"


void show_menu() {
    printf("\n======= CARD VALIDATOR MENU =======\n");
    printf("1. ✅ Check Card Validity & Type\n");
    printf("2. 🌐 Lookup Card Info via API\n");
    printf("3. 📜 View Encrypted Card History\n");
    printf("4. ➕ Add New Card\n");
    printf("5. 📂 View Saved Cards\n");
    printf("0. ❌ Exit\n");
    printf("===================================\n");
    printf("Choose an option: ");
}

void add_to_history(const char *encrypted_card) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file) {
        fprintf(file, "%s\n", encrypted_card);
        fclose(file);
    } else {
        printf("⚠️ Unable to save to history.\n");
    }
}

void view_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    char line[128];

    printf("\n📜 Encrypted Card History:\n");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            printf("• %s", line);
        }
        fclose(file);
    } else {
        printf("⚠️ No history found.\n");
    }
}

void validate_card() {
    char card_input[MAX_CARD_LEN];
    printf("Enter Card Number: ");
    scanf("%s", card_input);

    long card_num = atol(card_input);
    int count = count_digits(card_num);

    if (count < 13 || count > 16) {
        printf("❌ Invalid card length.\n");
        log_action("Invalid card length entered.");
        return;
    }

    if (!check_sum(card_num)) {
        printf("❌ INVALID CARD (Checksum failed)\n");
        log_action("Checksum failed.");
        return;
    }

    if (!check_type(card_num)) {
        log_action("Card type not recognized.");
        return;
    }

    // Encryption section
    unsigned char ciphertext[MAX_CARD_LEN * 2]; // Encrypted data
    int ciphertext_len = 0;

    // BUG SOLVED
    encrypt_data(
        (unsigned char *)card_input,   // card_input is cast to unsigned char *
        strlen(card_input),            // strlen for the length
        ciphertext,                    // ciphertext is unsigned char[MAX_LENGTH]
        &ciphertext_len,               // pass pointer to ciphertext_len
        key,                           // key is a const unsigned char *
        iv                             // iv is a const unsigned char *
    );
    

    // Save to history
    add_to_history((char *)ciphertext);

    printf("✅ Card is VALID. Encrypted and saved to history.\n");
    log_action("Card validated and saved (AES encrypted).");
}

void api_lookup() {
    char card_input[MAX_CARD_LEN];
    printf("Enter Card Number for API lookup: ");
    scanf("%s", card_input);

    lookup_card_info(card_input); // This uses cJSON + BIN API
    log_action("Card BIN lookup via API.");
}

void save_card(struct Card new_card) {
    // Load existing cards
    cJSON *cards = read_json_file("cards.json");
    if (!cards) cards = cJSON_CreateArray();


    // Encrypt the card number
    unsigned char ciphertext[128] = {0};
    int ciphertext_len = 0;
    encrypt_data((unsigned char *)new_card.card_number, strlen(new_card.card_number),
                 ciphertext, &ciphertext_len, key, iv);

    // Base64-encode the ciphertext
    int encoded_len = 4 * ((ciphertext_len + 2) / 3); // Base64 length calculation
    unsigned char *encoded = (unsigned char *)malloc(encoded_len + 1);
    if (!encoded) {
        printf("❗ Memory allocation error.\n");
        cJSON_Delete(cards);
        return;
    }
    EVP_EncodeBlock(encoded, ciphertext, ciphertext_len);

    // Build a new card JSON object
    cJSON *card_json = cJSON_CreateObject();
    cJSON_AddStringToObject(card_json, "name", new_card.name);
    cJSON_AddStringToObject(card_json, "card_number", (char *)encoded);
    cJSON_AddNumberToObject(card_json, "expiry_month", new_card.expiry_month);
    cJSON_AddNumberToObject(card_json, "expiry_year", new_card.expiry_year);

    cJSON_AddItemToArray(cards, card_json);

    // Write the updated array back to file
    FILE *file = fopen("cards.json", "w");
    if (!file) {
        printf("❗ Error opening file for writing.\n");
        free(encoded);
        cJSON_Delete(cards);
        return;
    }

    char *json_str = cJSON_Print(cards);
    fprintf(file, "%s", json_str);
    fclose(file);

    free(encoded);
    free(json_str);
    cJSON_Delete(cards);
}

void add_card() {
    struct Card new_card;

    // Get cardholder name
    printf("Enter cardholder name: ");
    fgets(new_card.name, sizeof(new_card.name), stdin);
    new_card.name[strcspn(new_card.name, "\n")] = '\0'; // Remove newline from name

    // Get card number (make sure to check it is valid, here simplified)
    printf("Enter card number: ");
    fgets(new_card.card_number, sizeof(new_card.card_number), stdin);
    new_card.card_number[strcspn(new_card.card_number, "\n")] = '\0'; // Remove newline from number

    // Get expiry month and validate
    printf("Enter expiry month (1-12): ");
    scanf("%d", &new_card.expiry_month);
    while (new_card.expiry_month < 1 || new_card.expiry_month > 12) {
        printf("Invalid month. Enter expiry month (1-12): ");
        scanf("%d", &new_card.expiry_month);
    }

    // Get expiry year and validate
    printf("Enter expiry year (e.g., 2025): ");
    scanf("%d", &new_card.expiry_year);
    while (new_card.expiry_year < 2023) { // Ensuring year is at least current year
        printf("Invalid year. Enter expiry year (e.g., 2025): ");
        scanf("%d", &new_card.expiry_year);
    }

    // Here, save the card (e.g., to a file or memory; simplified)
    save_card(new_card);

    printf("✅ Card added successfully.\n");
}

void view_cards() {
    printf("\n======= SAVED CARDS =======\n");

    cJSON *cards = read_json_file("cards.json");
    if (!cards || !cJSON_IsArray(cards)) {
        printf("❗ No valid cards found.\n");
        if (cards) cJSON_Delete(cards);
        printf("===========================\n");
        return;
    }

    int index = 1;
    cJSON *card = NULL;
    cJSON_ArrayForEach(card, cards) {
        cJSON *name = cJSON_GetObjectItem(card, "name");
        cJSON *card_number = cJSON_GetObjectItem(card, "card_number");
        cJSON *exp_month = cJSON_GetObjectItem(card, "expiry_month");
        cJSON *exp_year = cJSON_GetObjectItem(card, "expiry_year");

        if (!cJSON_IsString(name) || !cJSON_IsString(card_number) ||
            !cJSON_IsNumber(exp_month) || !cJSON_IsNumber(exp_year)) {
            continue;
        }

        // Base64-decode the card number
        int decoded_len = (strlen(card_number->valuestring) * 3) / 4;
        unsigned char *decoded = (unsigned char *)malloc(decoded_len + 1);
        if (!decoded) {
            printf("❗ Memory allocation error.\n");
            continue;
        }
        decoded_len = EVP_DecodeBlock(decoded, (unsigned char *)card_number->valuestring, strlen(card_number->valuestring));

        // Decrypt the card number
        unsigned char decrypted[128] = {0};
        int decrypted_len = 0;
        decrypt_data(decoded, decoded_len, decrypted, &decrypted_len, key, iv);
        free(decoded);

        decrypted[decrypted_len] = '\0'; // Null-terminate the string

        mask_card_number(decrypted);

        printf("%d. %s - %s - Expiry: %02d/%d\n", index++, name->valuestring, decrypted,
               exp_month->valueint, exp_year->valueint);
    }

    cJSON_Delete(cards);
    printf("===========================\n");
}



// Function to read the JSON file and return a cJSON object
cJSON *read_json_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening JSON file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *data = (char *)malloc(length + 1);
    if (!data) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    fread(data, 1, length, file);
    data[length] = '\0';  // Null-terminate

    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
    }

    free(data);
    return json;
}