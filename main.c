#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

int main() {
    FILE *file;
    TwinBuffer tb;
    int bytesRead;

    file = fopen("/home/revant/Desktop/3-2/CoCo/Compiler-Project/symbolTable.c", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Initialize the TwinBuffer
    tb.file = file;
    tb.activeBuffer = 0; // Start with buffer1
    tb.bufferEnd = 0; // Not at the end of buffer
    // Main loop to read and print the file content using the twin buffer
    do {
        bytesRead = loadBuffer(&tb); // Load data into the active buffer
        // bytesRead = tb.forward - (tb.activeBuffer == 0 ? tb.buffer1 : tb.buffer2);
        printf("Number of bytes read = %d\n", bytesRead);
        if (bytesRead == 0) {
            // Print the contents of the active buffer
            printf("Zero bytes read\n");
        }
    } while (!tb.bufferEnd); // Continue until the end of the file
    printf("Exited\n");
    // Close the file
    fclose(file);
}
