#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char sourceFileName[256];
    char destFileName[256];

    printf("Enter the name of the source file: ");
    scanf("%s", sourceFileName);

    if (access(sourceFileName, F_OK) == -1) {
        perror("Source file does not exist");
        exit(1);
    }

    printf("Enter the name of the destination file: ");
    scanf("%s", destFileName);

    int sourceFile = open(sourceFileName, O_RDONLY);
    if (sourceFile == -1) {
        perror("Error opening source file");
        exit(1);
    }

    int destFile = open(destFileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (destFile == -1) {
        perror("Error opening destination file");
        close(sourceFile);
        exit(1);
    }

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer)))> 0) {
        printf("Read %ld bytes\n", bytesRead); // Debugging line
        if (write(destFile, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFile);
            close(destFile);
            exit(1);
        }
        printf("Wrote %ld bytes\n", bytesRead); // Debugging line
    }

    close(sourceFile);
    close(destFile);
    printf("File copy successful.\n");
}
