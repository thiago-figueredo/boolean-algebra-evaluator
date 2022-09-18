#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <sys/types.h>
#include "tokenizer.h"

typedef struct {
    Token* token;
    char* data;
    ssize_t position;
} Lexer;

Lexer* new_lexer(char* data);
Token* next_token(Lexer* lexer);
char current_char(Lexer* lexer);
char next_char(Lexer* lexer);
bool has_next_token(Lexer* lexer);
void advance(Lexer* lexer, ssize_t n);

#endif