#ifndef LEXER_H
#define LEXER_H

#include "lexerDef.h"

const char *getTokenTypeName(TokenType type);
void setNode(struct node *node, char *key, TokenType token);
void initializeHashMap(struct hashMap *mp);
int hashFunction(struct hashMap *mp, char *key);
void insert(struct hashMap *mp, char *key, TokenType token);
TokenType search(struct hashMap *mp, char *key);
void insertKeyWords(struct hashMap *mp);


FILE *getStream(FILE *fp, int space_to_fill);
void checklimits(void);
TokenInfo getNextToken(void);

void removeComments(char *testcaseFile, char *cleanFile);
const char *getTokenTypeName(TokenType type); 

#endif