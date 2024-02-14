#include "lexer.h"
#include "token.h"
#include "buffer.h"

TokenInfo getNextToken(TwinBuffer* tb, int curr) {
    // Lexer implementation
    char currBuffer[BUFFER_SIZE];
    if(tb->activeBuffer){
        for(int i=0;i<BUFFER_SIZE;i++){
            currBuffer[i]=tb->buffer1[i];
        }
    }
    else {
        for(int i=0;i<BUFFER_SIZE;i++){
            currBuffer[i]=tb->buffer2[i];
        }
    }
    
}