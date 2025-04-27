#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "api.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) return 0;

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void lookup_card_info(const char *card_number) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk = { malloc(1), 0 };

    char url[256];
    snprintf(url, sizeof(url), "https://lookup.binlist.net/%.6s", card_number);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            cJSON *json = cJSON_Parse(chunk.memory);
            if (json) {
                cJSON *scheme = cJSON_GetObjectItem(json, "scheme");
                cJSON *brand = cJSON_GetObjectItem(json, "brand");
                cJSON *type = cJSON_GetObjectItem(json, "type");
                cJSON *bank = cJSON_GetObjectItem(json, "bank");
                cJSON *country = cJSON_GetObjectItem(json, "country");

                printf("🛰 BIN Info:\n");
                printf("  Scheme : %s\n", scheme ? scheme->valuestring : "Unknown");
                printf("  Brand  : %s\n", brand ? brand->valuestring : "Unknown");
                printf("  Type   : %s\n", type ? type->valuestring : "Unknown");
                printf("  Bank   : %s\n", bank ? cJSON_GetObjectItem(bank, "name")->valuestring : "Unknown");
                printf("  Country: %s\n", country ? cJSON_GetObjectItem(country, "name")->valuestring : "Unknown");

                cJSON_Delete(json);
            }
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    }

    curl_global_cleanup();
}
