#ifndef CREDIT_MENU_H
#define CREDIT_MENU_H
#include "cJSON.h"
#include "openssl_crypto.h"


struct Card {
    char name[100];
    char card_number[20];
    int expiry_month;
    int expiry_year;
};

// Function declarations
void show_menu();
void add_to_history(const char *encrypted_card);
void view_history();
void validate_card();
void api_lookup();
void save_card(struct Card new_card);
void add_card();
void view_cards();
cJSON *read_json_file(const char *filename);

#endif
 