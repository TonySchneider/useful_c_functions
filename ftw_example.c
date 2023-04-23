#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

struct file_info{
    char *pathname;
};

static int get_file_info(const char *pathname, const struct stat *sbuf, int type) {
    if (type == FTW_F) {
        printf("%s\n", pathname);
        printf("\tSize: %ld bytes\n", (long) sbuf->st_size);
        printf("\tPermissions: %o\n", sbuf->st_mode & 0777);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (ftw(argv[1], get_file_info, 5) == -1) {
        perror("ftw");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}