#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <json-c/json.h>

size_t static curl_write(void *buffer, size_t size, size_t nmemb, void *userp)
{
     userp += strlen(userp);  // Skipping to first unpopulated char
     memcpy(userp, buffer, nmemb);  // Populating it.
     return nmemb;
}

// function to send an API request and check if "isVerified" is true in the response
int is_verified(char* file_path, char* hash_value) {
    CURL *curl;
    CURLcode res;
    char url[1000];
    //char response[10000] = {0};
    char *response = (char *) malloc(512);
    struct json_object *root;
    struct json_tokener *tok;
    enum json_tokener_error error;
    int is_verified = 0;

    printf("creating url\n");
    // create the URL for the API request
    sprintf(url, "http://example.com:9000/verify_credential_app/%s/%s", file_path, hash_value);

    printf("intializing url: %s\n", url);
    // initialize curl
    curl = curl_easy_init();

    if(curl) {
	// set the URL for the API request
        curl_easy_setopt(curl, CURLOPT_URL, url);

        printf("sending api request\n");
        // send the API request and retrieve the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }

	// cleanup curl

        printf("cleanup\n");
        curl_easy_cleanup(curl);
    }

    // parse the JSON response
    tok = json_tokener_new();
    root = json_tokener_parse_ex(tok, response, strlen(response));

    if(!root) {
        fprintf(stderr, "error: %s\n", json_tokener_error_desc(tok->err));
        json_tokener_free(tok);
        return 0;
    }


    // check if "isVerified" is true in the JSON response
    struct json_object *is_verified_obj;
    if (json_object_object_get_ex(root, "isVerified", &is_verified_obj)) {
        is_verified = json_object_get_boolean(is_verified_obj);
    }

    // cleanup JSON
    json_object_put(root);
    json_tokener_free(tok);

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