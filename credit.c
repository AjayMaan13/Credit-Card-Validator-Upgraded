#include <stdio.h>
#include <stdbool.h>  // Standard header for bool type
#include <string.h>
#include <time.h>


/*
int main(void)
{
    long int number;

    while (1)
    {
        count = 0;  // Reset count every loop

        printf("Enter Card Number (0 to exit): ");
        if (scanf("%ld", &number) != 1)
        {
            // Clear invalid input
            while (getchar() != '\n');
            continue;
        }

        // Exit condition
        if (number == 0)
        {
            printf("Exiting program.\n");
            break;
        }

        // Ignore negative numbers
        if (number < 0)
        {
            printf("Please enter a positive number.\n");
            continue;
        }

        long copy = number;
        while (copy != 0)
        {
            copy = copy / 10;
            count++;
        }

        if (check_sum(number) == false)
        {
            printf("INVALID\n");
        }
        else
        {
            check_type(number);
        }
    }

    return 0;
}
*/

int count_digits(long num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

// This function is used to check the sum value of a card number
bool check_sum(long num)
{
    // These are all the variables used in the check_sum function
    int total = 0;
    int even_sum = 0;
    int odd_sum = 0;
    long long even_ten1 = 100;
    long long even_ten2 = 10;
    long long odd_ten1 = 10;
    long long odd_ten2 = 1;

    int count = count_digits(num);  // FIXED: get digit count properly

    // This finds the sum of even places in the number
    for (int j = 0 ; j < 1 + (count / 2) ; j++)
    {
        int sum = 2 * ((num % even_ten1) / even_ten2);
        // This is used when the digit exceeds the value of 10 and we want to add only the unit places together
        if (sum > 9)
        {
            even_sum += (sum / 10);
            even_sum += (sum % 10);
        }
        // Normal case when sum is less than 10
        else
        {
            even_sum += sum;
        }
        even_ten1 *= 100;
        even_ten2 *= 100;

    }
    for (int k = 0 ; k < 1 + (count / 2) ; k++)
    {
        odd_sum += ((num % odd_ten1) / odd_ten2);
        odd_ten1 *= 100;
        odd_ten2 *= 100;
    }
    // assigning the total value of the sum
    total = even_sum + odd_sum;

    //Final checking of the check_sum fucntion if it is a multiple of 10
    if ((total % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//American Express - 15 digits           starts with 34 and 37
//MasterCard       - 16 digits           starts with 51,52,53,54 and 55
//Visa             - 13 and 16 digits    starts with 4
bool check_type(long num)
{
    int count = count_digits(num);

    // using count number here to check if it checks out the nard requirements
    if (count == 15)
    {
        // if the first 2 digits of the card are 34 or 36
        if (((num % 1000000000000000) / 10000000000000) == 34 || ((num % 1000000000000000) / 10000000000000) == 37)
        {
            printf("AMEX\n");
            return true;
        }
        else
        {
            printf("INVALID\n");
            return false;
        }

    }
    else if (count == 13)
    {
        // If the first digit of the card is 4
        if (((num % 10000000000000) / 1000000000000) == 4)
        {
            printf("VISA\n");
            return true;
        }
        else
        {
            printf("INVALID\n");
            return false;
        }

    }
    else if (count == 16)
    {
        //if the first two digits of the card is 51 or 52 or 53 or 54 or 55
        if (((num % 10000000000000000) / 100000000000000) == 51 || ((num % 10000000000000000) / 100000000000000) == 52
            || ((num % 10000000000000000) / 100000000000000) == 53 || ((num % 10000000000000000) / 100000000000000) == 54
            || ((num % 10000000000000000) / 100000000000000) == 55)
        {
            printf("MASTERCARD\n");
            return true;
        }
        // if the first digit of the card is 4
        else if (((num % 10000000000000000) / 1000000000000000) == 4)
        {
            printf("VISA\n");
            return true;
        }
        else
        {
            printf("INVALID\n");
            return false;
        }
    }
    // If all value do not checks out
    else
    {
        printf("INVALID\n");
        return false;
    }
}


// Function to mask card number
void mask_card_number(unsigned char card_number[]) {
    
    int len = 0;

    // Find the length of the string manually
    while (card_number[len] != '\0') {
        len++;
    }
    
    // Mask all but the last 4 digits
    for (int i = 0; i < len - 5; i++) {
        card_number[i] = '*';  // Replace with asterisk
        if ((i + 1) % 4 == 0) {
            card_number[i] = ' ';  // Add space after every 4 characters
        }
    }
    
    // The last 4 digits remain unchanged
    for (int i = len - 4; i < len; i++) {
        // Keep the last 4 digits visible
    }
}

int check_expiry(int exp_month, int exp_year) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    int current_year = tm.tm_year + 1900; // tm_year gives years since 1900
    int current_month = tm.tm_mon + 1; // tm_mon gives months from 0-11

    // Compare the expiry year and month with the current date
    if (exp_year < current_year || (exp_year == current_year && exp_month < current_month)) {
        return 0;  // Card expired
    }
    return 1;  // Card is valid
}




