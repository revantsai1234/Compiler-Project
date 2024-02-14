#include "buffer.h"

void loadBuffer(TwinBuffer *tb) {
    size_t bytesRead;
    if (tb->activeBuffer == 0) {
        bytesRead = fread(tb->buffer1, 1, BUFFER_SIZE, tb->file);
        // tb->buffer1[bytesRead] = EOF; // Append EOF at the end of the buffer
        tb->forward = tb->buffer1;
    } else {
        bytesRead = fread(tb->buffer2, 1, BUFFER_SIZE, tb->file);
        // tb->buffer2[bytesRead] = EOF; // Append EOF at the end of the buffer
        tb->forward = tb->buffer2;
    }
    tb->bufferEnd = bytesRead < BUFFER_SIZE; // Check if we've reached the end of the file
    tb->activeBuffer = 1 - tb->activeBuffer; // Switch the active buffer

}
