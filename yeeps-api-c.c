#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

typedef struct {
    char *data;
    size_t size;
} Response;

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    Response *resp = (Response *)userp;

    char *ptr = realloc(resp->data, resp->size + total + 1);
    if (!ptr)
        return 0;

    resp->data = ptr;
    memcpy(resp->data + resp->size, contents, total);
    resp->size += total;
    resp->data[resp->size] = '\0';

    return total;
}

char *api_call(const char *oculusID, const char *mobileCode) {
    CURL *curl;
    CURLcode res;
    Response response = {0};

    // Create JSON body
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "oculusID", oculusID);
    cJSON_AddStringToObject(json, "mobileCode", mobileCode);

    char *json_body = cJSON_PrintUnformatted(json);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl = curl_easy_init();
    if (!curl) {
        cJSON_Delete(json);
        free(json_body);
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://yeeps-proxy.onrender.com/yeeps");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
        free(response.data);
        response.data = NULL;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    cJSON_Delete(json);
    free(json_body);

    return response.data;
}

int main(void) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    char *response = api_call("ExampleOculusID", "123456");

    if (response) {
        printf("Response:\n%s\n", response);

        cJSON *json = cJSON_Parse(response);
        if (json) {
            printf("Valid JSON received.\n");
            cJSON_Delete(json);
        }

        free(response);
    }

    curl_global_cleanup();
    return 0;
}
