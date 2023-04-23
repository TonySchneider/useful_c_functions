#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item {
    const void* index;
    const void* data;
    struct item* next;
} list_item_t;

typedef struct list_header {
    long count;
    struct item* first;
    struct item* last;
} list_t;

void read_file(const char* file_path, list_t* list_ptr) {
    FILE* fp = fopen(file_path, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline character at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Create a new item for the line and add it to the list
        list_item_t* item = malloc(sizeof(list_item_t));
        if (item == NULL) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        item->index = NULL; // not used in this example
        item->data = strdup(line);
        item->next = NULL;
        if (list_ptr->count == 0) {
            list_ptr->first = item;
        } else {
            list_ptr->last->next = item;
        }
        list_ptr->last = item;
        list_ptr->count++;
    }

    fclose(fp);
}

int main() {
    const char* file_path = "file.txt";
    list_t list;
    list.count = 0;
    list.first = NULL;
    list.last = NULL;
    read_file(file_path, &list);

    // Print the list of file names
    list_item_t* item = list.first;
    while (item != NULL) {
        printf("%s\n", (char*) item->data);
        item = item->next;
    }

    // Free the memory allocated for the list
    item = list.first;
    while (item != NULL) {
        free((void*) item->data);
        list_item_t* next_item = item->next;
        free(item);
        item = next_item;
    }

    return 0;
}