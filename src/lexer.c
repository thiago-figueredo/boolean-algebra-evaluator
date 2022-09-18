#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/types.h>
#include "lexer.h"
#include "tokenizer.h"
#include "string_utils.h"

Lexer* new_lexer(char* data)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    assert(lexer && "Cannot malloc lexer");
    assert(data && "Cannot lex a null string");

    lexer->position = 0;
    lexer->token = new_token(-1, NULL);
    assert(lexer->token && "Could not allocate lexer token");
    lexer->data = data;

    return lexer;
}

char current_char(Lexer* lexer)
{
    assert(lexer && "Cannot get current char of a null lexer");
    size_t current_position = lexer->position;

    if (current_position < 0 || current_position > strlen(lexer->data)) {
        return '\0';
    }

    return lexer->data[current_position];
}

char next_char(Lexer* lexer) {
    assert(lexer && "Cannot get next char of a null lexer");
    size_t next_position = lexer->position + 1;

    if (next_position > strlen(lexer->data)) {
        return '\0';
    }

    return lexer->data[next_position];
}

void advance(Lexer* lexer, ssize_t n)
{
    assert(lexer && "Cannot advance a null lexer");
    assert(lexer->position + n <= strlen(lexer->data) && "Cannot advance more then lexer data length");
    assert(lexer->position + n >= 0 && "Cannot advance less then first char of lexer data");

    lexer->position += n;
}

Token* next_token(Lexer* lexer)
{
    assert(lexer && "Cannot get previous char of a null lexer");
    Token* token = NULL;
    char c = current_char(lexer);
    char content[MAX_EXPRESSION_SIZE] = { 0 };
    content[0] = c;

    if (c == AND_OPERATOR) {
        token = new_token(AND, content);
    } else if (c == '(') {
        char next_character = next_char(lexer);

        if (next_character == AND_OPERATOR || next_character == OR_OPERATOR) {
            uint8_t i;

            for (i = 1; next_character != ')'; i++) {
                content[i] = next_character;
                advance(lexer, 1);
                next_character = next_char(lexer);
            }

            advance(lexer, 1);
            content[i] = next_character;

            if (string_equals(content, XOR_OPERATOR)) {
                token = new_token(XOR, content);
            } else {
                token = new_token(XAND, content);
            }
        } else {
            token = new_token(LEFT_PARENTHESIS, content);
        }
    } else if (c == ')') {
        token = new_token(RIGHT_PARENTHESIS, content);
    } else if (c == OR_OPERATOR) {
        token = new_token(OR, content);
    } else if (c == NOT_OPERATOR || c == '\\') {
        token = new_token(NOT, content);
    } else if (isalpha(c)) {
        token = new_token(VARIABLE, content);
    } else if (is_bool(c)) {
        token = new_token(BOOLEAN, content);
    } else {
        token = new_token(UNKNOWN, content);
    }

    lexer->position++;
    return token;
}

bool has_next_token(Lexer* lexer)
{
    assert(lexer &&  "Cannot check that lexer has next token if it's null");
    return lexer->position + 1 <= strlen(lexer->data);
}