#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 4096

const char *target_file_name;
int target_file_size = 0;

static int validate_file(const char *file_path, const struct stat *sbuf, int type) {
    int current_file_path_size = strlen(file_path);

    if (type == FTW_F) {
        if(strcmp(&file_path[current_file_path_size-target_file_size], target_file_name) == 0){

            printf("%s\n", file_path);
            printf("\tSize: %ld bytes\n", (long) sbuf->st_size);
            printf("\tPermissions: %o\n", sbuf->st_mode & 0777);
        }
    }
    return 0;
}

void find_files(const char *name) {
    target_file_name = name;
    target_file_size = strlen(name);

    printf("target_file_name - %s, target_file_size - %d", (char *) target_file_name, target_file_size);
    if (ftw(".", validate_file, MAX_PATH_LENGTH) == -1) {
        perror("ftw");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *target_file_name = argv[1];
    find_files(target_file_name);

    return 0;
}