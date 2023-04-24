#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int get_is_verified(const char* json_string) {
    cJSON* json = cJSON_Parse(json_string);
    if (!json) {
        fprintf(stderr, "Error parsing JSON string: %s\n", cJSON_GetErrorPtr());
        return -1;
    }
    cJSON* is_verified = cJSON_GetObjectItemCaseSensitive(json, "isVerified");
    if (!cJSON_IsBool(is_verified)) {
        fprintf(stderr, "Error retrieving 'isVerified' key\n");
        cJSON_Delete(json);
        return -1;
    }
    int result = cJSON_IsTrue(is_verified);
    cJSON_Delete(json);
    return result;
}

int main() {
    const char* json_string = "{\"isVerified\":\"false\"}";
    int is_verified = get_is_verified(json_string);
    printf("isVerified = %d\n", is_verified);
    return 0;
}