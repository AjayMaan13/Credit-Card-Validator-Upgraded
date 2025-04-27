#ifndef CREDIT_H
#define CREDIT_H

#include <stdbool.h>

// ======== Card Utility Functions ========

// Checks if the card number matches known card types (Visa, MasterCard, etc.)
bool check_type(long num);

// Masks all digits except the last 4 (e.g., XXXXXXXXXXXX1234)
void mask_card_number(unsigned char card_number[]);

// Validates if the expiry date is valid (not in the past)
int check_expiry(int exp_month, int exp_year);

// Counts the number of digits in the card number
int count_digits(long num);

// Validates the card number using the Luhn algorithm
bool check_sum(long num);

#endif // CREDIT_H
