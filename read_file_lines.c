#include <stdio.h>
#include <stdlib.h>

void read_file(const char* file_path, char** list, int list_size) {
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (i >= list_size) {
            fprintf(stderr, "List size too small\n");
            exit(EXIT_FAILURE);
        }
        // Remove newline character at the end of the line
        line[strcspn(line, "\n")] = '\0';
        // Copy the line into the list
        list[i] = strdup(line);
        i++;
    }

    fclose(fp);
}

int main() {
    const char* file_path = "trust.txt";
    const int list_size = 100;
    char** list = malloc(list_size * sizeof(char*));
    read_file(file_path, list, list_size);

    // Print the list of file names
    for (int i = 0; i < list_size; i++) {
        if (list[i] != NULL) {
            printf("%s\n", list[i]);
        } else {
            break;
        }
    }

    // Free the memory allocated for the list
    for (int i = 0; i < list_size; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}