#include <stdio.h>

long get_file_size(char *filename) {
    FILE *fp;
    long size;

    fp = fopen(filename, "rb"); // open the file in binary mode
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1; // return -1 to indicate an error
    }

    fseek(fp, 0L, SEEK_END); // move the file pointer to the end of the file
    size = ftell(fp); // get the position of the file pointer, which is the size of the file in bytes
    fclose(fp); // close the file

    return size;
}

int main(int argc, char *argv[]) {
    char* filename = argv[1];
    long size;

    size = get_file_size(filename);

    if (size == -1) {
        printf("Error getting file size\n");
    } else {
        printf("The file size is %ld bytes\n", size);
    }

    return 0;
}
