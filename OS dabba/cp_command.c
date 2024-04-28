#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open the source file for reading
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing (creating if it doesn't exist)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Copy data from source to destination
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Close file descriptors
    close(source_fd);
    close(dest_fd);

    return 0;
}
