#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <jansson.h>

// function to send an API request and check if "isVerified" is true in the response
int is_verified(char* file_path, char* hash_value) {
    CURL *curl;
    CURLcode res;
    char url[1000];
    char response[1000];
    json_t *root;
    json_error_t error;

    // create the URL for the API request
    sprintf(url, "http://example.com/verify_credential_app/%s/%s", file_path, hash_value);

    // initialize curl
    curl = curl_easy_init();

    if(curl) {
        // set the URL for the API request
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // send the API request and retrieve the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &strcpy);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }

        // cleanup curl
        curl_easy_cleanup(curl);
    }

    // parse the JSON response
    root = json_loads(response, 0, &error);

    if(!root) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 0;
    }

    // check if "isVerified" is true in the JSON response
    json_t *is_verified_value = json_object_get(root, "isVerified");
    int is_verified = json_is_true(is_verified_value);

    // cleanup JSON
    json_decref(root);

    // return 1 if "isVerified" is true, or 0 if it's not
    return is_verified;
}

int main() {
    char file_path[] = "";
    char hash_value[] = "";
    int result;

    result = is_verified(file_path, hash_value);

    if(result == 1) {
        printf("The file is verified.\n");
    } else {
        printf("The file is not verified.\n");
    }

    return 0;
}