#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexerDef.h" // Ensure this file contains all necessary type definitions

// Token operations
const char *getTokenTypeName(TokenType type);

// Hash map operations
void setNode(struct node *node, char *key, TokenType token);
void initializeHashMap(struct hashMap *mp);
int hashFunction(struct hashMap *mp, char *key);
void insert(struct hashMap *mp, char *key, TokenType token);
TokenType search(struct hashMap *mp, char *key);
void insertKeyWords(struct hashMap *mp);

// Stream and token processing
FILE *getStream(FILE *fp, int space_to_fill);
void checklimits(void);
TokenInfo getNextToken(void);

// Comment removal
void removeComments(char *testcaseFile);
long getFileSize(FILE* fp);
void printFileContents(FILE * fp);
void printLexemes(char *fileName);

#endif // LEXER_H
