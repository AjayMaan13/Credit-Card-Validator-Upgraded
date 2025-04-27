#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cJSON.h"

#define LOG_FILE "log.json"

void log_action(const char *message) {
    FILE *file = fopen(LOG_FILE, "a");
    if (!file) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    cJSON *log_entry = cJSON_CreateObject();
    cJSON_AddStringToObject(log_entry, "timestamp", asctime(t));
    cJSON_AddStringToObject(log_entry, "message", message);

    char *log_str = cJSON_PrintUnformatted(log_entry);
    fprintf(file, "%s\n", log_str);

    free(log_str);
    cJSON_Delete(log_entry);
    fclose(file);
}
