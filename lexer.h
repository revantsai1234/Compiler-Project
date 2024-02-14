#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "buffer.h"

TokenInfo getNextToken(TwinBuffer* tb, int curr);

#endif // LEXER_H