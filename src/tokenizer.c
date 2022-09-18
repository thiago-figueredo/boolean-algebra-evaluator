#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <string.h> 
#include <assert.h>
#include "./tokenizer.h"
#include "./linked_list.h"
#include "./string_utils.h"
#include "./lexer.h"

static char* tokens_type[] = {
    [AND] = "AND_OPERATOR",
    [OR] = "OR_OPERATOR",
    [NOT] = "NOT_OPERATOR",
    [XOR] = "XOR_OPERATOR",
    [XAND] = "XAND_OPERATOR",
    [VARIABLE] = "VARIABLE",
    [LEFT_PARENTHESIS] = "LEFT_PARENTHESIS",
    [RIGHT_PARENTHESIS] = "RIGHT_PARENTHESIS",
    [UNKNOWN] = "UNKNOWN",
    [BOOLEAN] = "BOOLEAN",
};

Token* new_token(TokenType type, char* content) 
{
    Token* token = malloc(sizeof(Token));
    
    token->type = type;
    token->content = content ? calloc(strlen(content), sizeof(char)) : NULL;

    if (content) {
        strcpy(token->content, content);
    }

    return token;
}

LinkedList* tokenize(char* expression) 
{
    assert(expression && "Could not tokenize null expression");

    LinkedList* tokens = new_linked_list();
    Lexer* lexer = new_lexer(expression);

    while (has_next_token(lexer)) {
        linked_list_insert(tokens, next_token(lexer));
    }

    return tokens;
}

void print_token(Token token) 
{
    if (token.type < AND && token.type > BOOLEAN) {
        fprintf(stderr, "Invalid token: %s\n", token.content);
        return;
    }

    printf("{ TOKEN_TYPE: %s, TOKEN_CONTENT: %s }\n", tokens_type[token.type], token.content);
}

void print_tokens(LinkedList* tokens)
{
    assert(tokens && "Cannot print a null tokens linked list");

    LinkedListNode* token = tokens->head;

    while (token) {
        print_token(*((Token*)token->data));
        token = token->next;
    }
}