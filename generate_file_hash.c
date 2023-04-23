#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define BUFSIZE 4096

char* sha256_file(char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        return 0;
    }

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    unsigned char buf[BUFSIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buf, 1, BUFSIZE, file))) {
        SHA256_Update(&ctx, buf, bytes_read);
    }
    fclose(file);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);

    char *hex = malloc(sizeof(char) * (SHA256_DIGEST_LENGTH * 2 + 1));
    if (!hex) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex[i * 2], "%02x", hash[i]);
    }

    hex[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hex;
}

int main(int argc, char *argv[]) {
    char* path = argv[1];
    char* hash = NULL;
    hash = sha256_file(path);

    if (hash) {
        printf("SHA256 hash of %s: %s\n", path, hash);
    } else {
        printf("Error: could not calculate SHA256 hash of %s\n", path);
    }
    return 0;
}