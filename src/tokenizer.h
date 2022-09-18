#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "./linked_list.h"

#define MAX_EXPRESSION_SIZE 2048

typedef enum { 
    AND, 
    OR, 
    NOT, 
    XOR, 
    XAND, 
    VARIABLE,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    UNKNOWN,
    BOOLEAN,
} TokenType; 

typedef struct {
    TokenType type;
    char* content;
} Token;

Token* new_token(TokenType type, char* content);
LinkedList* tokenize(char* expression);
void print_token(Token token);
void print_tokens(LinkedList* tokens);

#endif 