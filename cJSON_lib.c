#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

int get_is_verified(const char* json_string) {
    json_error_t error;
    json_t* root = json_loads(json_string, 0, &error);
    if (!root) {
        fprintf(stderr, "Error parsing JSON string: %s\n", error.text);
        return -1;
    }
    json_t* is_verified = json_object_get(root, "isVerified");
    if (!json_is_boolean(is_verified)) {
        fprintf(stderr, "Error retrieving 'isVerified' key\n");
        json_decref(root);
        return -1;
    }
    int result = json_boolean_value(is_verified);
    json_decref(root);
    return result;
}

int main() {
    const char* json_string = "{\"isVerified\":\"false\"}";
    int is_verified = get_is_verified(json_string);
    printf("isVerified = %d\n", is_verified);
    return 0;
}