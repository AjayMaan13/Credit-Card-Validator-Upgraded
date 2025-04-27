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

int main() {
    int choice;

    while (1) {
        show_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                validate_card();
                break;
            case 2:
                api_lookup();
                break;
            case 3:
                view_history();
                break;
            case 4:
                add_card();
                break;
            case 5:
                view_cards();
                break;
            case 0:
                printf("👋 Exiting... Goodbye!\n");
                log_action("Exited program.");
                return 0;
            default:
                printf("❗ Invalid choice. Try again.\n");
        }
    }

    return 0;
}
