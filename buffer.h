#ifndef BUFFER_H
#include <stdio.h>
#define BUFFER_H

#define BUFFER_SIZE 1024

typedef struct {
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    char *forward;
    int activeBuffer; // 0 for buffer1, 1 for buffer2
    int bufferEnd; // Indicates the end of the current buffer
    FILE *file;
} TwinBuffer;

void loadBuffer(TwinBuffer *tb);

#endif // BUFFER_H
